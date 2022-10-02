#include "definitions.hpp"

class UI
{
private:
    void InitDPIScale(float scale, ImFont*& smallFont, ImFont*& fixedWidthFont, ImFont*& largeFont);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool renderWireframe = false;
    bool renderPoints = false;
    bool hello = false;

    float dpiScale = 1.0f;

    ImVec4 offset = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
public:
    UI(GLFWwindow* window, const char* glVersion);
    void Update();
    void Render(GLFWwindow* window);
    ImVec4 GetOffset();
    void Shutdown();
};

// void InitDPIScale(float scale, ImFont*& smallFont, ImFont*& fixedWidthFont, ImFont*& largeFont) 
// {
    
// }