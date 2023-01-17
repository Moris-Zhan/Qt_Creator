#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"

#ifndef GL_SETUP_H
#define GL_SETUP_H

class Gl_Setup
{
public:
    Gl_Setup(Camera _camera);
    GLFWwindow* windowSetup();

    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void static mouse_callback(GLFWwindow* window, double xPos, double yPos);
    void static key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void static scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    Camera getCamera();
};



#endif // GL_SETUP_H
