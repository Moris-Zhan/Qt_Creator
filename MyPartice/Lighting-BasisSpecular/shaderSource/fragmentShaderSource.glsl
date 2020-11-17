#version 330 core
in vec3 FragPos;
in vec3 Normal;

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;    // second texture

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

void main(){
    vec3 lightDir = normalize(lightPos - FragPos);
    //    reflect函數要求第一個向量是從光源指向片段位置的向量 (注意的是我們對lightDir向量進行了取反)，
    //    第二個參數要求是一個法向量，所以我們提供的是已標準化的norm向量。
    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);


    //    FragColor = vec4(objColor * ambientColor, 1.0); // ambientColor
    vec3 diffuse = max(dot(lightDir , Normal),0) * lightColor ; // 計算光照反射強度，並乘上反射的顏色向量

    float specularAmount = dot(reflectVec , cameraVec);
    vec3 specular = specularAmount * lightColor;

    FragColor = vec4((ambientColor + diffuse + specular) * objColor, 1.0); // ambientColor + DiffuseColor
}

