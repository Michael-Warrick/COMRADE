#include "definitions.hpp"

class UI
{
private:
    void InitDPIScale(float scale, ImFont*& smallFont, ImFont*& fixedWidthFont, ImFont*& largeFont);

    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool renderWireframe = false;
    bool renderPoints = false;
    bool hello = false;
    bool vSyncEnabled = true;

    float dpiScale = 1.0f;

    ImVec4 scaleOffset = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    ImVec4 rotateOffset = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 translateOffset = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    float mixAmount = 0.2f;

public:
    UI(GLFWwindow* window, const char* glVersion);
    void Update();
    void Render(GLFWwindow* window);

    void MenuBar();
    void RenderOptionsWindow();
    void TransformComponentWindow();
    
    ImVec4 GetTranslationOffset();
    ImVec4 GetRotationOffset();
    ImVec4 GetScaleOffset();
    float GetMixAmount();

    void Shutdown();
};

// void InitDPIScale(float scale, ImFont*& smallFont, ImFont*& fixedWidthFont, ImFont*& largeFont) 
// {
    
// }