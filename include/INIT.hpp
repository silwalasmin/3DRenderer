#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <iostream>

namespace INIT
{

    void glfw()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void terminateglfw()
    {
        glfwTerminate();
    }

    void AssertglfwInit(GLFWwindow *window)
    {
        if ( !window )
        {
            std::cout << "[GLFW_ERROR] : Failed to create window." << std::endl;
            terminateglfw();
            exit(-1);
        }
    }

    void glad()
    {
        if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
        {
            std::cout << "[GLAD_ERROR] : Failed to initialize glad." << std::endl;
            exit(-1);
        }
        //if no error, display OpenGl version. 
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }

    void Enable()
    {
        //enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //vsync enable
        glfwSwapInterval(1);

        //enable z-depth test
        glEnable(GL_DEPTH_TEST);

        //set clear color
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

        // flip texture on load enabled
        stbi_set_flip_vertically_on_load(true);
    }

}