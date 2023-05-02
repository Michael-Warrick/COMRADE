#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
public:
    Framebuffer() = default;
    Framebuffer(int horizontalResolution, int verticalResolution);
    void Bind();
    void Unbind();
    void Clear();
    void BindColorTexture();
    void UnbindColorTexture();

    unsigned int GetColorTexture();
private:
    unsigned int framebuffer;
    unsigned int colorBuffer;
    unsigned int renderBuffer;
};
