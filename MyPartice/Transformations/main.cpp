#include <iostream>
#include "shader.h"
#include "gl_setup.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//container, cover
float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   4.0f, 4.0f,   // 右上
//    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   4.0f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 4.0f    // 左上
//};

//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//    1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   4.0f, 4.0f,   // 右上
//    1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 右下
//    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//    -1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 4.0f    // 左上
//};

//step14.  創造欲進行索引填充的indices
unsigned int indices[] = { // 注意索引从0开始!
                           0, 1, 2, // 第一个三角形
                           2, 3, 0  // 第二个三角形
                         };

int GLM_Test()
{
    //    基礎的位移測試
    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans; // trans will be a identity matrix
    trans = glm::translate(trans, glm::vec3(2.0f,0.0f,-1.0f));

    vec = trans * vec;
    cout << vec.x << " " << vec.y << " " << vec.z << endl;
    return -1;
}

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
    unsigned int textBufferB = gen_texture("../img/awesomeface.png", GL_RGBA, 3);

    // calculate out translation matrix here
    //把箱子逆時針旋轉90度。然後縮放0.5倍，使它變成原來的一半大。我們先來創建變換矩陣：
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0.1f, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    glm::mat4 trans2;

    bool flag = true;
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

//        // first
//        trans = glm::translate(trans, glm::vec3(0.005f, 0.005f, 0.0f));
//        trans = glm::rotate(trans, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, -1.0f));
//        trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
//        // 查詢uniform變量的地址，然後用有Matrix4fv後綴的glUniform函數把矩陣數據發送給著色器
//        unsigned int transformLoc = glGetUniformLocation(programID1, "transform");
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // second transformation
        // ---------------------
        trans2 = glm::mat4(1.0f); // reset it to identity matrix
//        trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = sin(glfwGetTime()/2);
        float scaleAmount2 = cos(glfwGetTime()/2);
        trans2 = glm::scale(trans2, glm::vec3(scaleAmount2, scaleAmount, scaleAmount2));
        unsigned int transformLoc = glGetUniformLocation(programID1, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans2[0][0]); // this time take the matrix value array's first element as its memory pointer value

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
