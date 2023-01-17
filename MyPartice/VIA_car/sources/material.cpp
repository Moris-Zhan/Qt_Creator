#include "material.h"

Material::Material(unsigned int _shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, unsigned int _emission, float _shininess):
    shader(_shader), ambient(_ambient), diffuse(_diffuse), specular(_specular), emission(_emission), shininess(_shininess)
{

}
