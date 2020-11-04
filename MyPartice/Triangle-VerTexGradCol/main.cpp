#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h> /* 亂數相關函數 */
#include "math.h"
using namespace std;


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

/**
未來shader中pipeline的input name要與上一個shader的output name相同否則報錯
**/
//step5. 編譯著色器,獲取頂點著色器的源代碼，並將其存儲在代碼文件頂部的const C字符串中：
const char *vertexShaderSource =
        "#version 330 core\n"
        "out vec4 vertexColor;\n" // 为片段着色器指定一个颜色输出
        "layout (location = 6) in vec3 aPos;\n"        // 位置变量的属性位置值为 0
        "layout (location = 7) in vec3 aColor;\n"      // 颜色变量的属性位置值为 1
        "void main(){\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"  // 在程式碼中可以直接透過apos取得這個location的資訊
        "   vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);}\n";        // 將ourColor設置為我們從頂點資料那裡得到的輸入顏色


//step6. 編譯片段著色器,獲取頂點著色器的源代碼，並將其存儲在代碼文件頂部的const C字符串中：
const char *fragmentShaderSource =
        "#version 330 core\n"
        "in vec4 vertexColor;\n" // 从顶点着色器传来的输入变量（名称相同、类型相同）
        "uniform vec4 ourColor;\n" // 在OpenGL程序代码中设定这个变量
        "out vec4 FragColor;\n"
        "void main(){\n"
//        "   FragColor = ourColor;}     \n";
        "   FragColor = vertexColor;}     \n";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) // resize glfw window
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // 偵測ESC鍵有沒有被按下
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main()
{
    cerr << "xyz" << endl << endl;
//    Shader* testshader = new Shader("vertexShaderSource.txt","fragmentShaderSource.txt");
//    testshader->wellcome();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle-VerTexGradCol", NULL, NULL);
    if (window == NULL)
    {
        cout << "openGL window failed!" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit()!=GLEW_OK){
        cout << "Init GLEW failed.";
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,600);
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);*/   //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // GL_VERTEX_SHADER常量作為著色器類型
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::VERTEX SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }else {
        cout << "INFO::VERTEX SHADER::VERTEX::COMPILATION_SUCCESSED\n" << infoLog << endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // GL_FRAGMENT_SHADER常量作為著色器類型
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::FRAGMENT SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }else {
        cout << "INFO::FRAGMENT SHADER::VERTEX::COMPILATION_SUCCESSED\n" << infoLog << endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // 將著色器附加到程序上並通過 glLinkProgram
    glUseProgram(shaderProgram); // 通過調用來激活它 glUseProgram 以新創建的程序對像作為其參數

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
    }else{
        cout << "INFO::SHADER::PROGRAM::LINK_SUCCESS\n" << infoLog << endl;
    }
    // 知道了现在使用的布局，我们就可以使用glVertexAttribPointer函数更新顶点格式
    // 位置属性
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(6);
    // 颜色属性
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(7);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        // TO-DO
        glClearColor(0.0f, 0.3f, 0.3f, 0.5f); // R, G, B, alpha透明值
        glClear(GL_COLOR_BUFFER_BIT);


        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        /* 首先我們通過glfwGetTime()獲取運行的秒數。然後我們使用sin函數讓顏色在0.0到1.0之間改變，最後將結果儲存到greenValue裡 */
        float timeValue = glfwGetTime();
        float greenvalue =(sin(timeValue)/2.0f)+0.5f;
        /*
        接著，我們用glGetUniformLocation查詢uniform ourColor的位置值。
        我們為查詢函數提供著色器程序和uniform的名字（這是我們希望獲得的位置值的來源）
        */
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); // 用glGetUniformLocation查詢uniform ourColor的位置值
        glUniform4f(vertexColorLocation, 0.0f, greenvalue, 0.0f, 1.0f); // 通過glUniform4f函數設置uniform值

        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // TO-DO END
        // check and call events and swap the buffers
        glfwSwapBuffers(window);    // glfwSwapBuffers will swap the color buffer
        glfwPollEvents(); // checks if any events are triggered
    }

    glfwTerminate(); /*退出渲染循環後，我們要正確清理/刪除已分配的所有GLFW資源。*/
    return 0;
}


