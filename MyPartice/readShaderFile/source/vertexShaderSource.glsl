#version 330 core
uniform float xOffset;

out vec4 vertexColor;
out vec4 ourPosition;
layout (location = 6) in vec3 aPos;
layout (location = 7) in vec3 aColor;
void main(){
   gl_Position = vec4(aPos.x - xOffset, -aPos.y, aPos.z, 1.0);
   vertexColor = vec4(aColor.x+0.6, aColor.y+0.5, aColor.z, 1.0);
   ourPosition = vec4(aPos,1.0);
}
