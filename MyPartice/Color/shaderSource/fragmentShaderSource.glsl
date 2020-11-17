#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;    // second texture

uniform vec3 objColor;
uniform vec3 lightColor;

out vec4 FragColor;

void main(){
//    FragColor = mix(texture2D(ourTexture, TexCoord), texture2D(ourFace, vec2(1.0 - TexCoord.x, TexCoord.y)),0.5); // 控制x方向顛倒

    FragColor = vec4(objColor * lightColor, 1.0) * mix(texture2D(ourTexture, TexCoord), texture2D(ourFace, vec2(1.0 - TexCoord.x, TexCoord.y)),0.5);

}

