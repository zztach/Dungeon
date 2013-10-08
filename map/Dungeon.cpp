/*
 * Copyright © 2012-2013 Graham Sellers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <sb6.h>
#include <shader.h>
#include <vmath.h>
#include "Level.h"

class Dungeon : public sb6::application
{
    void init()
    {
        static const char title[] = "Dungeon - OpenGL SuperBible";

        sb6::application::init();

        memcpy(info.title, title, sizeof(title));
    }

	void onKey(int key, int action)
	{
		if (action)
		{
			switch (key)
			{
				case 'W':
					z += 1.0f;
					break;				
				case 'S':
					z -= 1.0f;
					break;
				case 'D':
					x -= 1.0f;
					break;
				case 'A':
					x += 1.0f;
					break;    
			}
		}
    
	}

    virtual void startup()
    {        
        program = glCreateProgram();
 
        GLuint fs = sb6::shader::load("fragment_shader.fg", GL_FRAGMENT_SHADER);
        GLuint vs = sb6::shader::load("vertex_shader.vs", GL_VERTEX_SHADER);
        
        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        mv_location = glGetUniformLocation(program, "mv_matrix");
        proj_location = glGetUniformLocation(program, "proj_matrix");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
     
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);		

		level = new Level();
		x = z = 0.0f;
		
    }

    virtual void render(double currentTime)
    {			
		// store the "initial camera" matrix
		mv_matrix_initial = vmath::translate(15.0f + x, 15.0f, -25.0f + z) * vmath::rotate(25.0f, 0.0f, 1.0f, 0.0f)  * vmath::rotate(-25.0f, 1.0f, 0.0f, 0.0f);		
		GLuint mv_location = glGetUniformLocation(program, "mv_matrix");
		glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix_initial);

        static const GLfloat gray[] = { 0.6f, 0.6f, 0.6f, 1.0f };
        static const GLfloat one = 1.0f;

        glViewport(0, 0, info.windowWidth, info.windowHeight);
        glClearBufferfv(GL_COLOR, 0, gray);
        glClearBufferfv(GL_DEPTH, 0, &one);

        glUseProgram(program);

        glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

		level->render(program);
	}

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
		delete level;
    }

    void onResize(int w, int h)
    {
        sb6::application::onResize(w, h);

        aspect = (float)w / (float)h;
        proj_matrix = vmath::perspective(45.0f, aspect, 0.1f, 100.0f);
    }

private:
    GLuint          program;
    GLuint          vao;
	
    GLint           mv_location;
    GLint           proj_location;

    float           aspect;
    vmath::mat4     proj_matrix;
	IDrawable*		level;
	float			x, z;
	vmath::mat4		mv_matrix_initial;
};

DECLARE_MAIN(Dungeon)
