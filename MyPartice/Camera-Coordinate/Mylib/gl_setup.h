#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"

#ifndef GL_SETUP_H
#define GL_SETUP_H

GLFWwindow* windowSetup();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera getCamera();
#endif // GL_SETUP_H
