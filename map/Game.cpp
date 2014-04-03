#include "Game.h"
#include "TextRenderer.h"

Game::Game() 
{
    velocity = 4.0f;
    acceleration = 0.0f;
    counter = 0;
    keyPresses[SDLK_w] = false;
    keyPresses[SDLK_a] = false;
    keyPresses[SDLK_s] = false;
    keyPresses[SDLK_d] = false;
    fpsString = new char[100];
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

    GLuint program = LoadShader("vertex_shader.vs", "fragment_shader.fg");

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    mode = GL_FILL;
    level = new Level();
    particle = new Particle(1);
    x = z = rotY = 0.0f;
    mv_matrix_initial = glm::mat4(1.0f);

    glViewport(0, 0, width, height);
    aspect = (float) width / (float) height;

    proj_matrix = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
    ortho_matrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
    txFactory = new TextureFactory();
    txFactory->loadTextures();
    textRenderer = new TextRenderer(txFactory->getTexture("font")->getTexture());
    timer = new Timer();
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::frameStart()
{
    timer->tick();
}

void Game::render3D() {
    static const GLfloat gray[] = {0.6f, 0.6f, 0.6f, 1.0f};
    static const GLfloat one = 1.0f;

    glClearBufferfv(GL_COLOR, 0, gray);
    glClearBufferfv(GL_DEPTH, 0, &one);

    // store the "initial camera" matrix
    stack<glm::mat4> modelviewStack;

    modelviewStack.push(mv_matrix_initial);

    mv_rot_camera = glm::rotate(mv_matrix_initial, rotY, glm::vec3(0.0f, 1.0f, 0.0f));
    mv_matrix_camera = glm::translate(mv_matrix_initial, glm::vec3(x, 0.0f, 30.0f + z));
    mv_matrix_camera = mv_rot_camera * mv_matrix_camera;
    modelviewStack.push(mv_matrix_camera);
    GLuint camera_location = glGetUniformLocation(program, "camera_matrix");
    glUniformMatrix4fv(camera_location, 1, GL_FALSE, glm::value_ptr(mv_matrix_camera));

    // set the projection matrix
    GLint proj_location = glGetUniformLocation(program, "proj_matrix");
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj_matrix));

    // w=0.0 equals directional light (sunlight), while w=1.0 equals positional light
    // set the light matrix
    glm::vec4 light = glm::vec4(25.0, 20.0, 15.0, 0.0f);
    GLint light_pos = glGetUniformLocation(program, "light_pos");
    glUniform4fv(light_pos, 1, glm::value_ptr(light));

    // set the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, txFactory->getTexture("mossy_wall")->getTexture());
    GLint programTex = glGetUniformLocation(program, "tex");
    glUniform1i(programTex, 0);

    glUseProgram(program);
    level->bindVAO();
    level->render(program, timer->getTimeElapsed());
    
    glBindTexture(GL_TEXTURE_2D, txFactory->getTexture("font")->getTexture());
    particle->bindVAO();
    particle->render(program, timer->getTimeElapsed());
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(ortho_matrix));
    glUniformMatrix4fv(camera_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

    // object in static distance from viewer		
    /*modelviewStack.pop();
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(modelviewStack.top()));        		
    glUseProgram(program);
    level->render(program);*/
}

void Game::render2D() 
{        
    textRenderer->bindVAO();
    sprintf(fpsString, "FPS: %d", timer->getAverageFPS());
    textRenderer->render(program, 0, 0, fpsString);
}

void Game::frameEnd()
{
    SDL_GL_SwapWindow(g_pWindow);
    SDL_GL_SetSwapInterval(0);
}

void Game::clean() {
    std::cout << "cleaning game\n";
    glDeleteProgram(program);
    delete level;
    delete txFactory;
    delete textRenderer;
    delete[] fpsString;
    if (glContext) SDL_GL_DeleteContext(glContext);
    if (g_pWindow) SDL_DestroyWindow(g_pWindow);

    // clean up SDL
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    float yrotrad = (rotY / 180 * M_PI);

    velocity += acceleration * timer->getTimeElapsed();
    velocity = std::min(velocity, 8.0);
    float zVector = float(cos(yrotrad)) * velocity * timer->getTimeElapsed();
    float xVector = float(sin(yrotrad)) * velocity * timer->getTimeElapsed();

    SDL_PumpEvents();
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    //continuous-response keys
    if (keyPresses.at(SDLK_w) || keyPresses.at(SDLK_a) || keyPresses.at(SDLK_s)
            || keyPresses.at(SDLK_d)) {
        counter++;
        acceleration += 0.05 * counter;
        if (keyPresses.at(SDLK_w)) {
            z += zVector;
            x -= xVector;
        }
        if (keyPresses.at(SDLK_s)) {
            z -= zVector;
            x += xVector;

        }
        if (keyPresses.at(SDLK_a)) {
            z -= -xVector;
            x += zVector;
        }
        if (keyPresses.at(SDLK_d)) {
            z += -xVector;
            x -= zVector;
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
                if (event.key.keysym.sym == SDLK_w) {
                    keyPresses[SDLK_w] = true;
                    break;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    keyPresses[SDLK_s] = true;
                    break;
                }
                if (event.key.keysym.sym == SDLK_a) {
                    keyPresses[SDLK_a] = true;
                    break;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    keyPresses[SDLK_d] = true;
                    break;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    rotY -= 1.0f;
                    if (rotY > 360)
                        rotY -= 360;
                    break;
                }
                if (event.key.keysym.sym == SDLK_e) {
                    rotY += 1.0f;
                    if (rotY < -360)
                        rotY += 360;
                    break;
                }
                if (event.key.keysym.sym == SDLK_f) {
                    mode = (mode == GL_LINE) ? GL_FILL : GL_LINE;
                    glPolygonMode(GL_FRONT_AND_BACK, mode);
                    break;
                }
                break;
            case SDL_KEYUP:
                if (keyPresses.at(event.key.keysym.sym) == true) {
                    acceleration = 0.0;
                    velocity = 4.0;
                    counter = 0;
                    keyPresses[event.key.keysym.sym] = false;
                    break;
                }
            case SDL_MOUSEMOTION:
                // event.motion.rel*frameTime to limit speed of rotation
                rotY += event.motion.xrel / 5.0;
                if (rotY > 360)
                    rotY -= 360;
                if (rotY < -360)
                    rotY += 360;
                break;
            default:
                break;
        }
    }
    // allows the mouse events to be processed even when cursor is out of the game window
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

std::string Game::readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint Game::LoadShader(const char *vertex_path, const char *fragment_path) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders
    std::string vertShaderStr = readFile(vertex_path);
    std::string fragShaderStr = readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader
    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);
    std::cout << "yeah" << glGetError() << std::endl;

    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::cout << "yeah" << glGetError() << std::endl;
    if (logLength > 0) {
        std::vector<char> vertShaderError(logLength);
        glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
        std::cout << &vertShaderError[0] << std::endl;
    }


    // Compile fragment shader
    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);


    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        std::vector<char> fragShaderError(logLength);
        glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
        std::cout << &fragShaderError[0] << std::endl;
    }
    std::cout << "Linking program" << std::endl;
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    std::cout << "Program OK" << std::endl;
    return program;
}