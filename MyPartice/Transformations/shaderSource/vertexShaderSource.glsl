#version 330 core
uniform float xOffset;

layout (location = 6) in vec3 aPos;
layout (location = 7) in vec3 aColor;
layout (location = 8) in vec2 aTexCoord;

uniform mat4 transform;

out vec4 vertexColor;
//out vec4 ourPosition;
out vec2 TexCoord;

void main(){
    //    修改頂點著色器讓其接收一個mat4的uniform變量，然後再用矩陣uniform乘以位置向量
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1);
    TexCoord = aTexCoord;

}
