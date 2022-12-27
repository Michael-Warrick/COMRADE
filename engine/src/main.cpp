#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ui.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"

#include "definitions.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 1.5f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.5f, 0.1, 75.0f);
float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;

bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool isRightClicking = false;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Make the initial window 75% of the user's screen
    int initialWindowSizeX = glfwGetVideoMode(glfwGetPrimaryMonitor())->width * 0.75;
    int initialWindowSizeY = glfwGetVideoMode(glfwGetPrimaryMonitor())->height * 0.75;

    static const char* title = "M_Engine Dev-Build - " PLATFORM_NAME;

    GLFWwindow* window = glfwCreateWindow(initialWindowSizeX, initialWindowSizeY, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // GLOBAL DEPTH SETTINGS
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // GLOBAL STENCIL SETTINGS
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // GLOBAL BLEND SETTINGS
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    UI ui(window, "#version 410");

    Shader outlineShader("engine/resources/shaders/stencil-vertex.glsl", "engine/resources/shaders/stencil-fragment.glsl");

    Shader galleryShader("engine/resources/shaders/vertex-shader.glsl", "engine/resources/shaders/fragment-shader.glsl");
    Model gallery("engine/resources/models/gallery/gallery.obj");

    Shader companionCubeShader("engine/resources/shaders/vertex-shader.glsl", "engine/resources/shaders/fragment-shader.glsl");
    Model companionCube("engine/resources/models/companion_cube/companion_cube.obj");

    Shader grassShader("engine/resources/shaders/billboard-vertex.glsl", "engine/resources/shaders/billboard-fragment.glsl");
    Model grassBillboard("engine/resources/models/realistic_grass/realistic_grass_tuff.obj");

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        ui.Update(window);

        // Allows for dynamic resolutions/aspect ratios
        int windowWidth;
        int windowHeight;
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // View/Projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        outlineShader.Use();
        outlineShader.SetMat4("view", view);
        outlineShader.SetMat4("projection", projection);

        // Tells stencil mask to ignore the rest of the scene
        glStencilMask(0x00);

        // Gallery
        galleryShader.Use();
        galleryShader.SetBool("renderDepthBuffer", ui.GetDepthBufferBool());
        galleryShader.SetVec3("directionalLight.direction", ui.GetDirectionalLightRotation().x, ui.GetDirectionalLightRotation().y, ui.GetDirectionalLightRotation().z);
        galleryShader.SetVec3("directionalLight.ambientIntensity", ui.GetDirectionalLightAmbient().x, ui.GetDirectionalLightAmbient().y, ui.GetDirectionalLightAmbient().z);
        galleryShader.SetVec3("directionalLight.diffuseIntensity", 0.5f, 0.5f, 0.5f);
        galleryShader.SetVec3("directionalLight.specularIntensity", 1.0f, 1.0f, 1.0f);
        galleryShader.SetVec3("viewPosition", camera.position);
        galleryShader.SetMat4("projection", projection);
        galleryShader.SetMat4("view", view);

        glm::mat4 galleryModel = glm::mat4(1.0f);
        galleryShader.SetMat4("model", galleryModel);
        gallery.Draw(galleryShader);

         // Grass
        std::vector<glm::vec3> vegetation 
        {
            glm::vec3(0.5f, 0.0f, -2.5f),
            glm::vec3( 0.4f, 0.0f, -3.0f),
            glm::vec3( 0.0f, 0.0f, -1.45f),
            glm::vec3(-0.1f, 0.0f, -2.48f),
            glm::vec3 (-0.3f, 0.0f, -3.52f)
        };

        grassShader.Use();
        grassShader.SetMat4("projection", projection);
        grassShader.SetMat4("view", view);

        for (unsigned int i = 0; i < vegetation.size(); i++)
        {
            glm::mat4 vegetationModelMat = glm::mat4(1.0f);
            vegetationModelMat = glm::translate(vegetationModelMat, vegetation[i]);
            grassShader.SetMat4("model", vegetationModelMat);
            grassBillboard.Draw(grassShader);
        }

        // Companion Cube - First render pass, drawing normally and writing to the stencil buffer
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        companionCubeShader.Use();
        companionCubeShader.SetBool("renderDepthBuffer", ui.GetDepthBufferBool());
        companionCubeShader.SetVec3("directionalLight.direction", ui.GetDirectionalLightRotation().x, ui.GetDirectionalLightRotation().y, ui.GetDirectionalLightRotation().z);
        companionCubeShader.SetVec3("directionalLight.ambientIntensity", ui.GetDirectionalLightAmbient().x, ui.GetDirectionalLightAmbient().y, ui.GetDirectionalLightAmbient().z);
        companionCubeShader.SetVec3("directionalLight.diffuseIntensity", 0.5f, 0.5f, 0.5f);
        companionCubeShader.SetVec3("directionalLight.specularIntensity", 1.0f, 1.0f, 1.0f);
        companionCubeShader.SetVec3("viewPosition", camera.position);
        companionCubeShader.SetMat4("projection", projection);
        companionCubeShader.SetMat4("view", view);
        glm::mat4 cubeModel = glm::mat4(1.0f);
        companionCubeShader.SetMat4("model", cubeModel);
        float moveSpeed = 3.0f;
        float superPosition = glm::sin(glfwGetTime() * moveSpeed) * 0.5f;
        cubeModel = glm::translate(cubeModel, glm::vec3(ui.GetCubePositionOffset().x, superPosition + ui.GetCubePositionOffset().y, ui.GetCubePositionOffset().z));
        float rotationSpeed = glfwGetTime() * 50.0f;
        cubeModel = glm::rotate(cubeModel, glm::radians(rotationSpeed + ui.GetCubeRotationOffset().x), glm::vec3(1.0f, 0.0f, 0.0f));
        cubeModel = glm::rotate(cubeModel, glm::radians(rotationSpeed + ui.GetCubeRotationOffset().y), glm::vec3(0.0f, 1.0f, 0.0f));
        cubeModel = glm::rotate(cubeModel, glm::radians(rotationSpeed + ui.GetCubeRotationOffset().z), glm::vec3(0.0f, 0.0f, 1.0f));
        cubeModel = glm::scale(cubeModel, glm::vec3(ui.GetCubeScaleOffset().x, ui.GetCubeScaleOffset().y, ui.GetCubeScaleOffset().z));
        companionCubeShader.SetMat4("model", cubeModel);
        companionCube.Draw(companionCubeShader);

        // Companion Cube - Second render pass, scaling up the model and drawing the size difference as a solid colour
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        float outlineScale = 1.05f;
        outlineShader.Use();
        outlineShader.SetMat4("model", cubeModel);
        cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, 0.0f, 0.0f));
        cubeModel = glm::rotate(cubeModel, glm::radians(ui.GetCubeRotationOffset().x), glm::vec3(1.0f, 0.0f, 0.0f));
        cubeModel = glm::rotate(cubeModel, glm::radians(ui.GetCubeRotationOffset().y), glm::vec3(0.0f, 1.0f, 0.0f));
        cubeModel = glm::rotate(cubeModel, glm::radians(ui.GetCubeRotationOffset().z), glm::vec3(0.0f, 0.0f, 1.0f));
        cubeModel = glm::scale(cubeModel, glm::vec3(outlineScale, outlineScale, outlineScale));
        outlineShader.SetMat4("model", cubeModel);
        companionCube.Draw(outlineShader);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        ui.Render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    ui.Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float zoomSpeed = 80.0f;

    if (isRightClicking)
    {
        // Movement
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(FORWARD, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(LEFT, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(RIGHT, deltaTime);
        }

        // Zoom - achieved by incrementing/decrementing FOV
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        {
            if (camera.fov >= 30.0f)
            {
                camera.fov -= zoomSpeed * deltaTime;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
        {
            if (camera.fov <= 75.0f)
            {
                camera.fov += zoomSpeed * deltaTime;
            }
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;

    if (isRightClicking)
    {
        camera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        isRightClicking = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        isRightClicking = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}