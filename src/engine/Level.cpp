#include "Level.h"

Level::Level(Texture *tex) {
    std::string line;
    ifstream mapFile;
    mapFile.open("map.txt");

    int rowNumber = 0;
    while (!mapFile.eof()) {
        getline(mapFile, line);
        mapLines.push_back(line);
        rowNumber++;
    }
    mapFile.close();

    width = mapLines.at(0).size();
    height = rowNumber;

    // create memory for the table that will hold table data
    level = new char *[width];
    for (int i = 0; i < width; i++) {
        level[i] = new char[height];
    }

    srand(time(NULL));
    texture = tex;
    createLevel();
    //init();
}

Level::~Level() {
    for (int i = 0; i < width; i++) {
        delete[] level[i];
    }
    delete[] level;
    glDeleteBuffers(1, &buffer);
    glDeleteBuffers(1, &normals_buffer);
    glDeleteVertexArrays(1, &vao);
}

void Level::createLevel(void) {
    int rowNumber = 0;
    for (std::vector<string>::iterator row = mapLines.begin(); row != mapLines.end(); ++row) {
        const char *columns = (*row).c_str();

        for (int i = 0; i < (*row).size(); i++) {
            if (columns[i] == 'X')
                level[rowNumber][i] = TILE_WALL;
            else if (columns[i] == 'O')
                level[rowNumber][i] = TILE_EMPTY;
        }
        rowNumber++;
    }

}

void Level::init() {
    static const GLfloat vertex_positions[] = {
            // back face
            -5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 0.0f, 0.0f,
            -5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 1.0f,
            5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 1.0f, 1.0f,

            5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 0.0f,
            5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 0.0f, 1.0f,
            -5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 1.0f, 1.0f,

            // right face
            5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 1.0f,
            5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 0.0f, 0.0f,
            5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 1.0f, 1.0f,

            5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 0.0f, 0.0f,
            5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 0.0f, 1.0f,
            5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 1.0f, 1.0f,

            // front face
            // bottom triangle
            5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 0.0f, 1.0f,
            -5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 0.0f, 0.0f,
            5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 1.0f, 1.0f,

            // upper triangle
            -5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 0.0f, 0.0f,
            -5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 0.0f, 1.0f,
            5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 1.0f, 1.0f,

            // left face
            -5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 0.0f, 1.0f,
            -5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 0.0f,
            -5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 1.0f, 1.0f,

            -5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 0.0f,
            -5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 0.0f, 1.0f,
            -5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 1.0f, 1.0f,

            // bottom face
            -5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 1.0f, 0.0f,
            5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 0.0f, 0.0f,
            5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 1.0f,

            5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 0.0f,
            -5 * 0.25f, -5 * 0.25f, -5 * 0.25f, 0.0f, 1.0f,
            -5 * 0.25f, -5 * 0.25f, 5 * 0.25f, 1.0f, 1.0f,

            // up face
            -5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 1.0f, 0.0f,
            5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 0.0f, 0.0f,
            5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 0.0f, 1.0f,

            5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 0.0f, 0.0f,
            -5 * 0.25f, 5 * 0.25f, 5 * 0.25f, 0.0f, 1.0f,
            -5 * 0.25f, 5 * 0.25f, -5 * 0.25f, 1.0f, 1.0f,
    };

    static const GLfloat vertex_normals[] = {
            // back face
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

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

    // load vertex positions into the buffer, input to vertex attributes 0,3
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);

    // load vertex normals into another buffer, input to vertex attribute 2
    glGenBuffers(1, &normals_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normals_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_normals), vertex_normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
}

void Level::bindVAO() {
    glGenVertexArrays(1, &vao); // Create our Vertex Array Object  
    glBindVertexArray(vao); // Bind our Vertex Array Object so we can use it  

    init();

    glBindVertexArray(0);
}

void Level::render(const GLuint program, const double timeElapsed) {
    GLuint mv_location = ShaderUniform::getInstance(program)->get("mv_matrix");
    glBindTexture(GL_TEXTURE_2D, texture->getTexture());

    glBindVertexArray(vao);
    // iterating the lines of map.txt
    for (int i = 0; i < height; i++) {
        // iterating the columns of map.txt
        for (int j = 0; j < width; j++) {
            if (level[i][j] == TILE_WALL) {
                GLfloat color[] = {1.0f, 1.0f, 0.0f, 1.0f};
                //                                                                   map_width_center + currect_cube_x,           0  ,            map_height_center - current_cube_y                       
                glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f),
                                                     glm::vec3(-(float) width * 2.5f / 2.0f + (float) j * 2.5f, 0.0f,
                                                               -34.0f - (float) height * 2.5f / 2.0f -
                                                               (float) i * 2.5f));
                // rotate as first matrix operation rotates each cube around its axis. Interesting for effect
                glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
                glVertexAttrib4fv(2, color);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }

    // generate floor
    for (int i = -height; i < height; i++) {
        for (int j = -width; j < width; j++) {
            GLfloat color[] = {0.9f, 0.9f, 0.9f, 0.0f};
            glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f),
                                                 glm::vec3(-(float) width * 2.5f / 2.0f + (float) j * 2.5f, -2.5f,
                                                           -34.0f - (float) height * 2.5f / 2.0f - (float) i * 2.5f));
            glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
            glVertexAttrib4fv(2, color);
            glDrawArrays(GL_TRIANGLES, 30, 6);
        }
    }
}
