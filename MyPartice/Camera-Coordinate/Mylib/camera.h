#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Camera
{
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
    Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);

    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 Worldup;
    float Pitch;
    float Yaw;
    float senseX = 0.001;
    float senseY = 0.001;
    float senseZ = 0.5f;
    float speedZ = 0;
    float radius = 10.0f;

    float left = -1;
    float right = 1;

    void ProcessMouseMovement(float deltaX, float deltaY,GLboolean constrain);
    void ProcessViewMovement(int mode);
    void UpdateCameraPos();
    glm::mat4 getViewMatrix();

private:
    void UpdateCameraVectors();
};

#endif // CAMERA_H
