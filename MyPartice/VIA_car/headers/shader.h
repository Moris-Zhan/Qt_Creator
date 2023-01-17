#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


unsigned int LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
void use(GLuint ID);
void setBool(GLuint ID, const std::string &name, bool value);
void setInt(GLuint ID,const std::string &name, int value);
void setFloat(GLuint ID,const std::string &name, float value);
void setUniform3f(GLuint ID, const char* paramNameString, glm::vec3 param);
void setUniform1f(GLuint ID, const char* paramNameString, float param);
void setUniform1i(GLuint ID, const char* paramNameString, int slot);

enum Slot
{
    DIFFUSE,
    SPEUULAR,
    EMISSION
};



#endif // SHADER_H

