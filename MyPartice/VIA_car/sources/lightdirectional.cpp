#include "lightdirectional.h"

LightDirectional::LightDirectional(){}

LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
    position(_position), angles(_angles), color(_color)
{
    updateDirection();
}

void LightDirectional::updateDirection(){
    direction = glm::vec3(0.0f,0.0f,1.0f); // unit vector // pointing to z (forward)
    direction = glm::rotateZ(direction, angles.z);
    direction = glm::rotateX(direction, angles.x);
    direction = glm::rotateY(direction, angles.y);
    direction = -1.0f * direction;  // calculate invert direction to Light (FragShader)
}
