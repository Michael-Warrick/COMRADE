#include "renderer.hpp"

Renderer::Renderer()
{
    Init();
}

Renderer::~Renderer()
{
}

void Renderer::GlobalSettings()
{
    // GLOBAL DEPTH SETTINGS
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // // GLOBAL STENCIL SETTINGS
    // glEnable(GL_STENCIL_TEST);
    // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // GLOBAL BLEND SETTINGS
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::LoadMaterialShaders()
{
    for (const auto &entry : std::filesystem::directory_iterator(shaderDirectory))
    {
        std::string fileName = entry.path().filename().string();
        std::string shaderName = fileName.substr(0, fileName.find_last_of("."));
        std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);
        if (fileExtension == "vert" || fileExtension == "frag")
        {
            if (shaders.find(shaderName) == shaders.end())
            {
                Shader shader(shaderDirectory + shaderName + ".vert", shaderDirectory + shaderName + ".frag");
                shaders.insert({shaderName, shader});
            }
        }
    }
}

void Renderer::Init()
{
    LoadMaterialShaders();
    GlobalSettings();

    scene.AddGameObject(std::make_shared<GameObject>("Directional Light"));
    scene.GetGameObject("Directional Light")->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    scene.GetGameObject("Directional Light")->AddComponent(std::make_shared<DirectionalLight>(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));

    scene.AddGameObject(std::make_shared<GameObject>("cm_flatgrass"));
    scene.GetGameObject("cm_flatgrass")->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    scene.GetGameObject("cm_flatgrass")->AddComponent(std::make_shared<MeshRenderer>(std::make_shared<Model>("engine/resources/models/cm_flatgrass/cm_flatgrass.obj"), std::make_shared<Shader>(shaders.at("default"))));

    viewportCamera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.5f, 0.1f, 75.0f, 1920.0f, 1080.0f, 0.1f, 1000.0f);
}

void Renderer::RenderScene()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    std::vector<std::shared_ptr<GameObject>> gameObjects = scene.GetGameObjects();
    for (int i = 0; i < gameObjects.size(); i++)
    {
        std::shared_ptr<GameObject> gameObject = gameObjects[i];
        std::vector<std::shared_ptr<Component>> components = gameObject->GetComponents();
        for (int j = 0; j < components.size(); j++)
        {
            std::shared_ptr<Component> component = components[j];
            if (component->GetType() == ComponentType::MeshRenderer && gameObject->IsActive())
            {
                std::shared_ptr<MeshRenderer> meshRenderer = std::dynamic_pointer_cast<MeshRenderer>(component);
                std::shared_ptr<Model> model = meshRenderer->GetModel();
                std::shared_ptr<Shader> shader = meshRenderer->GetShader();

                shader->Use();

                shader->SetBool("renderDepthBuffer", scene.GetDepthBufferBool());

                shader->SetVec3(
                    "directionalLight.direction",
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetDirection().x,
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetDirection().y,
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetDirection().z
                );

                shader->SetVec3(
                    "directionalLight.ambientIntensity", 
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetAmbient().x, 
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetAmbient().y, 
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetAmbient().z
                );

                shader->SetVec3(
                    "directionalLight.diffuseIntensity",
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetDiffuse().x, 
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetDiffuse().y, 
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetDiffuse().z
                );

                shader->SetVec3(
                    "directionalLight.specularIntensity",
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetSpecular().x, 
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetSpecular().y, 
                    scene.GetGameObject("Directional Light")->GetComponent<DirectionalLight>()->GetSpecular().z
                );

                shader->SetVec3("viewPosition", viewportCamera.position);
                shader->SetMat4("projection", viewportCamera.GetProjectionMatrix());
                shader->SetMat4("view", viewportCamera.GetViewMatrix());
                shader->SetMat4("model", gameObject->GetComponent<Transform>()->GetModelMatrix());

                model->Draw(*shader);
            }
        }
    }

    glDisable(GL_DEPTH_TEST);
}

void Renderer::RotateCameraAroundOrigin(Camera &camera, float angleDegrees)
{
    // Define the distance from the camera to the origin of the scene.
    float distance = glm::length(camera.position);

    // Define the angle of rotation around the Y-axis in radians.
    float angleRadians = glm::radians(angleDegrees);

    // Calculate the new camera position using spherical coordinates.
    float x = distance * sin(angleRadians);
    float y = camera.position.y;
    float z = distance * cos(angleRadians);
    camera.position = glm::vec3(x, y, z);

    // Calculate the new camera orientation by looking at the origin of the scene.
    camera.front = glm::normalize(glm::vec3(0.0f) - camera.position);
    camera.right = glm::normalize(glm::cross(camera.front, camera.worldUp));
    camera.up = glm::normalize(glm::cross(camera.right, camera.front));
}

void Renderer::Render()
{
    RenderScene();
    viewportCamera.position = glm::vec3(0.0f, 12.0f, 12.0f);
    RotateCameraAroundOrigin(viewportCamera, 45.0f * glfwGetTime() * 0.1f);
}

void Renderer::DrawGizmos()
{
    // // Get the currently active scene
    // Scene* scene = SceneManager::GetCurrentScene();

    // // Get the camera that's currently active in the scene
    // Camera* camera = scene->GetActiveCamera();

    // // If there is no active camera, don't draw any gizmos
    // if (!camera)
    // {
    //     return;
    // }

    // // Set up the view and projection matrices based on the active camera's position and orientation
    // glm::mat4 viewMatrix = camera->GetViewMatrix();
    // glm::mat4 projectionMatrix = camera->GetProjectionMatrix();

    // // Iterate over all game objects in the scene
    // for (auto& gameObject : scene->GetGameObjects())
    // {
    //     // If the game object doesn't have a transform component, skip it
    //     if (!gameObject->HasComponent<TransformComponent>())
    //     {
    //         continue;
    //     }

    //     // Get the transform component for the game object
    //     TransformComponent& transform = gameObject->GetComponent<TransformComponent>();

    //     // Calculate the model matrix for the game object based on its position and orientation
    //     glm::mat4 modelMatrix = transform.GetTransformMatrix();

    //     // Draw a gizmo for the game object using ImGuizmo
    //     ImGuizmo::SetOrthographic(false);
    //     ImGuizmo::SetDrawlist();
    //     ImGuizmo::SetRect(0, 0, 1920, 1080);
    //     ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), ImGuizmo::TRANSLATE, ImGuizmo::WORLD, glm::value_ptr(modelMatrix), nullptr, nullptr);

    //     // If the user has interacted with the gizmo, update the game object's position and orientation
    //     if (ImGuizmo::IsUsing())
    //     {
    //         glm::vec3 position, scale;
    //         glm::quat rotation;
    //         ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(modelMatrix), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

    //         transform.SetPosition(position);
    //         transform.SetRotation(rotation);
    //         transform.SetScale(scale);
    //     }
    // }
}
