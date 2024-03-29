#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
    LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f));

    glm::vec3 position; // 光源位置
    glm::vec3 angles;   // 光源旋轉角度 (受其主要影響)
    glm::vec3 color;
    glm::vec3 direction = glm::vec3(0, 0, 1.0f); // 光源輻射的方向 (預設為Z軸)

    float constant;
    float linear;
    float quadratic;

};

#endif // LIGHTPOINT_H
