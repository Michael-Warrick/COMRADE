#include "window.hpp"

Window::Window()
{
    glfwInit();

    // Initialize GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Use OpenGL 3.1 ES if on Raspberry Pi
    if (strcmp(PLATFORM_NAME, "Raspberry Pi ARM64") == 0)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    }
    // Use OpenGL 4.1 Core on anything else
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    // Get the primary monitor
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    // Get the monitor's video mode
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

    // Set the window size to 90% of the monitor size
    width = static_cast<int>(videoMode->width * 0.9f);
    height = static_cast<int>(videoMode->height * 0.9f);

    // Center the window on the monitor
    startX = (videoMode->width - width) / 2;
    startY = (videoMode->height - height) / 2;

    // Try to create a window
    window = glfwCreateWindow(width, height, defaultTitle, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    // Set the window position and show it
    glfwSetWindowPos(window, startX, startY);
    glfwShowWindow(window);

    // Set the context to the window
    glfwMakeContextCurrent(window);

    // Enable vsync
    glfwSwapInterval(1);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

Window::Window(int width, int height, const char *title)
{
    glfwInit();

    // Use OpenGL 3.1 ES if on Raspberry Pi
    if (strcmp(PLATFORM_NAME, "Raspberry Pi ARM64") == 0)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    }

    // Use OpenGL 4.1 Core on anything else
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    // Try to create a window
    try
    {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
}

void Window::Update()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::IsOpen()
{
    return !glfwWindowShouldClose(window);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}