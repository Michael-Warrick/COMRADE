#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "gameObject.hpp"

class Scene
{
public:
    Scene();
    ~Scene();

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void RemoveGameObject(std::shared_ptr<GameObject> gameObject);
    std::shared_ptr<GameObject> GetGameObject(std::string name);
    std::vector<std::shared_ptr<GameObject>> GetGameObjects();

    void SetDepthBuffer(bool depthBuffer);
    bool GetDepthBufferBool() { return renderDepth; }

    glm::vec3 GetDirectionalLightRotation();
    void SetDirectionalLightRotation(glm::vec3 rotation);

    glm::vec3 GetDirectionalLightAmbient();

    glm::vec3 GetViewportCameraPosition();
    std::vector<Model> GetModelsInScene();
    std::vector<Model> GetModelsInProject();

    std::vector<std::string> GetModelNames();

private:
    std::vector<std::string> getFilesInDirectory(std::string directory, std::string extension);
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    bool renderDepth = false;

    glm::vec3 directionalLightRotation = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 directionalLightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);

    glm::vec3 viewportCameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

    std::string assetsPath = "engine/resources/models/";

};