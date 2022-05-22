#include "Camera.hpp"

#include <iostream>

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

Camera::Camera( float posX, float posY, float posZ) 
{
    Position = glm::vec3(posX, posY, posZ);
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Yaw = YAW;
    Pitch = PITCH;
    Zoom = ZOOM;
    FlyMode = false;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard( CameraMovement direction, float deltaTime )
{
    velocity = MovementSpeed * deltaTime;
    //camera movement key events
    if ( direction == FORWARD )
        Position += Front * velocity;
    if ( direction == BACKWARD )
        Position -= Front * velocity;
    if ( direction == LEFT )
        Position -= Right * velocity;
    if ( direction == RIGHT )
        Position += Right * velocity;
    if ( direction == UP )
        Position += constUp * velocity;
    if ( direction == DOWN )
        Position -= constUp * velocity;
    // constrainHeight();
}

void Camera::constrainHeight()
{
    if ( !FlyMode )
        Position[1] = 1.5f;
    if ( Position[1] < 1.5f )
        Position[1] = 1.5f;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f; 
}