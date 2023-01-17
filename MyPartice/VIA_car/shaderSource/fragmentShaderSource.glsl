#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;    // second texture

//創建一個結構體(Struct)來儲存物體的材質屬性。我們也可以把它們儲存為獨立的uniform值
struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

uniform Material material;
uniform vec3 cameraPos;

out vec4 FragColor;


struct LightDirectional {
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
};
uniform LightDirectional lightD;

// 多點光源
struct LightPoint {
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
};
uniform LightPoint lightP[4];

struct LightSpot{
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
    float CosPhyInner;
    float CosPhyOutter;
};
uniform LightSpot lightS;


vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera){
    // diffuse max(dot(L, N),0)
    float diffIntensity = max(dot(light.dirToLight, uNormal), 0);
    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

    // specular pow(max(dot(R, Cam)),0, shininess)
    vec3 R = max(normalize(reflect(-light.dirToLight, uNormal)),0);
    float specIntensity = pow(max(dot(R, dirToCamera),0), material.shininess);
    vec3 specColor = specIntensity * light.color * texture(material.diffuse, TexCoord).rgb;


    vec3 result = diffColor + specColor;
    return result;
}

vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera){
    // attenuation
    float dist = length(light.pos - FragPos); // 根據位置計算光源距離
    float attenuation = 1/(light.constant + light.linear * dist + light.quadratic * (dist * dist)); // 計算衰減量

    // diffuse
    float diffIntensity = max( dot (normalize(light.pos - FragPos), uNormal), 0 ) * attenuation;
    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera),0), material.shininess) * attenuation;
    vec3 specColor = specIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

    vec3 result = diffColor + specColor;
    return result;
}

vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera){
    // attenuation
    float dist = length(light.pos - FragPos); // 根據位置計算光源距離
    float attenuation = 1/(light.constant + light.linear * dist + light.quadratic * (dist * dist)); // 計算衰減量
    float spotRatio;
    float cosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);
    // 以cos值做比較，角度越大Theta值越小
    if (cosTheta > light.CosPhyInner){
        // inside (若片段位於聚光的切光方向之間（也就是在錐形內），就照亮片段)
        spotRatio = 1.0f;
    }else if(cosTheta > light.CosPhyOutter){
        // middle (一樣在錐形內，但強度變弱)
        spotRatio =  (cosTheta - light.CosPhyOutter)/(light.CosPhyInner - light.CosPhyOutter);
    }else{
        // outside (落在這個角度之外的物體都不會被這個聚光所照亮)
        spotRatio = 0.0f;
    }

    // diffuse
    float diffIntensity = max( dot (normalize(light.pos - FragPos), uNormal), 0 )  * attenuation * spotRatio;
    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera),0), material.shininess) * attenuation * spotRatio;
    vec3 specColor = specIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

    vec3 result = diffColor + specColor;
    return result;
}

void main(){
    vec3 finalResult = vec3(0.0, 0, 0);
    vec3 uNormal = normalize(Normal);
    vec3 dirToCamera = normalize(cameraPos - FragPos);

    finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
//    for (int i =0;i<4;i++){
//        finalResult += CalcLightPoint(lightP[i], uNormal, dirToCamera);
//    }
//    finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);
    FragColor = vec4(finalResult, 1.0);
//    FragColor = vec4(1.0,1.0,1.0,1.0);
}

