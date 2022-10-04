#include "definitions.hpp"
#include "ui.hpp"
#include "shader.hpp"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    UI ui(window, "#version 410");
    Shader simpleShader("engine/resources/shaders/vertex-shader.glsl", "engine/resources/shaders/fragment-shader.glsl");

    float vertices[] = 
    {
        // positions         // texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = 
    {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int crateTexture;
    unsigned int decalTexture;

    glGenTextures(1, &crateTexture);
    glBindTexture(GL_TEXTURE_2D, crateTexture); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("engine/resources/img/textures/crate-texture.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &decalTexture);
    glBindTexture(GL_TEXTURE_2D, decalTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("engine/resources/img/textures/MJW.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    simpleShader.Use();
    simpleShader.setInt("crateTexture", 0);
    simpleShader.setInt("decalTexture", 1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        ui.Update();

        simpleShader.setFloat("mixAmount", ui.GetMixAmount());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, crateTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, decalTexture);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(ui.GetTranslationOffset().x, ui.GetTranslationOffset().y, ui.GetTranslationOffset().z));
        trans = glm::rotate(trans, glm::radians(ui.GetRotationOffset().x), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(ui.GetScaleOffset().x, ui.GetScaleOffset().y, ui.GetScaleOffset().z));  

        // get matrix's uniform location and set matrix
        simpleShader.Use();
        unsigned int transformLoc = glGetUniformLocation(simpleShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // second transformation
        // ---------------------
        trans = glm::mat4(1.0f); // reset it to identity matrix
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = static_cast<float>(sin(glfwGetTime()));
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]); // this time take the matrix value array's first element as its memory pointer value

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ui.Render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
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
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}