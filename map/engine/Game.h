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
    void clean();
    const bool running() { return m_bRunning;}
    void frameEnd();
private:
    std::string readFile(const char *filePath);
    GLuint LoadShader(const char *vertex_path, const char *fragment_path);
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
    double velocity, acceleration;
    int counter;
    IDrawable*      level;
    Emitter*        emitter;
    ShaderUniform* shaderUniform;
    std::map<char,bool> keyPresses;
    std::list<char> supportedKeys;
    // 2D controls    
    TextRenderer* textRenderer;
    MouseState mouseState;
    Control* controlled;
    ListBox* control;
    bool inventoryOn;
};

#endif