#version 330 core
uniform float xOffset;

layout (location = 6) in vec3 aPos;
layout (location = 7) in vec3 aColor;
layout (location = 8) in vec3 aTexCoord;

out vec4 vertexColor;
//out vec4 ourPosition;
out vec2 TexCoord;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
//    ourPosition = vec4(aPos,1.0);
}
