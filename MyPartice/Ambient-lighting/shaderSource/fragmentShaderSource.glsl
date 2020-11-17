#version 330 core
in vec3 FragPos;
in vec3 Normal;

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;    // second texture

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 FragColor;

void main(){
    vec3 lightDir = normalize(lightPos - FragPos);
    //    FragColor = vec4(objColor * ambientColor, 1.0); // ambientColor

//    vec3 diffuse = dot(lightDir , Normal) * lightColor ; // 計算光照反射強度，並乘上反射的顏色向量
    vec3 diffuse = max(dot(lightDir , Normal),0) * lightColor ; // 計算光照反射強度，並乘上反射的顏色向量
    //    FragColor = vec4(diffuse, 1.0);
    FragColor = vec4((ambientColor + diffuse) * objColor, 1.0); // ambientColor + DiffuseColor
}

