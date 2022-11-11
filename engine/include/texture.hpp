#include "definitions.hpp"

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