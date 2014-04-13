#include "Game.h"
#include "TextRenderer.h"

Game::Game() 
{
    velocity = 4.0f;
    acceleration = 0.0f;
    counter = 0;
    fpsString = new char[100];
    
    supportedKeys.push_back(SDLK_w);
    supportedKeys.push_back(SDLK_a);
    supportedKeys.push_back(SDLK_s);
    supportedKeys.push_back(SDLK_d);
    supportedKeys.push_back(SDLK_f);
    for(std::list<char>::iterator iter = supportedKeys.begin(); iter != supportedKeys.end(); iter++) 
    {
        keyPresses[*iter] = false;
    }
}
    
bool Game::init(const char* title, const int xpos, const int ypos,
        const int width, const int height, const int flags) {
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // if succeeded create our window
        g_pWindow = SDL_CreateWindow("Dungeon",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

        // Create an OpenGL context associated with the window.
        glContext = SDL_GL_CreateContext(g_pWindow);
        if (glContext != NULL)
            std::cout << "GL Context setup properly" << std::endl;

    } else {
        return 1; // sdl could not initialize
    }    
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    std::cout << glGetError() << std::endl;
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    program = ShaderLoader::load("vertex_shader.vs", "fragment_shader.fg");     
    shaderUniform = new ShaderUniform(program);
    
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);  
    glViewport(0, 0, width, height);
    mode = GL_FILL;
    
    timer = new Timer();
    camera = new Camera(width, height);    
    level = new Level();    
    txFactory = new TextureFactory();
    txFactory->loadTextures();
    textRenderer = new TextRenderer(txFactory->getTexture("font")->getTexture());
    emitter = new Emitter(program);
    emitter->setTexture(txFactory->getTexture("particle"));
    
    level->bindVAO();        
    textRenderer->bindVAO();

    glUseProgram(program);            
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::frameStart()
{
    timer->tick();
}

void Game::render3D() {
    static const GLfloat gray[] = {0.2f, 0.2f, 0.2f, 1.0f};
    static const GLfloat one = 1.0f;

    glClearBufferfv(GL_COLOR, 0, gray);
    glClearBufferfv(GL_DEPTH, 0, &one);

    // store the "initial camera" matrix
    stack<glm::mat4> modelviewStack;
//    modelviewStack.push(mv_matrix_camera);       
    glUniformMatrix4fv(shaderUniform->get("camera_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getMatrix()));

    // set the projection matrix
    glUniformMatrix4fv(shaderUniform->get("proj_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getProjection(true)));

    // w=0.0 equals directional light (sunlight), while w=1.0 equals positional light
    // set the light matrix
    glm::vec4 light = glm::vec4(25.0, 20.0, 15.0, 0.0f);
    glUniform4fv(shaderUniform->get("light_pos"), 1, glm::value_ptr(light));

    // set the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, txFactory->getTexture("mossy_wall")->getTexture());
    glUniform1i(shaderUniform->get("tex"), 0);
    
    level->render(program, timer->getTimeElapsed());
    emitter->update(timer->getTimeElapsed(), camera->getRotation());   
}

void Game::render2D() 
{            
    glUniformMatrix4fv(shaderUniform->get("proj_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getProjection(false)));
    glUniformMatrix4fv(shaderUniform->get("camera_matrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    sprintf(fpsString, "FPS: %d", timer->getAverageFPS());
    textRenderer->render(program, 0, 0, fpsString);
}

void Game::frameEnd()
{
    SDL_GL_SwapWindow(g_pWindow);
    SDL_GL_SetSwapInterval(0);
}

void Game::handleEvents() {
    SDL_Event event;
    float yrotrad = (camera->getRotation() / 180 * M_PI);

    velocity += acceleration * timer->getTimeElapsed();
    velocity = std::min(velocity, 8.0);
    float zVector = float(cos(yrotrad)) * velocity * timer->getTimeElapsed();
    float xVector = float(sin(yrotrad)) * velocity * timer->getTimeElapsed();

    //continuous-response keys
    if (keyPresses.at(SDLK_w) || keyPresses.at(SDLK_a) || keyPresses.at(SDLK_s)
            || keyPresses.at(SDLK_d)) {
        counter++;
        acceleration += 0.05 * counter;
        if (keyPresses.at(SDLK_w)) {
            camera->move(glm::vec3(-xVector, 0.0f, zVector));
        }
        if (keyPresses.at(SDLK_s)) {
            camera->move(glm::vec3(xVector, 0.0f, -zVector));
        }
        if (keyPresses.at(SDLK_a)) {
            camera->move(glm::vec3(zVector, 0.0f, xVector));
        }
        if (keyPresses.at(SDLK_d)) {
            camera->move(glm::vec3(-zVector, 0.0f, -xVector));
        }
    }

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    m_bRunning = false;
                    break;
                }                
                if (event.key.keysym.sym == SDLK_f) {
                    mode = (mode == GL_LINE) ? GL_FILL : GL_LINE;
                    glPolygonMode(GL_FRONT_AND_BACK, mode);
                    break;
                }
                keyPresses[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                if (keyPresses.count(event.key.keysym.sym) && keyPresses.at(event.key.keysym.sym) == true) {
                    acceleration = 0.0;
                    velocity = 4.0;
                    counter = 0;
                    keyPresses[event.key.keysym.sym] = false;
                    break;
                }
            case SDL_MOUSEMOTION:                
                camera->rotate(event.motion.xrel / 5.0);
                break;
            default:
                break;
        }
    }
    // allows the mouse events to be processed even when cursor is out of the game window
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Game::clean() {
    std::cout << "cleaning game\n";
    glDeleteProgram(program);
    delete level;
    delete txFactory;
    delete textRenderer;
    delete[] fpsString;
    delete timer;
    delete emitter;
    if (glContext) SDL_GL_DeleteContext(glContext);
    if (g_pWindow) SDL_DestroyWindow(g_pWindow);

    // clean up SDL
    SDL_Quit();
}
