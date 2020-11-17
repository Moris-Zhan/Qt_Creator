#version 330 core
uniform float xOffset;

layout (location = 6) in vec3 aPos;
layout (location = 7) in vec3 aColor;
layout (location = 8) in vec2 aTexCoord;

uniform mat4 transform;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;
//out vec4 ourPosition;
out vec2 TexCoord;

void main(){
    //  先做model再做view轉換最後再做projection
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1);
    TexCoord = aTexCoord;

}
