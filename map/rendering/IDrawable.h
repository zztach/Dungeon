#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <glew.h>
#include "IDrawable.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

class IDrawable
{
public:      
    virtual void bindVAO() = 0; 
    virtual void render(const GLuint program, const double timeElapsed) = 0;
};

#endif