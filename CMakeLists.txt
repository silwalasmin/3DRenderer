cmake_minimum_required(VERSION 3.21)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_STANDARD_REQUIRED TRUE)
file( GLOB SRC src/*.cpp libs/glad/src/glad.c libs/stb_image/stb_image.cpp)

#header files
file( GLOB INCLUDE include/ libs/glad/include/* libs/glm/** libs/stb_image/stb_image.cpp)

include_directories(
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/libs/
        ${CMAKE_SOURCE_DIR}/libs/glad/include/
        ${CMAKE_SOURCE_DIR}/libs/stb_image/
)

#executable
add_executable( ${PROJECT_NAME} src/main.cpp ${SRC} ${INCLUDE} )

#dependencies
target_link_libraries( ${PROJECT_NAME} assimp glfw GL dl)

