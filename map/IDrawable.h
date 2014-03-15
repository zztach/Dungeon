#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable
{
public:      
    virtual void bindVAO() = 0; 
    virtual void render(const GLuint program) = 0;
};

#endif