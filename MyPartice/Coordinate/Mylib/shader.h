#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>

unsigned int LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
void use(GLuint ID);
void setBool(GLuint ID, const std::string &name, bool value);
void setInt(GLuint ID,const std::string &name, int value);
void setFloat(GLuint ID,const std::string &name, float value);

#endif // SHADER_H
