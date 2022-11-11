#include "definitions.hpp"
#include "ui.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "texture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.5f, 0.1, 75.0f);
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

    int resolutionX = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    int resolutionY = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    static const char* title = "M_Engine Dev-Build - " PLATFORM_NAME;

    GLFWwindow* window = glfwCreateWindow(resolutionX * 0.75, resolutionY * 0.75, title, NULL, NULL);
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

    glEnable(GL_DEPTH_TEST);

    UI ui(window, "#version 410");

    Shader cubeShader("engine/resources/shaders/color-vertex.glsl", "engine/resources/shaders/color-fragment.glsl");
    Shader lightShader("engine/resources/shaders/light-vertex.glsl", "engine/resources/shaders/light-fragment.glsl");

    Texture crateDiffuseTexture;
    Texture crateSpecularTexture;

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    crateDiffuseTexture.Load("engine/resources/img/textures/crate/crate-diffuse.png");
    crateSpecularTexture.Load("engine/resources/img/textures/crate/crate-specular.png");
    
    cubeShader.Use();
    cubeShader.SetInt("material.diffuse", 0);
    cubeShader.SetInt("material.specular", 1);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        ui.Update();

        // Light + Cube positions
        cubeShader.Use();
        cubeShader.SetVec3("viewPosition", camera.position);

        // Directional light
        cubeShader.SetVec3("directionalLight.direction", glm::vec3(ui.GetDirectionalLightRotation().x, ui.GetDirectionalLightRotation().y, ui.GetDirectionalLightRotation().z));
        cubeShader.SetVec3("directionalLight.ambientIntensity", glm::vec3(ui.GetDirectionalLightAmbient().x, ui.GetDirectionalLightAmbient().y,  ui.GetDirectionalLightAmbient().z));
        cubeShader.SetVec3("directionalLight.diffuseIntenstiy", glm::vec3(ui.GetDirectionalLightDiffuse().x, ui.GetDirectionalLightDiffuse().y, ui.GetDirectionalLightDiffuse().z));
        cubeShader.SetVec3("directionalLight.specularIntensity", glm::vec3(ui.GetDirectionalLightSpecular().x, ui.GetDirectionalLightSpecular().y, ui.GetDirectionalLightSpecular().z));

        // Point Lights
        cubeShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
        cubeShader.SetVec3("pointLights[0].ambientIntensity", glm::vec3(ui.GetPointLightAmbient().x, ui.GetPointLightAmbient().y, ui.GetPointLightAmbient().z));
        cubeShader.SetVec3("pointLights[0].diffuseIntensity", glm::vec3(ui.GetPointLightDiffuse().x, ui.GetPointLightDiffuse().y, ui.GetPointLightDiffuse().z));
        cubeShader.SetVec3("pointLights[0].specularIntensity", glm::vec3(ui.GetPointLightSpecular().x, ui.GetPointLightSpecular().y, ui.GetPointLightSpecular().z));
        cubeShader.SetFloat("pointLights[0].constant", ui.GetPointLightConstant());
        cubeShader.SetFloat("pointLights[0].linear", ui.GetPointLightLinear());
        cubeShader.SetFloat("pointLights[0].quadratic", ui.GetPointLightQuadratic());

        cubeShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
        cubeShader.SetVec3("pointLights[1].ambientIntensity", glm::vec3(ui.GetPointLightAmbient().x, ui.GetPointLightAmbient().y, ui.GetPointLightAmbient().z));
        cubeShader.SetVec3("pointLights[1].diffuseIntensity", glm::vec3(ui.GetPointLightDiffuse().x, ui.GetPointLightDiffuse().y, ui.GetPointLightDiffuse().z));
        cubeShader.SetVec3("pointLights[1].specularIntensity", glm::vec3(ui.GetPointLightSpecular().x, ui.GetPointLightSpecular().y, ui.GetPointLightSpecular().z));
        cubeShader.SetFloat("pointLights[1].constant", ui.GetPointLightConstant());
        cubeShader.SetFloat("pointLights[1].linear", ui.GetPointLightLinear());
        cubeShader.SetFloat("pointLights[1].quadratic", ui.GetPointLightQuadratic());

        cubeShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
        cubeShader.SetVec3("pointLights[2].ambientIntensity", glm::vec3(ui.GetPointLightAmbient().x, ui.GetPointLightAmbient().y, ui.GetPointLightAmbient().z));
        cubeShader.SetVec3("pointLights[2].diffuseIntensity", glm::vec3(ui.GetPointLightDiffuse().x, ui.GetPointLightDiffuse().y, ui.GetPointLightDiffuse().z));
        cubeShader.SetVec3("pointLights[2].specularIntensity", glm::vec3(ui.GetPointLightSpecular().x, ui.GetPointLightSpecular().y, ui.GetPointLightSpecular().z));
        cubeShader.SetFloat("pointLights[2].constant", ui.GetPointLightConstant());
        cubeShader.SetFloat("pointLights[2].linear", ui.GetPointLightLinear());
        cubeShader.SetFloat("pointLights[2].quadratic", ui.GetPointLightQuadratic());

        cubeShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
        cubeShader.SetVec3("pointLights[3].ambientIntensity", glm::vec3(ui.GetPointLightAmbient().x, ui.GetPointLightAmbient().y, ui.GetPointLightAmbient().z));
        cubeShader.SetVec3("pointLights[3].diffuseIntensity", glm::vec3(ui.GetPointLightDiffuse().x, ui.GetPointLightDiffuse().y, ui.GetPointLightDiffuse().z));
        cubeShader.SetVec3("pointLights[3].specularIntensity", glm::vec3(ui.GetPointLightSpecular().x, ui.GetPointLightSpecular().y, ui.GetPointLightSpecular().z));
        cubeShader.SetFloat("pointLights[3].constant", ui.GetPointLightConstant());
        cubeShader.SetFloat("pointLights[3].linear", ui.GetPointLightLinear());
        cubeShader.SetFloat("pointLights[3].quadratic", ui.GetPointLightQuadratic());

        // Spot Light
        cubeShader.SetBool("enableSpotLight", ui.GetSpotLightBool());
        cubeShader.SetVec3("spotLight.position", camera.position);
        cubeShader.SetVec3("spotLight.direction", camera.front);
        cubeShader.SetVec3("spotLight.ambientIntensity", glm::vec3(ui.GetSpotLightAmbient().x, ui.GetSpotLightAmbient().y, ui.GetSpotLightAmbient().z));
        cubeShader.SetVec3("spotLight.diffuseIntensity", glm::vec3(ui.GetSpotLightDiffuse().x, ui.GetSpotLightDiffuse().y, ui.GetSpotLightDiffuse().z));
        cubeShader.SetVec3("spotLight.specularIntensity", glm::vec3(ui.GetSpotLightSpecular().x, ui.GetSpotLightSpecular().y, ui.GetSpotLightSpecular().z));
        cubeShader.SetFloat("spotLight.constant", ui.GetSpotLightConstant());
        cubeShader.SetFloat("spotLight.linear", ui.GetSpotLightLinear());
        cubeShader.SetFloat("spotLight.quadratic", ui.GetSpotLightQuadratic());
        cubeShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(ui.GetSpotLightCutOff())));
        cubeShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(ui.GetSpotLightOuterCutOff())));

        // Material properties
        cubeShader.SetFloat("material.shininess", ui.GetShininess());

        // View/Projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        cubeShader.SetMat4("projection", projection);
        cubeShader.SetMat4("view", view);

        // World transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normalModel = glm::transpose(glm::inverse(glm::mat3(1.0f)));
        cubeShader.SetMat4("model", model);
        cubeShader.SetMat3("normalModel", normalModel);

        crateDiffuseTexture.Bind(0);
        crateSpecularTexture.Bind(1);
        ui.SetDiffusePreviewTexture(crateDiffuseTexture.GetTexture());
        ui.SetSpecularPreviewTexture(crateSpecularTexture.GetTexture());

        // Render crates
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++) 
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader.SetMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Render lamp object
        lightShader.Use();
        lightShader.SetMat4("projection", projection);
        lightShader.SetMat4("view", view);

        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));

            lightShader.SetMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        ui.Render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    
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