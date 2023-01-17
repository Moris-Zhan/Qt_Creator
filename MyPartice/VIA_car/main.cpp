#define GLEW_STATIC
#include <iostream>
#include "shader.h"
#include "gl_setup.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "material.h"
#include <lightdirectional.h>
#include <lightpoint.h>
#include <lightspot.h>

#include <mesh.h>
#include <model.h>

#pragma region Model Data

#pragma endregion

int main()
{
# pragma region Camera Declare
    Camera mainCamera(glm::vec3(0, 8.0f, 20.0f), glm::radians(0.0f), glm::radians(-90.0f), glm::vec3(0,90.0f,0));
    Gl_Setup gl_Setup = Gl_Setup(mainCamera);
# pragma endregion

# pragma region Light Declare
    // Directional
    LightDirectional lightD(glm::vec3(12.2f, 10.0f, 20.0f),                              // position glm::vec3(1.2f, 1.0f, 2.0f)
                           glm::vec3(glm::radians(90.0f),glm::radians(0.0f) , 0),   // angles
                           glm::vec3(1.0f, 1.0f, 1.0f));                             // color
    //     Point
    LightPoint lightP[4] = {
        LightPoint(glm::vec3(30.0f, 0.0f, 0.0f),                    // position
        glm::vec3(glm::radians(45.0f),glm::radians(45.0f) , 0),    // angles
        glm::vec3(1.0f, 1.0f, 1.0f)),                               // color

        LightPoint(glm::vec3(0.0f, 30.0f, 0.0f),                    // position
        glm::vec3(glm::radians(45.0f),glm::radians(45.0f) , 0),    // angles
        glm::vec3(1.0f, 1.0f, 1.0f)),                               // color

        LightPoint(glm::vec3(0.0f, 0.0f, 30.0f),                    // position
        glm::vec3(glm::radians(45.0f),glm::radians(45.0f) , 0),    // angles
        glm::vec3(1.0f, 1.0f, 1.0f)),                               // color

        LightPoint(glm::vec3(30.0f, 30.0f, 30.0f),                    // position
        glm::vec3(glm::radians(45.0f),glm::radians(45.0f) , 0),    // angles
        glm::vec3(1.0f, 1.0f, 1.0f))                               // color
    };
    // Spot
    LightSpot lightS(glm::vec3(0.0f, 20.0f, 0.0f),                                            // position
                  glm::vec3(glm::radians(90.0f), glm::radians(45.0f) , 0),                  // angles
                  glm::vec3(1.0f, 1.0f, 1.0f));                                             // color

# pragma endregion

#pragma region Open a Window
    // Open a window and create its OpenGL context
    GLFWwindow* window = gl_Setup.windowSetup();
#pragma endregion

#pragma Init Shader Program
    GLuint myShaderID = LoadShaders( "../shaderSource/vertexShaderSource.glsl",
                                     "../shaderSource/fragmentShaderSource.glsl" );
//    GLuint myShaderID2 = LoadShaders( "../shaderSource/vertexShaderSource_wheel.glsl",
//                                     "../shaderSource/fragmentShaderSource.glsl" );
#pragma endregion

#pragma Init Material
//    Material *myMaterial = new Material(myShaderID,
//                                        glm::vec3(1.0f, 1.0f, 1.0f), // 环境光
//                                        LoadImgToGPU("../img/container.jpg", GL_RGB, GL_RGB, DIFFUSE), // 漫反射
//                                        LoadImgToGPU("../img/container2_specular.png", GL_RGBA, GL_RGB, SPEUULAR), // 鏡反射
//                                        LoadImgToGPU("../img/star.jpg", GL_RGBA, GL_RGB, EMISSION), // 放射光
//                                        64.0f);                      // 反光度
#pragma endregion

#pragma region Init and Load Models to VAO, VBO
//    Mesh cube(vertices_norm);
//    Model model2("../assim_models/nanosuit/nanosuit.obj");

    Model grab("../assim_models/Crane_qt/grab/grab.obj");
    Model head("../assim_models/Crane_qt/head/head.obj");
    Model body("../assim_models/Crane_qt/body/body.obj");
    Model wheel("../assim_models/Crane_qt/wheel/wheel.obj");

//    Model wheel("../assim_models/Van_qt/wheel/wheel.obj");
//    Model body("../assim_models/Van_qt/body/body.obj");
//    Model Van_qt("../assim_models/Van_qt/Van_qt.obj");
#pragma endregion

#pragma region Init texture data
    //    unsigned int textBufferA = LoadImgToGPU("../img/container.jpg", GL_RGB, GL_RGB, 0);
    //    unsigned int textBufferB = LoadImgToGPU("../img/awesomeface.png", GL_RGBA, GL_RGB, 0);
#pragma endregion

#pragma region MVP matrices (Render Pipeline)
    // calculate out translation matrix here
    glm::mat4 modelMat = glm::mat4(1.0f); // initial matrix
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::mat4 projMat = glm::mat4(1.0f);
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 trans2;
#pragma endregion

#pragma region Render-Loop
    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainCamera = gl_Setup.getCamera();
        viewMat = mainCamera.getViewMatrix();

        // Set Material -> Shader Program
        glUseProgram(myShaderID);
        // Set Material -> Textures
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
//            glActiveTexture(GL_TEXTURE0 + 1);
//            glBindTexture(GL_TEXTURE_2D, myMaterial->specular);



        // Set Material -> Uniforms
        unsigned int modelMatLoc = glGetUniformLocation(myShaderID, "modelMat");
        glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, &modelMat[0][0]);
        unsigned int viewMatLoc = glGetUniformLocation(myShaderID, "viewMat");
        glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, &viewMat[0][0]);
        unsigned int projMatLoc = glGetUniformLocation(myShaderID, "projMat");
        glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, &projMat[0][0]);



        // Ambient lighting
        glUniform3f(glGetUniformLocation(myShaderID,"ambientColor"),1.0f , 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(myShaderID,"objColor"),1.0f,1.0f,1.0f);

        // Directional Light
        setUniform3f(myShaderID, "lightD.pos", lightD.position);
        setUniform3f(myShaderID, "lightD.color", lightD.color);
        setUniform3f(myShaderID, "lightD.dirToLight", lightD.direction);

        // Multi-Point Light
        for(int i = 0; i < sizeof(lightP)/sizeof(LightPoint); i++){
            stringstream ss;
            ss << i;
            string pos1 = "lightP[" + ss.str() +"].pos";
            string pos2 = "lightP[" + ss.str() +"].color";
            string pos3 = "lightP[" + ss.str() +"].dirToLight";
            string pos4 = "lightP[" + ss.str() +"].constant";
            string pos5 = "lightP[" + ss.str() +"].linear";
            string pos6 = "lightP[" + ss.str() +"].quadratic";

            setUniform3f(myShaderID, pos1.c_str(), lightP[i].position);
            setUniform3f(myShaderID, pos2.c_str(), lightP[i].color);
            setUniform3f(myShaderID, pos3.c_str(), lightP[i].direction);
            glUniform1f(glGetUniformLocation(myShaderID, pos4.c_str()), lightP[i].constant);
            glUniform1f(glGetUniformLocation(myShaderID, pos5.c_str()), lightP[i].linear);
            glUniform1f(glGetUniformLocation(myShaderID, pos6.c_str()), lightP[i].quadratic);
        }
        // Spot Light
        setUniform3f(myShaderID, "lightS.pos", lightS.position);
        setUniform3f(myShaderID, "lightS.color", lightS.color);
        setUniform3f(myShaderID, "lightS.dirToLight", lightS.direction);
        glUniform1f(glGetUniformLocation(myShaderID, "lightS.constant"), lightS.constant);
        glUniform1f(glGetUniformLocation(myShaderID, "lightS.linear"), lightS.linear);
        glUniform1f(glGetUniformLocation(myShaderID, "lightS.quadratic"), lightS.quadratic);
        glUniform1f(glGetUniformLocation(myShaderID, "lightS.CosPhyInner"), lightS.cosPhyInner);
        glUniform1f(glGetUniformLocation(myShaderID, "lightS.CosPhyOutter"), lightS.cosPhyOuter);


        // Specular Lighting
        setUniform3f(myShaderID, "cameraPos", mainCamera.Position);

        // Set Material
        setUniform3f(myShaderID, "material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        setUniform1i(myShaderID,"material.diffuse", DIFFUSE);
        setUniform1i(myShaderID,"material.specular", SPEUULAR);
        setUniform1i(myShaderID,"material.emission", EMISSION);
        setUniform1f(myShaderID, "material.shininess", 64.0f);

        //////////////////////////
        trans2 = glm::mat4(1.0f); // reset it to identity matrix
        float scaleAmount = sin(glfwGetTime()/2);
        float scaleAmount2 = cos(glfwGetTime()/2);
        trans2 = glm::scale(trans2, glm::vec3(scaleAmount2, scaleAmount, scaleAmount2));
        unsigned int transformLoc = glGetUniformLocation(myShaderID, "transform");
//            unsigned int transformLoc2 = glGetUniformLocation(myShaderID2, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans2[0][0]);
//            glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, &trans2[0][0]);
        //////////////////////////
        body.draw(myShaderID);
        grab.draw(myShaderID);
        head.draw(myShaderID);
        wheel.draw(myShaderID);

//        body.draw(myShaderID);
//        wheel.draw(myShaderID);
        // To-Do End

        // Clean up, prepare for next render loop
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
#pragma endregion

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}
