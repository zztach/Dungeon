#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable
{
public:  
  virtual void render(GLuint program) = 0;
};

#endif