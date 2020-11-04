#include <iostream>
#include "shader.h"
#include "gl_setup.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "texture.h"


//container, cover
//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // 右上
//    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // 左上
//};

float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   4.0f, 4.0f,   // 右上
    1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 右下
   -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 4.0f    // 左上
};

//step14.  創造欲進行索引填充的indices
unsigned int indices[] = { // 注意索引从0开始!
                           0, 1, 2, // 第一个三角形
                           2, 3, 0  // 第二个三角形
                         };

int main()
{
    // Open a window and create its OpenGL context
    GLFWwindow* window = windowSetup();

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //    路徑從build那邊開始算....
    GLuint programID1 = LoadShaders( "../shaderSource/vertexShaderSource.glsl",
                                     "../shaderSource/fragmentShaderSource.glsl" );

    // 知道了现在使用的布局，我们就可以使用glVertexAttribPointer函数更新顶点格式
    // 3 + 3 + 2 每次跳8個
    // 位置属性
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(6);
    // 颜色属性 初始偏移3
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(7);
    // 紋理属性 初始偏移6
    glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(8);

    unsigned int textBufferA = gen_texture("../img/container.jpg", GL_RGB, 0);
    unsigned int textBufferB = gen_texture("../img/face.png", GL_RGBA, 3);


    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // To-Do
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textBufferA);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textBufferB);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUseProgram(programID1);
        glUniform1i(glGetUniformLocation(programID1, "ourTexture"), 0); // set it manually
        glUniform1i(glGetUniformLocation(programID1, "ourFace"), 3); // set it manually
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // To-Do End
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}
