#pragma once

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

class TextureData
{
public:
    unsigned int Load(char const* path);
    unsigned int GetTexture();
    void Bind(int textureEnum);
    void Free();
private:
    unsigned int textureID;

    int width;
    int height;
    int nrComponents;

    unsigned char* data;
    GLenum format;
};