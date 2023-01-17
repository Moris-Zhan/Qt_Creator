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
    Up = glm::normalize(glm::cross(Right,Forward));
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
    Up = glm::normalize(glm::cross(Right,Forward));
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
//    cout << deltaX << endl;

}

void Camera::HorizonViewMovement(int mode){
    if (mode == left){
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        Position = glm::vec3(camX, 0, camZ);

        Forward = -Position;


    }else if(mode == right){
        float camX = cos(glfwGetTime()) * radius;
        float camZ = sin(glfwGetTime()) * radius;
        Position = glm::vec3(camX, 0, camZ);

        Forward = -Position;

    }
}

void Camera::VerticViewMovement(int mode){
    if (mode == up){
        float camY = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        Position = glm::vec3(0, camY, camZ);

        Forward = -Position;


    }else if(mode == down){
        float camY = cos(glfwGetTime()) * radius;
        float camZ = sin(glfwGetTime()) * radius;
        Position = glm::vec3(0, camY, camZ);

        Forward = -Position;

    }
}


void Camera::UpdateCameraPos(){
    //    Position += glm::vec3(0, 0, speedZ * senseZ);
    Position += (Forward * speedZ * 0.1f) + (Right * speedX * 0.1f) + (Up * speedY * 0.1f);
}
glm::mat4 Camera::getViewMatrix(){

    return glm::lookAt(Position, Position + Forward, Worldup);
}
