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
#include <vmath.h>
#include "Level.h"

// Remove this to draw only a single cube!
//#define MANY_CUBES

class singlepoint_app : public sb6::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Spinny Cube";

        sb6::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void startup()
    {
        static const char * vs_source[] =
        {
            "#version 420 core                                                  \n"
            "                                                                   \n"
			"layout (location = 0) in vec4 position;                            \n"
			"layout (location = 1) in vec4 color;                               \n"
            "                                                                   \n"
            "out VS_OUT                                                         \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "} vs_out;                                                          \n"
            "                                                                   \n"
            "uniform mat4 mv_matrix;                                            \n"
            "uniform mat4 proj_matrix;                                          \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
            "    gl_Position = proj_matrix * mv_matrix * position;              \n"
            "  //vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);		\n"			
			"    vs_out.color = color;											\n"		    
            "}                                                                  \n"
        };

        static const char * fs_source[] =
        {
            "#version 420 core                                                  \n"
            "                                                                   \n"
            "out vec4 color;                                                    \n"
            "                                                                   \n"
            "in VS_OUT                                                          \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "} fs_in;                                                           \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
            "    color = fs_in.color;                                           \n"
            "}                                                                  \n"
        };

		static const char * gs_source[] =
        {
            "#version 420 core                                                  \n"
            "                                                                   \n"
			"layout (trianlges) in;                                             \n"
			"layout (points, max_vertices = 3) out;                             \n"
            "void main(void)                                                    \n"
            "{																	\n"
			"   int i=0;														\n"
			"   for (i=0; i< gl_in[i].length; i++)								\n"
			"   {																\n"
			"		gl_Position = gl_in[i].gl_Position;							\n"
			"		EmitVertex();												\n"
			"   }																\n"
            "}                                                                  \n"
        };

        program = glCreateProgram();
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, fs_source, NULL);
        glCompileShader(fs);

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, vs_source, NULL);
        glCompileShader(vs);

		//GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
        //glShaderSource(gs, 1, gs_source, NULL);
        //glCompileShader(gs);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
		//glAttachShader(program, gs);

        glLinkProgram(program);

        mv_location = glGetUniformLocation(program, "mv_matrix");
        proj_location = glGetUniformLocation(program, "proj_matrix");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
     
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

		level = new Level(8,8);
    }

    virtual void render(double currentTime)
    {
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        static const GLfloat one = 1.0f;

        glViewport(0, 0, info.windowWidth, info.windowHeight);
        glClearBufferfv(GL_COLOR, 0, green);
        glClearBufferfv(GL_DEPTH, 0, &one);

        glUseProgram(program);

        glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

		level->draw(program);
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
        proj_matrix = vmath::perspective(50.0f, aspect, 0.1f, 1000.0f);
    }

private:
    GLuint          program;
    GLuint          vao;

    GLint           mv_location;
    GLint           proj_location;

    float           aspect;
    vmath::mat4     proj_matrix;
	IDrawable*		level;
};

DECLARE_MAIN(singlepoint_app)
