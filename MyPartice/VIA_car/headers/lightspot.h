#ifndef LIGHTSPOT_H
#define LIGHTSPOT_H

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightSpot
{
public:
    LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f));

    glm::vec3 position; // 光源位置
    glm::vec3 angles;   // 光源旋轉角度 (受其主要影響)
    glm::vec3 color;
    glm::vec3 direction = glm::vec3(0, 0, 1.0f); // 光源輻射的方向 (預設為Z軸)

    void UpdateDirection();


    float constant;
    float linear;
    float quadratic;
    float cosPhyInner = 0.9f;  // 內切光角Cos(ϕ)
    float cosPhyOuter = 0.85f; // 外切光角Cos(ϕ)
};

#endif // LIGHTSPOT_H
