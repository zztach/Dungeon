#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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