#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>
#include <map>
#include "../rendering/textures/TextureFactory.h"
#include "../rendering/TextRenderer.h"
#include "Timer.h"
#include "Level.h"
#include "../rendering/particles/Emitter.h"
#include "../utils/ShaderLoader.h"
#include "Camera.h"
#include "../utils/ShaderUniform.h"
#include "../controls/ListBox.h"
#include "../inputhander/InputHandler.h"
#include "../inputhander/InputState.h"
#include "../model/Mesh.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
/**
 * This is the heart of the system. Responsible for dealing with user input, 
 * rendering (2D/3D) and all game-related actions. 
 */
class Game {
public:
    Game();
    ~Game();
    void frameStart();
    bool init(const char* title, const int flags);
    void render3D();
    void render2D();
    void handleEvents();
    const bool running() { return m_bRunning;}
    void frameEnd();
private:    
    SDL_Window* g_pWindow;
    SDL_GLContext glContext;
    GLuint program;
    bool m_bRunning;
    GLenum mode;
    TextureFactory* txFactory;    
    Timer* timer;
    Camera* camera;
    char* fpsString;
    int counter;
    IDrawable*      level;
    Emitter*        emitter;
    Mesh* mesh;
    ShaderUniform* shaderUniform;
    // 2D controls    
    TextRenderer* textRenderer;
    MouseState mouseState;
    Control* controlled;
    ListBox* control;
    bool inventoryOn;
    InputHandler* inputHandler;

    void initSDL(int &width, int &height);
    void initOpenGL(int width, int height) const;
    void initShaders();
    void initGameResources(int width, int height);
};

#endif