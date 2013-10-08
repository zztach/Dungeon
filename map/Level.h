#ifndef LEVEL_H
#define LEVEL_H

#include <sb6.h>
#include <vmath.h>
#include <list>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include "IDrawable.h"

using namespace std;
enum 
{
	TILE_EMPTY,
	TILE_WALL
};

class Level : public IDrawable
{
public :
	Level();
	~Level();	
	void update(void);		
	// IDrawable
	void init();
	void render(GLuint program);
	
protected: 
	void createLevel(void);

private :
	int width;
	int height;	
	char** level;
	vector<string> mapLines;
	GLuint buffer;
	GLuint normals_buffer;
};

#endif