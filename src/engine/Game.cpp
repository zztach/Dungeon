#include <SDL_video.h>
#include "Game.h"
#include "../rendering/TextRenderer.h"
#include "../model/Mesh.h"

Game::Game() {
    counter = 0;
    fpsString = new char[100];
    controlled = NULL;
    inventoryOn = false;
    mode = GL_FILL;
}

bool Game::init(const char *title, const int flags) {
    int width = 1024;
    int height = 768;

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        initSDL(width, height);
    } else {
        return 1;
    }

    initOpenGL(width, height);
    initShaders();
    initGameResources(width, height);

    m_bRunning = true;
    return true;
}

void Game::initSDL(int &width, int &height) {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Declare display mode structure to be filled in.
    SDL_DisplayMode modeInUse;

    // Get current display mode of all displays.
    for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
        SDL_DisplayMode current;
        int errorCode = SDL_GetCurrentDisplayMode(i, &current);

        if (errorCode != 0)
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
        else
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h,
                    current.refresh_rate);

        if (modeInUse.w == 0 || current.w > modeInUse.w) {
            modeInUse = current;
            width = current.w;
            height = current.h;
        }
    }

    // if succeeded create our window
    g_pWindow = SDL_CreateWindow("Dungeon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                 SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Create an OpenGL context associated with the window.
    glContext = SDL_GL_CreateContext(g_pWindow);
    if (glContext != NULL)
        cout << "GL Context setup properly" << endl;
}

void Game::initOpenGL(int width, int height) const {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    /* CULLING : Enable culling of back-facing triangles. Front-facing triangles have CW winding order. Culling takes
       CULLING : place after the vertex shader stage and before sending pixels down the pipeline for rasterization */
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    /* DEPTH_TEST : Reads the depth value of a fragment (z-coordinate) from the depth buffer at the current's fragment
       DEPTH_TEST : coordinate and compares it to the generated depth value of the fragment currently being processed
       DEPTH_TEST : Those who have lessOrEqual Z values pass the test and are written to the depth buffer */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    /* BLENDING : Determines final color by combining "source*GL_SRC_ALPHA" and "dest*GL_ONE" using a "blend equation"*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    /* VIEWPORT : Transforms the normalized device coordinates to window ones */
    glViewport(0, 0, width, height);
}

void Game::initShaders() {
    particle_shader = ShaderLoader::load("shaders/particle_vertex_shader.vert", "shaders/fragment_shader.frag");
    program = ShaderLoader::load("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");
    glUseProgram(program);
    shaderUniform = ShaderUniform::getInstance(program);
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Game::initGameResources(int width, int height) {
    inputHandler = new InputHandler();
    txFactory = new TextureFactory();
    txFactory->loadTextures();
    timer = new Timer();
    camera = new Camera(width, height);

    level = new Level(txFactory->getTexture("crate"));
    level->bindVAO();

    textRenderer = new TextRenderer(txFactory->getTexture("font")->getTexture());
    textRenderer->bindVAO();

    emitter = new Emitter(particle_shader);
    emitter->setTexture(txFactory->getTexture("particle"));

    control = new ListBox(5, 15, 150, 300);
    control->bindVAO();
}

void Game::frameStart() {
    timer->tick();
}

void Game::render3D() {
    static const GLfloat gray[] = {0.5f, 0.5f, 0.5f, 1.0f};
    static const GLfloat one = 1.0f;

    glClearBufferfv(GL_COLOR, 0, gray);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUniformMatrix4fv(shaderUniform->get("camera_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getMatrix()));
    glUniformMatrix4fv(shaderUniform->get("proj_matrix"), 1, GL_FALSE,
                       glm::value_ptr(camera->getPerpsectiveProjection()));

    // w=0.0 equals directional light (sunlight), while w=1.0 equals positional light    
    glm::vec4 light = glm::vec4(0.0, 20.0, 15.0, 0.0f);
    glUniform4fv(shaderUniform->get("light_pos"), 1, glm::value_ptr(light));

    level->render(program, timer->getInGameFrameDuration());

    glUseProgram(particle_shader);

    glUniformMatrix4fv(glGetUniformLocation(particle_shader, "camera_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(particle_shader, "proj_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getPerpsectiveProjection()));

    emitter->update(timer->getInGameFrameDuration(), camera->getRotation());


    glUseProgram(program);
}

void Game::render2D() {
    glUniformMatrix4fv(shaderUniform->get("proj_matrix"), 1, GL_FALSE, glm::value_ptr(camera->getOrthoProjection()));
    glUniformMatrix4fv(shaderUniform->get("camera_matrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    sprintf(fpsString, "FPS: %d", timer->getFPS());
    textRenderer->render(program, 0, 0, fpsString);
    if (inventoryOn) {
        control->update(mouseState);
        control->render(program, timer->getInGameFrameDuration());
    }
}

void Game::frameEnd() {
    SDL_GL_SwapWindow(g_pWindow);
    SDL_GL_SetSwapInterval(0);
}

void Game::handleEvents() {
    InputState *state = inputHandler->handleInput();
    MouseState mouseState = state->getMouseState();
    map<char, KeyState *> keyState = state->getKeyboardState();

    camera->process(keyState, mouseState, timer->getInGameFrameDuration());

    if (keyState[SDLK_f]->pressed && !keyState[SDLK_f]->consumed) {
        mode = (mode == GL_LINE) ? GL_FILL : GL_LINE;
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        keyState[SDLK_f]->consumed = true;
    }

    if (keyState[SDLK_TAB]->pressed && !keyState[SDLK_TAB]->consumed) {
        inventoryOn = !inventoryOn;
        keyState[SDLK_TAB]->consumed = true;
    }

    if (keyState[SDLK_ESCAPE]->pressed) {
        m_bRunning = false;
    }
}


Game::~Game() {
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
    delete mesh;
    if (glContext) SDL_GL_DeleteContext(glContext);
    if (g_pWindow) SDL_DestroyWindow(g_pWindow);

    // clean up SDL
    SDL_Quit();
}
