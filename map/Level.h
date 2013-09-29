#ifndef LEVEL_H
#define LEVEL_H

#include <sb6.h>
#include <vmath.h>
#include <list>
#include <time.h>
#include <fstream>
#include <string>
#include "IDrawable.h"

using std::list;
enum 
{
	TILE_EMPTY,
	TILE_WALL
};

class Level : public IDrawable
{
public :
	Level(int width = 4, int height = 4);
	~Level();	
	void update(void);		
	// IDrawable
	void init();
	void draw(GLuint program);
	
protected: 
	void createLevel(void);

private :
	int width;
	int height;
	char** level;		
	GLuint buffer;
};

#endif


//static const GLfloat vertex_positions[] =
//    {
//        -0.25f,  0.25f, -0.25f,
//        -0.25f, -0.25f, -0.25f,
//         0.25f, -0.25f, -0.25f,
//
//         0.25f, -0.25f, -0.25f,
//         0.25f,  0.25f, -0.25f,
//        -0.25f,  0.25f, -0.25f,
//
//         0.25f, -0.25f, -0.25f,
//         0.25f, -0.25f,  0.25f,
//         0.25f,  0.25f, -0.25f,
//
//         0.25f, -0.25f,  0.25f,
//         0.25f,  0.25f,  0.25f,
//         0.25f,  0.25f, -0.25f,
//
//         0.25f, -0.25f,  0.25f,
//        -0.25f, -0.25f,  0.25f,
//         0.25f,  0.25f,  0.25f,
//
//        -0.25f, -0.25f,  0.25f,
//        -0.25f,  0.25f,  0.25f,
//         0.25f,  0.25f,  0.25f,
//
//        -0.25f, -0.25f,  0.25f,
//        -0.25f, -0.25f, -0.25f,
//        -0.25f,  0.25f,  0.25f,
//
//        -0.25f, -0.25f, -0.25f,
//        -0.25f,  0.25f, -0.25f,
//        -0.25f,  0.25f,  0.25f,
//
//        -0.25f, -0.25f,  0.25f,
//         0.25f, -0.25f,  0.25f,
//         0.25f, -0.25f, -0.25f,
//
//         0.25f, -0.25f, -0.25f,
//        -0.25f, -0.25f, -0.25f,
//        -0.25f, -0.25f,  0.25f,
//
//        -0.25f,  0.25f, -0.25f,
//         0.25f,  0.25f, -0.25f,
//         0.25f,  0.25f,  0.25f,
//
//         0.25f,  0.25f,  0.25f,
//        -0.25f,  0.25f,  0.25f,
//        -0.25f,  0.25f, -0.25f
//    };
