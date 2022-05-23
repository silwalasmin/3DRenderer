#ifndef MAIN_HPP
#define MAIN_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Renderer3D
{
public:
    Renderer3D(unsigned int width, unsigned int height, const char *name);
    ~Renderer3D();

    void run();
    void processEvent();

private:
    GLFWwindow *m_window;
    unsigned int m_width, m_height;
    const char *m_title;
};

#endif 