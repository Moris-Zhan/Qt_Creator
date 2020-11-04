#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;    // second texture

out vec4 FragColor;

void main(){
    //    使用GLSL內建的texture函數來採樣紋理的顏色，
    //    它第一個參數是紋理採樣器，第二個參數是對應的紋理坐標。texture函數會使用之前設置的紋理參數對相應的顏色值進行採樣

    //    opengl 乘法運算是一般點對點相乘並非矩陣相乘 // 變色
    //    FragColor = (texture2D(ourTexture, TexCoord)* vertexColor*2);

    //    opengl 乘法運算是一般點對點相乘並非矩陣相乘 // overlap texture
    //    FragColor = texture2D(ourTexture, TexCoord)* texture2D(ourFace, TexCoord);

//    FragColor = texture2D(ourTexture, TexCoord)* texture2D(ourFace, vec2(1.0 - TexCoord.x, TexCoord.y)); // 控制x方向顛倒

    FragColor = mix(texture2D(ourTexture, TexCoord), texture2D(ourFace, vec2(1.0 - TexCoord.x, TexCoord.y)),0.5); // 控制x方向顛倒

}

