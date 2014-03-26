#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>
#include <map>
#include "TextureFactory.h"
#include "Level.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

class Game
{
public: 
	Game() {
            velocity = 4.0f;
            acceleration = 0.0f;
            counter = 0;
            keyPresses[SDLK_w] = false;
            keyPresses[SDLK_a] = false;
            keyPresses[SDLK_s] = false;
            keyPresses[SDLK_d] = false;            
        }
	~Game() {

        }
	bool init(const char* title, const int xpos, const int ypos, 
                   const int width, const int height, const int flags);
	void render();
	void update() {};
	void handleEvents(float deltaTime);
	void clean();
	// a function to access the private running variable
	const bool running() { return m_bRunning; }

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
    
    float           aspect;
    double velocity, acceleration;
    int counter;
    glm::mat4       proj_matrix;
    IDrawable*      level;
    float           x, z, rotY;
    glm::mat4       mv_matrix_initial;
    glm::mat4       mv_matrix_camera;
    glm::mat4       mv_rot_camera;
    std::map<char,bool> keyPresses;
};

#endif