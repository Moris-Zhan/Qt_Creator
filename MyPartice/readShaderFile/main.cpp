#include <iostream>
#include "shader.h"
#include "gl_setup.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>

float vertices[] = {
    // 第一个三角形
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// 右上角 //0 // r
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// 右下角  //1 // g
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// 左上角  //2 // b
    // 第二个三角形
    //    0.5f, -0.5f, 0.0f,  // 右下角
    //    0.0f,  0.5f, 0.0f,  // 左下角
    0.8f,  0.7f, 0.6f,  1.0f, 0.0f, 1.0f// 左上角  //3
};

//step14.  創造欲進行索引填充的indices
unsigned int indices[] = { // 注意索引从0开始!
                           0, 1, 2, // 第一个三角形
                           2, 1, 3  // 第二个三角形
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
        GLuint programID1 = LoadShaders( "../source/vertexShaderSource.glsl",
                                         "../source/fragmentShaderSource.glsl" );

    // 知道了现在使用的布局，我们就可以使用glVertexAttribPointer函数更新顶点格式
    // 位置属性
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(6);
    // 颜色属性
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(7);


    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // To-Do
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        /* 首先我們通過glfwGetTime()獲取運行的秒數。然後我們使用sin函數讓顏色在0.0到1.0之間改變，最後將結果儲存到greenValue裡 */

        float offset = 0.5f;
        setFloat(programID1,"xOffset", offset);

        glUseProgram(programID1);
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
