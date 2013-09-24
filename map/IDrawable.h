#ifndef IDRAWABLE_H_
#define IDRAWABLE_H_

class IDrawable
{
public:  
  virtual void draw(GLuint program) = 0;
};

#endif