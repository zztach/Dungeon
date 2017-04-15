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
    this->mesh = new Mesh();
    createLevel();
}

Level::~Level() {
    for (int i = 0; i < width; i++) {
        delete[] level[i];
    }
    delete[] level;
    delete mesh;
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
    vector<Vertex> vertex_positions = mesh->load("models/crate.obj");

    // load vertex positions into the buffer, input to vertex attributes 0,3
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_positions.size() * sizeof(Vertex), &vertex_positions[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


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

    // generate walls
    float cube_side_length = 2.0f;
    float initial_distance = -24.0f;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (level[i][j] == TILE_WALL) {
                GLfloat color[] = {1.0f, 1.0f, 0.0f, 1.0f};
                //  map_width_center + current_cube_x,  0,  map_height_center - current_cube_y
                float x = getXOffset(cube_side_length, j);
                float z = getZOffset(cube_side_length, initial_distance, i);
                glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z));
                // rotate as first matrix operation rotates each cube around its axis. Interesting for effect
                glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
                glVertexAttrib4fv(3, color);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }

    // generate floor
    for (int i = -1; i < height + 1; i++) {
        for (int j = -1; j < width + 1; j++) {
            GLfloat color[] = {0.9f, 0.9f, 0.9f, 0.0f};
            float x = getXOffset(cube_side_length, j);
            float y = 0.0f;
            float z = getZOffset(cube_side_length, initial_distance, i);

            glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
            glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
            glVertexAttrib4fv(3, color);
            glDrawArrays(GL_TRIANGLES, 18, 6);

            y = -2.0f;
            mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
            glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
            glVertexAttrib4fv(3, color);
            glDrawArrays(GL_TRIANGLES, 18, 6);
        }
    }
}

float Level::getXOffset(float cube_side_length, int j) const {
    return -(float) width * cube_side_length / cube_side_length + (float) j * cube_side_length;
}

float Level::getZOffset(float cube_side_length, float initial_distance, int i) const {
    return initial_distance - (float) height * cube_side_length / cube_side_length - (float) i * cube_side_length;
}