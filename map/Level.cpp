#include "Level.h"

Level::Level()
{				
	std::string line;	
	ifstream mapFile;
	mapFile.open("map.txt");

	int rowNumber = 0;	
	while(!mapFile.eof()) 
	{				
		getline(mapFile, line);						
		mapLines.push_back(line);
		rowNumber++;
	}
	mapFile.close();	

	width = mapLines.at(0).size();
	height = rowNumber;
	
	// create memory for the table that will hold table data
	level = new char*[width];
	for(int i=0; i< width; i++)
	{
		level[i] = new char[height];
	}

	srand (time(NULL));

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
	int rowNumber = 0;
	for(std::vector<string>::iterator row = mapLines.begin(); row != mapLines.end(); ++row) {
		const char *columns = (*row).c_str();		

		for(int i=0; i<(*row).size(); i++)
		{
			if (columns[i] == 'X')
				level[rowNumber][i] = TILE_WALL;
			else if (columns[i] == 'O')
				level[rowNumber][i] = TILE_EMPTY;
		}
		rowNumber++;
	}	

}

void Level::init() 
{		
    static const GLfloat vertex_positions[] =
    {
	    // back face
        -5*0.25f,  5*0.25f, -5*0.25f,
        -5*0.25f, -5*0.25f, -5*0.25f,
         5*0.25f, -5*0.25f, -5*0.25f,

         5*0.25f, -5*0.25f, -5*0.25f,
         5*0.25f,  5*0.25f, -5*0.25f,
        -5*0.25f,  5*0.25f, -5*0.25f,

		// right face
         5*0.25f, -5*0.25f, -5*0.25f,
         5*0.25f, -5*0.25f,  5*0.25f,
         5*0.25f,  5*0.25f, -5*0.25f,
		 
		 5*0.25f, -5*0.25f,  5*0.25f,
         5*0.25f,  5*0.25f,  5*0.25f,
         5*0.25f,  5*0.25f, -5*0.25f,

		 // front face
         5*0.25f, -5*0.25f,  5*0.25f,
        -5*0.25f, -5*0.25f,  5*0.25f,
         5*0.25f,  5*0.25f,  5*0.25f,

        -5*0.25f, -5*0.25f,  5*0.25f,
        -5*0.25f,  5*0.25f,  5*0.25f,
         5*0.25f,  5*0.25f,  5*0.25f,

		 // left face
        -5*0.25f, -5*0.25f,  5*0.25f,
        -5*0.25f, -5*0.25f, -5*0.25f,
        -5*0.25f,  5*0.25f,  5*0.25f,

        -5*0.25f, -5*0.25f, -5*0.25f,
        -5*0.25f,  5*0.25f, -5*0.25f,
        -5*0.25f,  5*0.25f,  5*0.25f,

		 // bottom face
        -5*0.25f, -5*0.25f,  5*0.25f,
         5*0.25f, -5*0.25f,  5*0.25f,
         5*0.25f, -5*0.25f, -5*0.25f,

         5*0.25f, -5*0.25f, -5*0.25f,
        -5*0.25f, -5*0.25f, -5*0.25f,
        -5*0.25f, -5*0.25f,  5*0.25f,

		 // up face
        -5*0.25f,  5*0.25f, -5*0.25f,
         5*0.25f,  5*0.25f, -5*0.25f,
         5*0.25f,  5*0.25f,  5*0.25f,
		 
		 5*0.25f,  5*0.25f,  5*0.25f,
        -5*0.25f,  5*0.25f,  5*0.25f,
        -5*0.25f,  5*0.25f, -5*0.25f
    };

	static const GLfloat vertex_normals[] =
    {
	     // back face
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,

         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,

		 // right face
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
		 
		 1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,

		 // front face
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,

         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,

		 // left face
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

		 // bottom face
         0.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,

         0.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,

		 // up face
         0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
		 
		 0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
    };

	// load vertex positions into the buffer, input to vertex attribute 0
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

	// load vertex normals into another buffer, input to vertex attribute 2
	glGenBuffers(1, &normals_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normals_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_normals), vertex_normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
}

void Level::render(GLuint program)
{
	GLuint mv_location = glGetUniformLocation(program, "mv_matrix");		
	
	for(int i=0; i < height; i++)
	{
		for(int j=0; j < width; j++)
		{				
			
			if (level[i][j] == TILE_EMPTY) 
			{									
				GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
				glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(float)width*2.5f/2.0f + (float)j*2.5f, -2.5f, -34.0f -(float)height*2.5f/2.0f - (float)i*2.5f));																				
				glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
				glVertexAttrib4fv(2, color);
				// draw only the upper face of the cube and translate it -2.5 on the y axis in order to get the floor ;)
				glDrawArrays(GL_TRIANGLES, 30, 6);
			} 
			else 
			{
				GLfloat color[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
				glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(float)width*2.5f/2.0f + (float)j*2.5f, 0.0f, -34.0f -(float)height*2.5f/2.0f - (float)i*2.5f));										
				// rotate as first matrix operation rotates each cude around its axis. Interesting for effect
				glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
				glVertexAttrib4fv(2, color);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

		}
	}
}
