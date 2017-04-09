//
// Created by zisis on 9/4/2017.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Mesh.h"

const string Mesh::VERTEX_HEADER = "v ";
const string Mesh::TEXTURE_HEADER = "vt";
const string Mesh::NORMAL_HEADER = "vn";
const string Mesh::FACE_HEADER = "f ";

Mesh::Mesh() {

}

Mesh::~Mesh() {

}

void Mesh::load(const std::string &fileName) {
    ifstream objFile(fileName);
    vector<glm::vec3> verticesList;
    vector<glm::vec2> uvList;
    vector<Vertex> vertices;

    cout << "Loading " << fileName << endl;
    string line;
    while (getline(objFile, line)) {
        if (line.substr(0, 2) == VERTEX_HEADER) {
            cout << line << endl;
            istringstream coordinates(line.substr(VERTEX_HEADER.size()));
            glm::vec3 vertex;
            coordinates >> vertex.x;
            coordinates >> vertex.y;
            coordinates >> vertex.z;
            verticesList.push_back(vertex);
        } else if (line.substr(0, 2) == TEXTURE_HEADER) {
            istringstream uvs(line.substr(TEXTURE_HEADER.size()));
            glm::vec2 uvPair;
            uvs >> uvPair.s;
            uvs >> uvPair.t;
            uvList.push_back(uvPair);
        } else if (line.substr(0, 2) == NORMAL_HEADER) {

        } else if (line.substr(0, 2) == FACE_HEADER) {
            cout << line << endl;

            int vertexIdx[3];
            int textureIdx[3];
            int normalIdx[3];
            string triplet;

            istringstream faceVertices(line.substr(FACE_HEADER.size()));
            for (int i = 0; i < 3; i++) {
                faceVertices >> triplet;
                vector<int> indices = readTriplet(triplet);
                vertexIdx[i] = indices[0];
                textureIdx[i] = indices[1];
                normalIdx[i] = indices[2];

                glm::vec3 pos = verticesList[vertexIdx[i] -1];
                glm::vec2 tex = uvList[textureIdx[i] -1];
                glm::vec3 normal;

                Vertex vertex = Vertex(pos, tex, normal);
                vertices.push_back(vertex);
            }
        }

    }

    cout << vertices.size() << endl;
    objFile.close();
}

vector<int> Mesh::readTriplet(string &triplet) {
    vector<int> indices;
    stringstream ss(triplet);
    string test;

    while (getline(ss, test, '/')) {
        indices.push_back(stoi(test));
    }

    return indices;
}

Vertex::Vertex(const glm::vec3 &pos, const glm::vec2 &tex, const glm::vec3 &normal) : pos(pos), tex(tex),
                                                                                      normal(normal) {}
