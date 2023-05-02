#pragma once
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

// #include "ImGuizmo.h"

#include "definitions.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "framebuffer.hpp"
#include "scene.hpp"
#include "ui.hpp"
#include "window.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Init();
    void Render();
    void DrawGizmos();
    void DrawUI();

    Scene GetScene() { return scene; }
    void SetSceneInfo(Scene scene) { this->scene = scene; }

    std::unordered_map<std::string, Shader> GetShaders() { return shaders; }    
    
private:
    void GlobalSettings();
    void LoadMaterialShaders();
    void RenderScene();
    void RotateCameraAroundOrigin(Camera &camera, float angleDegrees);

    // List of all the shaders
    std::string shaderDirectory = "engine/resources/shaders/";
    std::unordered_map<std::string, Shader> shaders;

    Camera viewportCamera;
    Scene scene;
};