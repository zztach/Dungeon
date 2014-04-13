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
#include "TextureFactory.h"
#include "TextRenderer.h"
#include "Timer.h"
#include "Level.h"
#include "Emitter.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "ShaderUniform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

class Game
{
public: 
	Game();
	~Game();
        void frameStart();
	bool init(const char* title, const int xpos, const int ypos, 
                   const int width, const int height, const int flags);
	void render3D();
        void render2D();
	void handleEvents();
	void clean();
	const bool running() { return m_bRunning; }
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
    TextRenderer* textRenderer;
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
};

#endif