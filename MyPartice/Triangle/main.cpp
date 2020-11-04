#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h> /* 亂數相關函數 */
using namespace std;

// step0. 必須寫很多檔案操作的程式碼才可以形成一個數組，在此直接新增
//我們可以使用兩個三角形繪製一個矩形（OpenGL主要用於三角形）。這將生成以下一組頂點：
float vertices[] = {
    // 第一个三角形
    -0.5f, -0.5f, 0.0f,   // 右上角 //0
    0.5f, -0.5f, 0.0f,  // 右下角  //1
    0.0f,  0.5f, 0.0f,  // 左上角  //2
    // 第二个三角形
    //    0.5f, -0.5f, 0.0f,  // 右下角
    //    0.0f,  0.5f, 0.0f,  // 左下角
    0.8f,  0.7f, 0.6f,  // 左上角  //3
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
        "layout (location = 0) in vec3 aPos;\n"        // 把0號location值指派成apos這個變數
        "void main(){\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";  // 在程式碼中可以直接透過apos取得這個location的資訊

//step6. 編譯片段著色器,獲取頂點著色器的源代碼，並將其存儲在代碼文件頂部的const C字符串中：
const char *fragmentShaderSource =
        "#version 330 core                                  \n"
        "out vec4 FragColor;                                \n"
        "void main(){\n"
        "   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);     \n"
        "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);}     \n";

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
    /*在主函數中，我們首先使用 glfwInit，之後我們可以使用 glfwWindowHint。
    第一個論點glfwWindowHint告訴我們要配置的選項，我們可以從大量以開頭的可能選項中選擇該選項GLFW_。
    第二個參數是一個整數，用於設置選項的值。可以在GLFW的窗口處理文檔中找到所有可能選項及其對應值的列表。
    如果您現在嘗試運行該應用程序，但它給出了許多未定義的引用錯誤，則意味著您未成功鏈接GLFW庫。*/

    // instantiate the GLFW window
    glfwInit();

    // Hint openGL Ver. 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open GLFW Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
    if (window == NULL)
    {
        cout << "openGL window failed!" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Init GLEW
    glewExperimental = true;
    if (glewInit()!=GLEW_OK){
        cout << "Init GLEW failed.";
        glfwTerminate();
        return -1;
    }

    // Viewport
    glViewport(0,0,800,600);

    //    step13.  面剔除
    //glEnable(GL_CULL_FACE);
    //面剔除(Face culling)所要做的。OpenGL允许检查所有正面朝向（Front facing）观察者的面，并渲染它们，
    //    而丢弃所有背面朝向（Back facing）的面
    //glCullFace(GL_FRONT);
    //    glCullFace函数有三个可用的选项：
    //    GL_BACK：只剔除背面。
    //    GL_FRONT：只剔除正面。
    //    GL_FRONT_AND_BACK：剔除背面和正面。

    //    step16. 使用線框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //step1. 先造一個VAO
    unsigned int VAO;
    glGenVertexArrays(1,&VAO); // 這個方法可一次造多個VAO
    glBindVertexArray(VAO);

    //step2. 造一個VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);   // 這個方法可一次造多個VBO
    // step3. 將VBO綁至Array Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //step4. 將數據由cpu複製到的gpu緩衝區
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //    到目前為止，我們將頂點數據存儲在圖形卡的內存中，由名為VBO的頂點緩衝區對像管理。
    //    接下來，我們要創建一個vertex和fragment shader來實際處理這些數據，因此讓我們開始構建它們。

    //    step14. 造一個EBO，並把indices流向GPU的ARRAY_BUFFER
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //step7.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // GL_VERTEX_SHADER常量作為著色器類型
    // 將source放到vertexShader裡面並進行編譯
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // step7.5 check Compile vertexShader
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

    //step8.
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // GL_FRAGMENT_SHADER常量作為著色器類型
    // 將source放到fragmentShader裡面並進行編譯
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // step8.5 check Compile fragmentShader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::FRAGMENT SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }else {
        cout << "INFO::FRAGMENT SHADER::VERTEX::COMPILATION_SUCCESSED\n" << infoLog << endl;
    }

    //step9. 透過shaderProgram將兩個shader並在一起成為一個program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // 將著色器附加到程序上並通過 glLinkProgram
    glUseProgram(shaderProgram); // 通過調用來激活它 glUseProgram 以新創建的程序對像作為其參數

    //step9. 鏈接到程序對象，別忘了刪除它們
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //step9.5 check Program LINK_STATUS
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
    }else{
        cout << "INFO::SHADER::PROGRAM::LINK_SUCCESS\n" << infoLog << endl;
    }

    //step10.  設定0號頂點特徵值的內容,告訴OpenGL在渲染之前應如何解釋頂點數據
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //step11. 把第0號的attribute塞進去pointer number
    glEnableVertexAttribArray(0);



    // 告訴GLFW，我們要通過註冊每個窗口大小來調用此函數
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        // TO-DO
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float alpha = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //        glClearColor(0.0f, 0.3f, 0.3f, 0.5f); // R, G, B, alpha透明值
        glClearColor(r, g, b, alpha); // R, G, B, alpha透明值
        glClear(GL_COLOR_BUFFER_BIT);

        //step12.  draw triangle
        //        glBindVertexArray(VAO);
        //        glUseProgram(shaderProgram);
        //        glDrawArrays(GL_TRIANGLES,0,6); // 從第0個頂點起始畫3個頂點

        //    step15. 將EBO綁至當前Context，將資料丟給VAO描繪三角形
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // TO-DO END
        // check and call events and swap the buffers
        glfwSwapBuffers(window);    // glfwSwapBuffers will swap the color buffer
        glfwPollEvents(); // checks if any events are triggered

        // Double buffer 雙緩衝區
        /*當應用程序使用單個緩衝區時，生成的圖像可能會出現閃爍問題。
        這是因為生成的輸出圖像不是立即繪製，而是一個像素一個像素地繪製，通常是從左到右，從上到下。
        由於此圖像在仍被渲染時不會立即顯示給用戶，因此結果可能包含偽像。
        為了避免這些問題，窗口應用程序應用了雙重緩衝區進行渲染。所述前緩衝器中包含顯示在屏幕上，
        而所有的渲染命令繪製到最終輸出圖像回緩衝器。一旦所有渲染命令完成，我們交換 後緩衝區到前緩衝區，
        因此可以顯示圖像而無需渲染，從而消除了所有上述偽像。*/
    }

    glfwTerminate(); /*退出渲染循環後，我們要正確清理/刪除已分配的所有GLFW資源。*/
    return 0;
}


