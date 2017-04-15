//
// Created by zisis on 9/4/2017.
//

#ifndef DUNGEON_MESH_H
#define DUNGEON_MESH_H

using namespace std;

#include <glm.hpp>
#include <string>
#include <fstream>

struct Vertex {
    glm::vec3 pos;
    glm::vec2 tex;
    glm::vec3 normal;

    Vertex(const glm::vec3 &pos, const glm::vec2 &tex, const glm::vec3 &normal);
};

class Mesh {
public:
    Mesh();
    virtual ~Mesh();
    vector<Vertex> load(const std::string& fileName);

private:
    static const string VERTEX_HEADER;
    static const string TEXTURE_HEADER;
    static const string NORMAL_HEADER;
    static const string FACE_HEADER;

    vector<int> readTriplet(string &triplet);
};


#endif //DUNGEON_MESH_H
