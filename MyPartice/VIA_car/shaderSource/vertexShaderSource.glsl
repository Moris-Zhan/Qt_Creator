#version 330 core
uniform float xOffset;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 transform;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//out vec4 vertexColor;
//out vec4 ourPosition;
//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main(){
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);
    FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;
    //    Normal = mat3(modelMat) * aNorm; // 法向量通過modelMat轉換到世界空間坐標系統的法向量
    // 但執行了不等比縮放，頂點的改變會導致法向量不再垂直於表面
    Normal = mat3(transpose(inverse(modelMat))) * aNorm;
    TexCoord = aTexCoord;
}
