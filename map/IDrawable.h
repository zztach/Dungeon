#ifndef IDRAWABLE_H_
#define IDRAWABLE_H_

class IDrawable
{
public:  
  virtual void render(GLuint program) = 0;
};

#endif