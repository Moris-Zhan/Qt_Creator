#version 330 core
uniform float xOffset;

layout (location = 6) in vec3 aPos;
//layout (location = 7) in vec3 aColor;
//layout (location = 8) in vec2 aTexCoord;
layout (location = 9) in vec3 aNorm;

uniform mat4 transform;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//out vec4 vertexColor;
//out vec4 ourPosition;
//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main(){
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);
    FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;
    Normal = mat3(modelMat) * aNorm;
}
