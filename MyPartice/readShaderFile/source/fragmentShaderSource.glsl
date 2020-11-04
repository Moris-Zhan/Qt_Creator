#version 330 core

uniform vec4 ourColor;

in vec4 vertexColor;
in vec4 ourPosition;

out vec4 FragColor;

void main(){
//   FragColor = vertexColor;
   FragColor = ourPosition;
}
