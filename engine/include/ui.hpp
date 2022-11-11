#include "definitions.hpp"

class UI
{
private:
    void InitDPIScale(float scale, ImFont*& smallFont, ImFont*& fixedWidthFont, ImFont*& largeFont);

    ImVec4 clearColor = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

    bool renderWireframe = false;
    bool renderPoints = false;
    bool hello = false;
    bool vSyncEnabled = true;

    float dpiScale = 1.0f;

    // Cube settings
    ImVec4 scaleOffset = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    ImVec4 rotateOffset = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 translateOffset = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    ImTextureID diffusePreviewTexture = 0;
    ImTextureID specularPreviewTexture = 0;

    float shininess = 32.0f;
    
    // LIGHT SETTINGS
    // Directional
    ImVec4 directionalLightRotation = ImVec4(-0.2f, -1.0f, -0.3f, 0.0f);
    ImVec4 directionalLightAmbient = ImVec4(0.05f, 0.05f, 0.05f, 0.0f);
    ImVec4 directionalLightDiffuse = ImVec4(0.4f, 0.4f, 0.4f, 0.0f);
    ImVec4 directionalLightSpecular = ImVec4( 0.5f, 0.5f, 0.5f, 0.0f);

    // Point
    bool enableSpotLight = false;
    ImVec4 pointLightAmbient = ImVec4(0.05f, 0.05f, 0.05f, 0.0f);
    ImVec4 pointLightDiffuse = ImVec4(0.8f, 0.8f, 0.8f, 0.0f);
    ImVec4 pointLightSpecular = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    float pointLightConstant = 1.0f;
    float pointLightLinear = 0.09f;
    float pointLightQuadratic = 0.032f;

    // Spotlight
    ImVec4 spotLightAmbient = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 spotLightDiffuse = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    ImVec4 spotLightSpecular = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    float spotLightConstant = 1.0f;
    float spotLightLinear = 0.09f;
    float spotLightQuadratic = 0.032f;
    float spotLightCutOff = 12.5f;
    float spotLightOuterCutOff = 15.0f;

public:
    UI(GLFWwindow* window, const char* glVersion);
    void Update();
    void Render(GLFWwindow* window);

    void MenuBar();
    void RenderOptionsWindow();
    void TransformComponentWindow();
    void LightSettingsWindow();

    // GETTERS    
    ImVec4 GetTranslationOffset();
    ImVec4 GetRotationOffset();
    ImVec4 GetScaleOffset();

    ImVec4 GetDirectionalLightRotation();
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

    // SETTERS
    void SetDiffusePreviewTexture(unsigned int texture);
    void SetSpecularPreviewTexture(unsigned int texture);

    void Shutdown();
};

// void InitDPIScale(float scale, ImFont*& smallFont, ImFont*& fixedWidthFont, ImFont*& largeFont) 
// {
    
// }