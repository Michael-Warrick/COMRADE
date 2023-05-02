#pragma once

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ui.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "framebuffer.hpp"
#include "window.hpp"
#include "renderer.hpp"

#include "definitions.hpp"

class Application
{
public:
    Application();
    ~Application();

    void Run();
private:
    void InitUI();

    void EditorLoop();

    void Start();
    void PhysicsUpdate();
    void Update();
    void RenderScene();
    void DrawGizmos();
    void DrawUI();
    
    Window platformWindow;
    
    Renderer renderer;

    bool editorWindowIsOpen = true;
    bool gameIsRunning = false;
};