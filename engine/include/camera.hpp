#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vector>

enum Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera() = default;
    Camera(glm::vec3 cameraPosition, glm::vec3 cameraUp, float cameraYaw, float cameraPitch, float cameraMovementSpeed, float cameraMouseSensitivity, float cameraFOV, float cameraHorizontalResolution, float cameraVerticalResolution, float cameraNearPlane, float cameraFarPlane);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float cameraYaw, float cameraPitch, float cameraMovementSpeed, float cameraMouseSensitivity, float cameraFOV);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    void ProcessKeyboard(Movement direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch);

    glm::vec3 position;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw = -90.0f;
    float pitch = 0.0f;

    float movementSpeed = 2.5f;
    float mouseSensitivity = 0.1f;
    float fov = 75.0f;
    float horizontalResolution = 1280.0f;
    float verticalResolution = 720.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;

private:
    void updateCameraVectors();
};
