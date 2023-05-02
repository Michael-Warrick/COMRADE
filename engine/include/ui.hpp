#pragma once

#include <iostream>
#include <cmath>
#include <regex>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../external/imgui-docking/imgui.h"
#include "../external/imgui-docking/backends/imgui_impl_glfw.h"
#include "../external/imgui-docking/backends/imgui_impl_opengl3.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../external/imgui-docking/imgui_internal.h"

#include "../external/nativefiledialog-extended/src/include/nfd.h"

#include "texture.hpp"
#include "scene.hpp"
#include "gameObject.hpp"

class UI
{
public:
    UI() = default;
    UI(GLFWwindow* window, const char* glVersion);
    ~UI();

    void Update();
    void Render();

    void MenuBar();
    void InteractionsBar();
    void RenderOptionsOverlay();
    void Inspector();
    void Viewport();
    void SceneHierarchy();
    void ProjectFolder();
    void Console();

    // COMPONENT WINDOWS
    void TransformComponentWindow(GameObject gameObject);
    void MeshRendererComponentWindow(GameObject gameObject);
    void DirectionalLightComponentWindow(GameObject gameObject);
    void ScriptComponentWindow(GameObject gameObject);
    // void CameraComponentWindow(GameObject gameObject);
    // void LightComponentWindow(GameObject gameObject);

    unsigned int viewportTexture;
    ImVec2 viewportSize;


    bool showRenderOptionsOverlay = false;
    float globalFontSize = 5.5f;
    float globalFontNormalizerConstant = 0.05f;
    std::string console_output;

    // GETTERS    
    bool GetDepthBufferBool();
    float GetViewportWidth();
    float GetViewportHeight();

    ImVec4 GetTranslationOffset();
    ImVec4 GetRotationOffset();
    ImVec4 GetScaleOffset();

    ImVec4 GetCubePositionOffset();
    ImVec4 GetCubeRotationOffset();
    ImVec4 GetCubeScaleOffset();

    // ImVec4 GetDirectionalLightRotation();
    ImVec4 GetDirectionalLightAmbient();
    ImVec4 GetDirectionalLightDiffuse();
    ImVec4 GetDirectionalLightSpecular();

    ImVec4 GetPointLightAmbient();
    ImVec4 GetPointLightDiffuse();
    ImVec4 GetPointLightSpecular();
    float GetPointLightConstant();
    float GetPointLightLinear();
    float GetPointLightQuadratic();

    bool GetSpotLightBool();
    ImVec4 GetSpotLightAmbient();
    ImVec4 GetSpotLightDiffuse();
    ImVec4 GetSpotLightSpecular();
    float GetSpotLightConstant();
    float GetSpotLightLinear();
    float GetSpotLightQuadratic();
    float GetSpotLightCutOff();
    float GetSpotLightOuterCutOff();

    float GetShininess();

    bool GetGameState();

    Scene GetScene() { return scene; }

    // SETTERS
    void SetDiffusePreviewTexture(unsigned int texture);
    void SetSpecularPreviewTexture(unsigned int texture);
    void SetViewportTexture(unsigned int colorBufferTexture);
    void SetSceneInfo(Scene scene);
    void SetShaderInfo(std::unordered_map<std::string, Shader> shaders);

    // HELPERS
    void PrintToConsole(const char* const message);
    bool DragFloatN_Colored(const char* label, float* v, int components, float v_speed, float v_min, float v_max, const char* display_format, float power);
    ImVec4 hexToImVec4(std::string hex);

    void Shutdown();
private:
    std::string labelPrefix(const char* const label);
    bool ButtonCenteredOnLine(const char* label, ImVec2 size, float alignment);

    Scene scene;
    std::unordered_map<std::string, Shader> shaders;

    TextureData pauseButtonIcon;
    ImTextureID pauseButtonIconID;

    TextureData playButtonIcon;
    ImTextureID playButtonIconID;
    
    TextureData removeButtonIcon;
    ImTextureID removeButtonIconID;

    float my_value = 0.5f;

    ImVec4 clearColor = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

    bool renderWireframe = false;
    bool renderPoints = false;
    bool renderDepthBuffer = false;
    bool vSyncEnabled = true;

    bool gameIsRunning = false;

    ImVec2 addComponentButtonPos, addComponentButtonSize;
    bool showAvailableComponentsWindow = false;
    ImVec2 componentSelectionWindowPos, componentSelectionWindowSize;

    bool showCppScriptCreateModal = false;
};