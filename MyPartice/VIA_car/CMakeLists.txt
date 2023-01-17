cmake_minimum_required(VERSION 2.8)

project(VIA_car)

file(GLOB HEADER_FILES
            "headers/*.h"
    )
file(GLOB SOURCE_FILES
            "sources/*.cpp"
    )
file(GLOB IMG_FILES
            "img/*.*"
    )
file(GLOB SHADER_FILES
            "shaderSource/*.*"
    )

add_executable(${PROJECT_NAME}
                "main.cpp"
                ${SOURCE_FILES}
                ${HEADER_FILES}
                ${SHADER_FILES}
                )

# openGL
find_package(OpenGL REQUIRED)
# assimp
#find_package(ASSIMP REQUIRED)


include_directories(
    D:/WorkSpace/VIA/QT/QT_Lib/glfw-3.3.2/include/
    D:/WorkSpace/VIA/QT/QT_Lib/glfw-3.3.2/lib/

    D:/WorkSpace/VIA/QT/QT_Lib/glew-2.1.0/include/
    D:/WorkSpace/VIA/QT/QT_Lib/glew-2.1.0/lib/Release/Win32/

    D:/WorkSpace/VIA/QT/QT_Lib/glm/

    D:/WorkSpace/VIA/QT/QT_Lib/assimp-3.3.1/include

    shaderSource/
    headers/
    )

# 設定ALL_LIBS加入glfw, glew, assimp
set(ALL_LIBS
    ${OPENGL_LIBRARY}
    D:/WorkSpace/VIA/QT/QT_Lib/glfw-3.3.2/lib/glfw3.lib
    D:/WorkSpace/VIA/QT/QT_Lib/glew-2.1.0/lib/Release/Win32/glew32s.lib
    D:/WorkSpace/VIA/QT/QT_Lib/assimp-3.3.1/lib/assimp.lib
    )

target_link_libraries(${PROJECT_NAME}
    ${ALL_LIBS}
    )

