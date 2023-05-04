#pragma once

#include <iostream>
#include <cstring>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "definitions.hpp"

class Window
{
public:
    Window();
    Window(int width, int height, const char *title);

    GLFWwindow *GetWindow() { return window; }

    void Update();
    bool IsOpen();
    
    ~Window();
private:
    GLFWwindow *window = nullptr;

    int width;
    int height;
    const char *title;

    const char *defaultTitle = "COMRADE Dev-Build - " PLATFORM_NAME;

    // Make the initial window 90% of the user's screen
    int startWidth;
    int startHeight;

    // Position window in the center of the screen
    int startX;
    int startY;
};
