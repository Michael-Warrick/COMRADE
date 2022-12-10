#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

class Texture 
{
private:
    unsigned int textureID;

    int width;
    int height;
    int nrComponents;

    unsigned char* data;
    GLenum format;

public:
    unsigned int Load(char const* path);
    unsigned int GetTexture();
    void Bind(int textureEnum);
};