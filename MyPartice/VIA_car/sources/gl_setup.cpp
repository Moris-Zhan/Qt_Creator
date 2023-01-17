#include "gl_setup.h"
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

#include <lightdirectional.h>

// 第一步是計算鼠標自上一幀的偏移量。我們必須先在程序中儲存上一幀的鼠標位置，我們把它的初始值設置為屏幕的中心：

float lastX = 1024/2;
float lastY = 768/2;
bool firstMouse = true; // 使用一個bool變量檢驗我們是否是第一次獲取鼠標輸入
Camera camera;

void Gl_Setup::framebuffer_size_callback(GLFWwindow* window, int width, int height) // resize glfw window
{
    glViewport(0, 0, width, height);
}

void Gl_Setup::mouse_callback(GLFWwindow* window, double xPos, double yPos){

    if(firstMouse) // 这个bool变量初始时是设定为true的
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    // xpos和ypos代表當前鼠標的位置
    float deltaX = xPos - lastX;
    float deltaY = - (yPos - lastY); // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(deltaX,deltaY, GL_TRUE);
}

void Gl_Setup::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    int mode;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        mode = -1;
        camera.HorizonViewMovement(mode);
    }else if (glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        mode = 1;
        camera.HorizonViewMovement(mode);
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        mode = -1;
        camera.VerticViewMovement(mode);
    }else if (glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        mode = 1;
        camera.VerticViewMovement(mode);
    }

    if (glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){
        camera.speedX = 1.0f;
    }else if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){
        camera.speedX = -1.0f;
    }else {
        camera.speedX = 0.0f;
    }


    if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){
        camera.speedY = 1.0f;
    }else if (glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){
        camera.speedY = -1.0f;
    }else {
        camera.speedY = 0.0f;
    }

    camera.UpdateCameraPos();

}

void Gl_Setup::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.speedZ = float(yoffset);
    camera.UpdateCameraPos();
}

Gl_Setup::Gl_Setup(Camera _camera)
{
    camera = _camera;
}

Camera Gl_Setup::getCamera(){
    return camera;
}

GLFWwindow* Gl_Setup::windowSetup(){
    // Open a window and create its OpenGL context
    GLFWwindow* window;

    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        //        return -1;
        return window;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        //        return -1;
        return window;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 告訴GLFW，它應該隱藏光標，並捕捉(Capture)它
    glfwSetCursorPosCallback(window, mouse_callback); // 用GLFW註冊了回調函數之後，鼠標一移動mouse_callback函數就會被調用：
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSwapInterval(3);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        //        return -1;
        return window;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST); // 開啟深度測試
    glDepthFunc(GL_LESS);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}


