#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
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
	Game() {}
	~Game() {}
	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update() {};
	void handleEvents();
	void clean();
	// a function to access the private running variable
	bool running() { return m_bRunning; }

private:
	std::string readFile(const char *filePath);
	GLuint LoadShader(const char *vertex_path, const char *fragment_path);
private:
	SDL_Window* g_pWindow;
	SDL_GLContext glContext;
	GLuint          vao;
	GLuint program;
	bool m_bRunning;

    GLint           mv_location;
    GLint           proj_location;
	GLint			light_pos;

    float           aspect;
    glm::mat4       proj_matrix;
	IDrawable*		level;
	float			x, z, rotY;
	glm::mat4		mv_matrix_initial;
	glm::mat4		mv_matrix_camera;
	glm::mat4		mv_rot_camera;
};

#endif