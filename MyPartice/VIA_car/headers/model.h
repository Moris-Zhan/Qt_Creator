#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <mesh.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdio.h>
#include <stdbool.h>

class Model
{
public:
    Model(string path);
    vector<Mesh> meshes;
    vector<Texture> loaded_textures;
    string directory;
    void draw(GLuint shaderID);
private:
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> processTexture(aiMaterial *mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(const char *path, const string &directory, bool gamma=false);
};

#endif // MODEL_H
