#include "scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
    gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i] == gameObject)
        {
            gameObjects.erase(gameObjects.begin() + i);
            break;
        }
    }
}

std::shared_ptr<GameObject> Scene::GetGameObject(std::string name)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i]->GetName() == name)
        {
            return gameObjects[i];
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects()
{
    return gameObjects;
}

void Scene::SetDepthBuffer(bool depthBuffer)
{
    this->renderDepth = depthBuffer;
}

glm::vec3 Scene::GetDirectionalLightRotation()
{
    return directionalLightRotation;
}

void Scene::SetDirectionalLightRotation(glm::vec3 rotation)
{
    directionalLightRotation = rotation;
}

glm::vec3 Scene::GetDirectionalLightAmbient()
{
    return directionalLightAmbient;
}

glm::vec3 Scene::GetViewportCameraPosition()
{
    return viewportCameraPosition;
}

std::vector<Model> Scene::GetModelsInScene()
{
    std::vector<Model> models;
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i]->GetComponent<MeshRenderer>()->GetModel() != nullptr)
        {
            models.push_back(*gameObjects[i]->GetComponent<MeshRenderer>()->GetModel());
        }
    }
    return models;
}


// for a given directory and extension, return a list of files in that directory and its subdirectories with that extension.
std::vector<std::string> Scene::getFilesInDirectory(std::string directory, std::string extension)
{
    std::vector<std::string> files;

    for (const auto & directoryEntry : std::filesystem::directory_iterator(directory))
    {
        if (directoryEntry.is_directory())
        {
            for (const auto & fileEntry : std::filesystem::directory_iterator(directoryEntry.path()))
            {
                if (fileEntry.path().extension() == extension)
                {
                    files.push_back(fileEntry.path().string());
                }
            }
        }
    }
    return files;
}

std::vector<Model> Scene::GetModelsInProject()
{
    std::vector<Model> models;
    std::vector<std::string> modelPaths = getFilesInDirectory(assetsPath, ".obj");
    for (int i = 0; i < modelPaths.size(); i++)
    {
        Model model = Model(modelPaths[i].c_str());
        models.push_back(model);
    }
    return models;
}

std::vector<std::string> Scene::GetModelNames()
{
    std::vector<std::string> modelNames = getFilesInDirectory(assetsPath, ".obj");
    return modelNames;
}