#ifndef TEXTURE_H
#define TEXTURE_H

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"


#include "GL/glew.h"
#include "GLFW/glfw3.h"

unsigned int gen_texture(const char* imgPath, GLint image_format, int position=0);

#endif // TEXTURE_H
