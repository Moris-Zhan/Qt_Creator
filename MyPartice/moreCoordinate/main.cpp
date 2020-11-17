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

// non color attributes
float vertices_3D[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//step14.  創造欲進行索引填充的indices
unsigned int indices[] = { // 注意索引从0开始!
                           0, 1, 2, // 第一个三角形
                           2, 3, 0  // 第二个三角形
                         };

//為每個立方體定義一個位移向量來指定它在世界空間的位置
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_3D), vertices_3D, GL_STATIC_DRAW);

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
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(6);
    // 颜色属性 初始偏移3
    //    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    //    glEnableVertexAttribArray(7);
    // 紋理属性 初始偏移6
    glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(8);

    unsigned int textBufferA = gen_texture("../img/container.jpg", GL_RGB, 0);
    unsigned int textBufferB = gen_texture("../img/awesomeface.png", GL_RGBA, 3);

    // calculate out translation matrix here
    //把箱子逆時針旋轉90度。然後縮放0.5倍，使它變成原來的一半大。我們先來創建變換矩陣：
    glm::mat4 trans;
    //    trans = glm::translate(trans, glm::vec3(0.1f, 0.0f, 0.0f));
    //    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0f));
    //    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    //    model matrix consists of translations, scaling and/or rotations
    glm::mat4 modelMat = glm::mat4(1.0f); // initial matrix
    //        modelMat = glm::rotate(modelMat, glm::radians(-55.0f),glm::vec3(1.0f, 0.0f, 0.0f)); // model trans
    modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    // translating the scene in the reverse direction of where we want to move
    glm::mat4 viewMat = glm::mat4(1.0f);
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));

    //    use perspective projection for our scene so we'll declare the projection matrix
    glm::mat4 projMat = glm::mat4(1.0f);
    // change view coord into homogenous coord
    //    glm::perspective創建了一個定義了可視空間的大平截頭體，任何在這個平截頭體以外的東西最後都不會出現在裁剪空間體積內，並且將會受到裁剪
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    do{
        // Clear the screen
        //        在每次渲染迭代之前清除深度緩衝（否則前一幀的深度信息仍然保存在緩衝中）
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // To-Do
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textBufferA);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textBufferB);
        glBindVertexArray(VAO);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUseProgram(programID1);


        /*unsigned int transformLoc = glGetUniformLocation(programID1, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans2[0][0]);*/ // this time take the matrix value array's first element as its memory pointer value



        for(unsigned int i = 0; i < 10; i++)
        {
            glUniform1i(glGetUniformLocation(programID1, "ourTexture"), 0); // set it manually
            glUniform1i(glGetUniformLocation(programID1, "ourFace"), 3); // set it manually

            glm::mat4 modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, cubePositions[i]);
            float angle = 20.0f * i;
            modelMat = glm::rotate(modelMat, (float)glfwGetTime() *glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            unsigned int modelMatLoc = glGetUniformLocation(programID1, "modelMat");
            glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, &modelMat[0][0]);
            unsigned int viewMatLoc = glGetUniformLocation(programID1, "viewMat");
            glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, &viewMat[0][0]);
            unsigned int projMatLoc = glGetUniformLocation(programID1, "projMat");
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, &projMat[0][0]);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



//        unsigned int modelMatLoc = glGetUniformLocation(programID1, "modelMat");
//        glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, &modelMat[0][0]);
//        unsigned int viewMatLoc = glGetUniformLocation(programID1, "viewMat");
//        glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, &viewMat[0][0]);
//        unsigned int projMatLoc = glGetUniformLocation(programID1, "projMat");
//        glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, &projMat[0][0]);



        //        //        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //        glDrawArrays(GL_TRIANGLES, 0, 36);


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
