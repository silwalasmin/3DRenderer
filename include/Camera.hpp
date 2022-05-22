#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>
#include <vector>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

//default values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.0f;
const float ZOOM = 45.0f;
const float SENSITIVITY = 0.1f;
const float ROTATION_SENSITIVITY = 8.0f;
const glm::vec3 constUp = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera
{
public:
    glm::vec3 Position, Front, Up, Right, WorldUp;
    float Yaw, Pitch;
    float MouseSensitivity, Zoom;
    float MovementSpeed, velocity;
    bool FlyMode;

    Camera(float posX, float posY, float posZ);

    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void constrainHeight();
    void ProcessMouseMovement(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};

#endif 