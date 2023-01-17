#include "texture.h"

//#include "GL/glew.h"
//#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Texture
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int LoadImgToGPU(const char* filename, GLint internalFormat, GLenum format,int textureSlot){
    // 紋理BufferA建立綁定
    unsigned int textBuffer;
    glGenTextures(1, &textBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);    // 若有兩個texture需開bind 0位置放進去
    glBindTexture(GL_TEXTURE_2D, textBuffer);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //多級漸遠紋理过滤
//    glTexParameteri(GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    //    讀檔+生成紋理
    //使用stb_image.h加載圖片
    //這個函數首先接受一個圖像文件的位置作為輸入。接下來它需要三個int作為它的第二、第三和第四個參數，
    //stb_image.h將會用圖像的寬度、高度和顏色通道的個數填充這三個變量。我們之後生成紋理的時候會用到的圖像的寬度和高度的
    int width, height, nrChannels;
    //    OpenGL期望0.0y軸上的坐標位於圖像的底側，但是圖像通常0.0位於y軸的頂部
    //    stb_image.h在加載任何圖像之前，可以通過添加stbi_set_flip_vertically_on_load在圖像加載期間翻轉y軸：
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format , width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        cout << "load Img success" << endl << endl;
    }
    else
    {
        cout << "Failed to load texture" << std::endl;
    }

    //    生成了紋理和相應的多級漸遠紋理後，釋放圖像的內存是一個很好的習慣。
    stbi_image_free(data);

    return textBuffer;
}

//void LoadImgToGPU(const char* filename, GLint internalFormat){
//    unsigned int textBuffer;
//    glGenTextures(1, &textBuffer);
//    glActiveTexture(GL_TEXTURE0 + position);    // 若有兩個texture需開bind 0位置放進去
//    glBindTexture(GL_TEXTURE_2D, textBuffer);


//    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//        cout << "load Img success" << endl << endl;
//    }
//    else
//    {
//        cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);

//}
