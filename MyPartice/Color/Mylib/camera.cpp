#include "camera.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

Camera::Camera(){};
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
    Position = position;
    Worldup = worldup;
    Forward = glm::normalize(target - position);
    Right = glm::normalize(glm::cross(Forward, Worldup));
    Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup){
    Position = position;
    Worldup = worldup;
    Pitch = pitch;
    Yaw = yaw;
    Forward.x = glm::cos(Pitch) * glm::cos(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::sin(Yaw);
    Right = glm::normalize(glm::cross(Forward, Worldup));
    Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::UpdateCameraVectors(){
    Forward.x = glm::cos(Pitch) * glm::cos(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::sin(Yaw);
    Right = glm::normalize(glm::cross(Forward, Worldup));
    Up = glm::normalize(glm::cross(Forward, Right));
}
void Camera::ProcessMouseMovement(float deltaX, float deltaY, GLboolean constrain=true){
    Pitch += deltaY * senseX;
    Yaw += deltaX * senseY;
    UpdateCameraVectors();
    if (constrain){
        if (Pitch > 89.0f){
            Pitch = 89.0f;
        }
        if (Pitch < -89.0f){
            Pitch = -89.0f;
        }
    }
    cout << deltaX << endl;

}

void Camera::ProcessViewMovement(int mode){
    float camX;
    float camZ;
    if (mode == left){
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        Position = glm::vec3(camX, 0, camZ);
        UpdateCameraVectors();
        Forward = -Position;
        Position += Forward * speedZ * senseZ;

    }else if(mode == right){
        float camX = cos(glfwGetTime()) * radius;
        float camZ = sin(glfwGetTime()) * radius;
        Position = glm::vec3(camX, 0, camZ);
        UpdateCameraVectors();
        Forward = -Position;
        Position += Forward * speedZ * senseZ;

    }



}


void Camera::UpdateCameraPos(){
    //    Position += glm::vec3(0, 0, speedZ * senseZ);
    Position += Forward * speedZ * senseZ;
}
glm::mat4 Camera::getViewMatrix(){

    return glm::lookAt(Position, Position + Forward, Worldup);
}
