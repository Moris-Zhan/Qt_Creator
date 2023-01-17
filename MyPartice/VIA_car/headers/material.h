#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
    unsigned int shader;
    glm::vec3 ambient;
//    glm::vec3 diffuse;
    unsigned int diffuse;
//    glm::vec3 specular;
    unsigned int specular;
    unsigned int emission;
    float shininess;

    Material(unsigned int _shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, unsigned int _emission, float _shininess);
};

#endif // MATERIAL_H
