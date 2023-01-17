#ifndef TEXTURE_H
#define TEXTURE_H

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"


#include "GL/glew.h"
#include "GLFW/glfw3.h"

unsigned int LoadImgToGPU(const char* filename, GLint internalFormat, GLenum format,int textureSlot=0);

#endif // TEXTURE_H
