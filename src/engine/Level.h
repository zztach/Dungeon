#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../rendering/IDrawable.h"
#include "../utils/ShaderUniform.h"
#include "../rendering/textures/Texture.h"
#include "../model/Mesh.h"


using namespace std;
enum {
    TILE_EMPTY,
    TILE_WALL
};

class Level : public IDrawable {
public :
    Level(Texture *pTexture);

    ~Level();

    void update(void);

    void init();

    // IDrawable
    void bindVAO();

    void render(const GLuint program, const double timeElapsed);

protected:
    void createLevel(void);

private :
    int width;              // # of columns in map.txt
    int height;             // # of lines in map.txt
    char **level;
    vector<string> mapLines;
    Texture *texture;
    Mesh *mesh;
    GLuint buffer;
    GLuint vao;
    GLuint normals_buffer;

    float getXOffset(float cube_side_length, int j) const;

    float getZOffset(float cube_side_length, float initial_distance, int i) const;
};

#endif