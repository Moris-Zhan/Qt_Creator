#include "model.h"

//Texture
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(string path)
{
    loadModel(path);
}

void Model::loadModel(string path){
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));
    cout << "Success!" << directory << endl;

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    cout << node->mName.data << endl;  // print node name
    // process each mesh located at the current node
    for (unsigned int i = 0 ; i< node->mNumMeshes; i++){
        aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(curMesh, scene));
    }

    // recursively process each of the children nodes
    for (unsigned int i =0; i<node->mNumChildren;i++){
        processNode(node->mChildren[i], scene);
    }

}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    vector<Vertex> tempvertices;
    vector<unsigned int> tempindices;
    vector<Texture> temptextures;

    glm::vec3 tempVec;
    for (unsigned int i = 0 ; i<mesh->mNumVertices; i++){
        Vertex tempVertex;
        // positions
        tempVertex.Position.x = mesh->mVertices[i].x;
        tempVertex.Position.y = mesh->mVertices[i].y;
        tempVertex.Position.z = mesh->mVertices[i].z;
        // normals
        tempVertex.Normal.x = mesh->mNormals[i].x;
        tempVertex.Normal.y = mesh->mNormals[i].y;
        tempVertex.Normal.z = mesh->mNormals[i].z;
        // texture coordinates
        if (mesh->mTextureCoords[0]){
            tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
            tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
        }else{
            tempVertex.TexCoords = glm::vec2(0,0);
        }
        tempvertices.push_back(tempVertex);
    }

    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0 ; i<mesh->mNumFaces; i++){
        for (unsigned int j =0; j < mesh->mFaces[i].mNumIndices;j++) {
            tempindices.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }

    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // 1. diffuse maps
    vector<Texture> diffuseMaps = processTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
    temptextures.insert(temptextures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = processTexture(material, aiTextureType_SPECULAR, "texture_specular");
    temptextures.insert(temptextures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = processTexture(material, aiTextureType_HEIGHT, "texture_normal");
    temptextures.insert(temptextures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = processTexture(material, aiTextureType_AMBIENT, "texture_height");
    temptextures.insert(temptextures.end(), heightMaps.begin(), heightMaps.end());


    return Mesh(tempvertices, tempindices, temptextures);
//    return Mesh(tempvertices, tempindices, {});
}

vector<Texture> Model::processTexture(aiMaterial *mat, aiTextureType type, string typeName){
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str); // 通過GetTexture函數獲取每個紋理的文件位置，這個位置以aiString類型儲存
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < loaded_textures.size(); j++)
        {
            if(std::strcmp(loaded_textures[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(loaded_textures[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            loaded_textures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const string &directory, bool gamma){
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    // print texture image name
    cout << filename << endl;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Model::draw(GLuint shaderID){
    for (unsigned int i =0 ; i < meshes.size();i++){
        meshes[i].draw(shaderID);
    }
}
