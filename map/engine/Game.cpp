#include "Game.h"
#include "../rendering/TextRenderer.h"

Game::Game() 
{
    velocity = 4.0f;
    acceleration = 0.0f;
    counter = 0;
    fpsString = new char[100];
    controlled = NULL;
    inventoryOn = false;
    
    supportedKeys.push_back(SDLK_w);
    supportedKeys.push_back(SDLK_a);
    supportedKeys.push_back(SDLK_s);
    supportedKeys.push_back(SDLK_d);
    supportedKeys.push_back(SDLK_f);
    supportedKeys.push_back(SDLK_TAB);
    for(std::list<char>::iterator iter = supportedKeys.begin(); iter != supportedKeys.end(); iter++) 
    {
        keyPresses[*iter] = false;
    }
}
    
bool Game::init(const char* title, const int flags) {
    int width,height;
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        
        // Declare display mode structure to be filled in.
        SDL_DisplayMode current;

        // Get current display mode of all displays.
        for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){
            int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);
            if(should_be_zero != 0)
            // In case of error...
                SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
            else
            // On success, print the current display mode.
                SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h, current.refresh_rate);
            width = current.w;
            height = current.h;
        }

        
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

    program = ShaderLoader::load("shaders/vertex_shader.vs", "shaders/fragment_shader.fg");     
    shaderUniform = ShaderUniform::getInstance(program);
    
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);  
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);  
    glViewport(0, 0, width, height);
    mode = GL_FILL;
       
    txFactory = new TextureFactory();
    txFactory->loadTextures();
    timer = new Timer();
    camera = new Camera(width, height);    
    level = new Level(txFactory->getTexture("mossy_wall")); 
    textRenderer = new TextRenderer(txFactory->getTexture("font")->getTexture());
    emitter = new Emitter(program);
    emitter->setTexture(txFactory->getTexture("particle"));
    
    level->bindVAO();        
    textRenderer->bindVAO();
    control = new ListBox(5,15,150,300);
    control->bindVAO();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(shaderUniform->get("tex"), 0);

    glUseProgram(program);            
    m_bRunning = true; 
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
    glUniformMatrix4fv(shaderUniform->get("camera_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getMatrix()));

    // set the projection matrix
    glUniformMatrix4fv(shaderUniform->get("proj_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getPerpsectiveProjection()));

    // w=0.0 equals directional light (sunlight), while w=1.0 equals positional light    
    glm::vec4 light = glm::vec4(25.0, 20.0, 15.0, 0.0f);
    glUniform4fv(shaderUniform->get("light_pos"), 1, glm::value_ptr(light));
    
    level->render(program, timer->getInGameFrameDuration());
    emitter->update(timer->getInGameFrameDuration(), camera->getRotation());   
}

void Game::render2D() 
{       
    glUniformMatrix4fv(shaderUniform->get("proj_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getOrthoProjection()));
    glUniformMatrix4fv(shaderUniform->get("camera_matrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    sprintf(fpsString, "FPS: %d", timer->getFPS());
    textRenderer->render(program, 0, 0, fpsString);        
    if (inventoryOn) {
        control->update(mouseState);
        control->render(program, timer->getInGameFrameDuration());
    }    
}

void Game::frameEnd()
{
    SDL_GL_SwapWindow(g_pWindow);
    SDL_GL_SetSwapInterval(0);
}

void Game::handleEvents() {
    SDL_Event event;

    velocity += acceleration * timer->getInGameFrameDuration();
    velocity = std::min(velocity, 8.0);    
    float distance = velocity * timer->getInGameFrameDuration();
    
    //continuous-response keys
    if (keyPresses.at(SDLK_w) || keyPresses.at(SDLK_a) || keyPresses.at(SDLK_s)
            || keyPresses.at(SDLK_d)) {
        counter++;
        acceleration += 0.05 * counter;
        if (keyPresses.at(SDLK_w)) {
            camera->moveForward(distance);
        }
        if (keyPresses.at(SDLK_s)) {
            camera->moveBackwards(distance);
        }
        if (keyPresses.at(SDLK_a)) {
            camera->strafeLeft(distance);
        }
        if (keyPresses.at(SDLK_d)) {
            camera->strafeRight(distance);
        }
    }

    SDL_GetMouseState(&mouseState.x, &mouseState.y);
    
    mouseState.leftButtonDown = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
    mouseState.middleButtonDown = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
    mouseState.rightButtonDown = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
    
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
                if (event.key.keysym.sym == SDLK_TAB) {
                    inventoryOn = inventoryOn ? false : true;
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
                if (event.motion.xrel > 100 || event.motion.xrel < -100)
                        camera->rotate(0.0f);
                else
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
    delete controlled;
    delete control;
    if (glContext) SDL_GL_DeleteContext(glContext);
    if (g_pWindow) SDL_DestroyWindow(g_pWindow);

    // clean up SDL
    SDL_Quit();
}
