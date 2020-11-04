#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

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
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

    // 告訴GLFW，我們要通過註冊每個窗口大小來調用此函數
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float alpha = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        glClearColor(0.0f, 0.3f, 0.3f, 0.5f); // R, G, B, alpha透明值
        glClearColor(r, g, b, alpha); // R, G, B, alpha透明值
        glClear(GL_COLOR_BUFFER_BIT);

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


