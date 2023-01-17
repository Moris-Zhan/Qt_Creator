#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <vector>
#include <shader.h>
using namespace std;

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture{
    unsigned int id;
    string type;
    string path;
};


class Mesh
{
public:
    Mesh(float vertices[]);
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    // mesh data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    void draw(GLuint shaderID);

private:
    //  render data
    unsigned int VAO, VBO, EBO;
    void setupMesh();

};

#endif // MESH_H
