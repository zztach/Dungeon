/* 
 * File:   TextRenderer.h
 * Author: zisis
 *
 * Created on March 31, 2014, 11:25 PM
 */

#ifndef TEXTRENDERER_H
#define	TEXTRENDERER_H

#include "IDrawable.h"
#include "ShaderUniform.h"
#include <string>

class TextRenderer {
public:
    TextRenderer(GLuint fontTexture);
    void bindVAO(); 
    void render(const GLuint program, GLint x, GLint y, std::string text);
    TextRenderer(const TextRenderer& orig);
    virtual ~TextRenderer();
private:
    GLuint vao;
    GLuint buffer;
    GLuint fontTexture;
    GLfloat* vertex_positions;
};

#endif	/* TEXTRENDERER_H */

