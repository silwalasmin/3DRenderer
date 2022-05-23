#include "main.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "INIT.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Model.hpp"


//Camera construct
Camera camera(0.0f, 1.5f, 10.0f);
float lastX = 1366/2;
float lastY = 768/2;
bool firstMouse = true;

// Projection Matrix
bool ortho=false;
//glm::mat4 projection;

//frame
float deltaTime = 0.0f;
float prevFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    auto  xpos = static_cast<float>(xposIn);
    auto  ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

struct objects
{
    unsigned int vao, vbo, ebo;
};

//Renderer3D constructor
Renderer3D::Renderer3D(unsigned int width, unsigned int height, const char *title) : m_width(width), m_height(height), m_title(title)
{
    INIT::glfw();
    //create window
    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL , NULL);
    INIT::AssertglfwInit(m_window);
    glfwMakeContextCurrent(m_window);

    INIT::glad();

    //set callbacks
    glfwSetCursorPosCallback(m_window, mouse_callback );
    glfwSetScrollCallback(m_window, scroll_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    INIT::Enable();
}

//Renderer3D destructor: Only needs to terminate glfw;
Renderer3D::~Renderer3D()
{
    INIT::terminateglfw();
}

void Renderer3D::run() {
    // ****************************** Square Start ******************************
    float square_vertices[] = {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int square_indices[] = {
            0, 1, 2, 0, 3, 2
    };
    objects square;
    {
        glGenVertexArrays(1, &square.vao);
        glGenBuffers(1, &square.vbo);
        glGenBuffers(1, &square.ebo);
        glBindVertexArray(square.vao);
        glBindBuffer(GL_ARRAY_BUFFER, square.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    Shader squareShader("basicTexture.shader");
    // ****************************** Square End ******************************


    float cube_vertices[] = {
            //position           //normal             //texture

            //front face
            -0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 0.0f, 0.0f,
            +0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 0.0f, 0.0f,
            -0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 0.0f, 1.0f,
            +0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 1.0f, 1.0f,
            //right face
            +0.5f, -0.5f, +0.5f, +1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
            +0.5f, -0.5f, -0.5f, +1.0f, +0.0f, +0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f, +1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
            +0.5f, -0.5f, +0.5f, +1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
            +0.5f, +0.5f, +0.5f, +1.0f, +0.0f, +0.0f, 0.0f, 1.0f,
            +0.5f, +0.5f, -0.5f, +1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
            //rear face
            +0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 1.0f, 0.0f,
            -0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 1.0f, 1.0f,
            +0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 0.0f, 0.0f,
            +0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 1.0f, 1.0f,
            //left face
            -0.5f, -0.5f, -0.5f, -1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, +0.5f, -1.0f, +0.0f, +0.0f, 1.0f, 0.0f,
            -0.5f, +0.5f, +0.5f, -1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
            -0.5f, +0.5f, -0.5f, -1.0f, +0.0f, +0.0f, 0.0f, 1.0f,
            -0.5f, +0.5f, +0.5f, -1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
            //bottom
            -0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, 1.0f, 0.0f,
            +0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, 0.0f, 0.0f,
            +0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, 0.0f, 1.0f,
            +0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, 1.0f, 1.0f,
            //top
            -0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, 0.0f, 0.0f,
            -0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, 1.0f, 1.0f,
            -0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, 0.0f, 0.0f,
            +0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, 0.0f, 1.0f,
            +0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, 1.0f, 1.0f};


    objects cube;
    {
        glGenVertexArrays(1, &cube.vao);
        glGenBuffers(1, &cube.vbo);
        glGenBuffers(1, &cube.ebo);
        glBindVertexArray(cube.vao);
        glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void* )0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void* )(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void* )(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    // ****************************** CUBE END ******************************

    //cubeShader
    Shader cubeShader("plainCube.shader");
    glm::vec3 lightPos(-25.0f, 25.0f, 25.0f);

    //model
    Shader modelShader("Model.shader");
    Model house("../res/objects/OBJ/Room.obj");
    //projection view matrices init
    glm::mat4 projection,view, model, transform;

    float currentFrame;
    // ****************************** LOOP ******************************
    while (!glfwWindowShouldClose(m_window))
    {
        // frame time logic
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - prevFrame;
        prevFrame = currentFrame;

        processEvent();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //setup camera
        if(!ortho) {
            projection = glm::perspective(glm::radians(camera.Zoom), (float) m_width / (float) m_height, 0.1f, 280.0f);
        }
        else{
            projection=glm::ortho(-60.0,60.0,-60.0,60.0,0.0,100.0);
        }
        //projection = glm::ortho(-100.0f, 100.0f,-100.0f, 100.0f,-100.0f, 100.0f);
        view = camera.GetViewMatrix();


        //light
        {
            model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.2f));
            model = glm::translate(model, lightPos / 0.2f);
            transform = projection * view * model;
            cubeShader.use();
            cubeShader.setMat4("transform", transform);
            glBindVertexArray(cube.vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //model
        {
            modelShader.use();

                model = glm::mat4(1.0f);
                // model = glm::translate(model, glm::vec3(10.0f, 2.0f, 0.0f));
                // model = glm::scale(model, glm::vec3(2.0f));
                transform = projection * view * model;
                modelShader.setMat4("transform", transform);
                modelShader.setMat4("model", model);
                modelShader.setVec3("lightPos", lightPos);
                modelShader.setVec3("viewPos", camera.Position);
                // ground.Draw(modelShader);
                house.Draw(modelShader);

        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
        // exit(0);
    }
}

void Renderer3D::processEvent()
{
    if ( glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    if ( glfwGetKey(m_window, GLFW_KEY_M) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if ( glfwGetKey(m_window, GLFW_KEY_N) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if ( glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS )
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS )
        camera.ProcessKeyboard(LEFT, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS )
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS )
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS )
        camera.ProcessKeyboard(UP, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS )
        camera.ProcessKeyboard(DOWN, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_O) == GLFW_PRESS )
        ortho=true;

    if ( glfwGetKey(m_window, GLFW_KEY_P) == GLFW_PRESS )
        ortho=false;

}
int main()
{
    Renderer3D Renderer3D(1920, 1024, "3DRenderer");
    Renderer3D.run();
    return 0;
}