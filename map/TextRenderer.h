/* 
 * File:   TextRenderer.h
 * Author: zisis
 *
 * Created on March 31, 2014, 11:25 PM
 */

#ifndef TEXTRENDERER_H
#define	TEXTRENDERER_H

#include "IDrawable.h"

class TextRenderer : public IDrawable {
public:
    TextRenderer();
    virtual void bindVAO(); 
    virtual void render(const GLuint program, const double timeElapsed);
    TextRenderer(const TextRenderer& orig);
    virtual ~TextRenderer();
private:
    GLuint vao;
    GLuint buffer;
    GLfloat* vertex_positions;
};

#endif	/* TEXTRENDERER_H */

