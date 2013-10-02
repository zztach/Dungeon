#include "Level.h"
using namespace std;

Level::Level(int w, int h)
{	
	width = w;
	height = h;

	// create memory for the table that will hold table data
	level = new char*[width];
	for(int i=0; i< width; i++)
	{
		level[i] = new char[height];
	}

	srand (time(NULL));
	// create the level
	createLevel();	
	init();
}

Level::~Level()
{
	for(int i=0 ; i < width; i++)
	{
		delete [] level[i];
	}
	delete [] level;	
    glDeleteBuffers(1, &buffer);
}

void Level::createLevel(void)
{
	string line;
	ifstream mapFile;
	mapFile.open("map.txt");

	int rowNumber = 0;
	while(!mapFile.eof()) 
	{		
		getline(mapFile, line);
		const char *column = line.c_str();
		for(int i=0; i<line.size(); i++)
		{
			if (column[i] == 'X')
				level[rowNumber][i] = TILE_WALL;
			else if (column[i] == 'O')
				level[rowNumber][i] = TILE_EMPTY;
		}
		rowNumber++;
	}

	mapFile.close();

	/*for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			int random = rand() % 100;

			if (y == 0 || y == height-1 || x ==0 || x == width -1)
				level[x][y] = TILE_WALL;
			else {
				if (random < 50 || (x <3 && y < 3) )
					level[x][y] = TILE_EMPTY;
				else 
					level[x][y] = TILE_WALL;
			}
		}
	}*/
}

void Level::init() 
{
	/*static const GLfloat square_vertex_positions[] =
    {
        -0.25f,  0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
         0.25f, -0.25f, -0.25f,

         0.25f, -0.25f, -0.25f,
         0.25f,  0.25f, -0.25f,
        -0.25f,  0.25f, -0.25f             
    };*/

	
    static const GLfloat vertex_positions[] =
    {
        -0.25f,  0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
         0.25f, -0.25f, -0.25f,

         0.25f, -0.25f, -0.25f,
         0.25f,  0.25f, -0.25f,
        -0.25f,  0.25f, -0.25f,

         0.25f, -0.25f, -0.25f,
         0.25f, -0.25f,  0.25f,
         0.25f,  0.25f, -0.25f,
		 
		 0.25f, -0.25f,  0.25f,
         0.25f,  0.25f,  0.25f,
         0.25f,  0.25f, -0.25f,

         0.25f, -0.25f,  0.25f,
        -0.25f, -0.25f,  0.25f,
         0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
        -0.25f,  0.25f,  0.25f,
         0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f, -0.25f,
        -0.25f,  0.25f, -0.25f,
        -0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
         0.25f, -0.25f,  0.25f,
         0.25f, -0.25f, -0.25f,

         0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f,  0.25f,

        -0.25f,  0.25f, -0.25f,
         0.25f,  0.25f, -0.25f,
         0.25f,  0.25f,  0.25f,
		 
		 0.25f,  0.25f,  0.25f,
        -0.25f,  0.25f,  0.25f,
        -0.25f,  0.25f, -0.25f
    };

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER,
                    sizeof(vertex_positions),
                    vertex_positions,
                    GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
}

void Level::draw(GLuint program)
{
	GLuint mv_location = glGetUniformLocation(program, "mv_matrix");
	vmath::mat4 mv_matrix_initial = vmath::translate(0.0f, 15.0f, -25.0f) * vmath::rotate(25.0f, 0.0f, 1.0f, 0.0f)  * vmath::rotate(-25.0f, 1.0f, 0.0f, 0.0f);
	for(int i=0; i < height; i++)
	{
		for(int j=0; j < width; j++)
		{				
			
			if (level[i][j] == TILE_EMPTY) 
			{									
				GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
				vmath::mat4 mv_matrix = mv_matrix_initial * vmath::translate(-(float)width*2.5f/2.0f + (float)j*2.5f, (float)height*2.5f/2.0f - (float)i*2.5f, -34.0f) *										
										vmath::scale(5.0f, 5.0f, 5.0f);
				glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
				glVertexAttrib4fv(1, color);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			} else 
			{
				GLfloat color[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
				vmath::mat4 mv_matrix = mv_matrix_initial * vmath::translate(-(float)width*2.5f/2.0f + (float)j*2.5f, (float)height*2.5f/2.0f - (float)i*2.5f, -34.0f) *										
										vmath::scale(5.0f, 5.0f, 5.0f);
				glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
				glVertexAttrib4fv(1, color);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

		}
	}
}
