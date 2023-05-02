#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.hpp"
#include "shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
    Model() = default;
    Model(const char *path);
    void Draw(Shader &shader);
    std::string GetName();

    // Get textures
    std::vector<Texture> GetTextures();
private:
    void load(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);

    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    bool gammaCorrection;
};