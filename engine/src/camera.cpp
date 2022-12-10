#include "camera.hpp"

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraUp, float cameraYaw, float cameraPitch, float cameraMovementSpeed, float cameraMouseSensitivity, float cameraFOV) 
{
    position = cameraPosition;
    worldUp = cameraUp;
    yaw = cameraYaw;
    pitch = cameraPitch;

    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float cameraYaw, float cameraPitch, float cameraMovementSpeed, float cameraMouseSensitivity, float cameraFOV) 
{
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    yaw = cameraYaw;
    pitch = cameraPitch;
    
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    if (direction == FORWARD)
    {
        position += front * velocity;
    }

    if (direction == BACKWARD)
    {
        position -= front * velocity;
    }
    
    if (direction == LEFT)
    {
        position -= right * velocity;
    }

    if (direction == RIGHT)
    {
        position += right * velocity;
    }

    // position.y = 0.0f;
    
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }
        
        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}