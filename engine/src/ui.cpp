#include "ui.hpp"

UI::UI(GLFWwindow* window, const char* glVersion)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 15.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glVersion);
}

void UI::Update() 
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    MenuBar();
    RenderOptionsWindow();
    TransformComponentWindow();
    LightSettingsWindow();
    
    // ImGui::ShowDemoWindow();

    glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void UI::MenuBar() 
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "CTRL+O")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void UI::RenderOptionsWindow() 
{
    ImGui::Begin("Rendering Options");
        ImGui::ColorEdit3("Clear Color", (float*)&clearColor);
        ImGui::Separator();
        ImGui::Checkbox("Wireframe", &renderWireframe);
        ImGui::SameLine();
        ImGui::Checkbox("Points", &renderPoints);

        if (renderWireframe) { glLineWidth(3.0); glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
        else if (renderPoints) { glPointSize(5.0); glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
        else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Checkbox("Enable V-Sync", &vSyncEnabled);

        if (vSyncEnabled) { glfwSwapInterval(1); }
        else { glfwSwapInterval(0); }
    ImGui::End();
}

void UI::TransformComponentWindow() 
{
    // Pushing of the ID allows for having a DragFloat3 of the same label, i.e. none.
    ImGui::Begin("Cube Properties");
        ImGui::PushID(0);
        ImGui::Text("Translation");
        ImGui::SameLine();
        ImGui::DragFloat3("", (float *)&translateOffset, 0.01f);
        ImGui::PopID();

        ImGui::PushID(1);
        ImGui::Text("Rotation   ");
        ImGui::SameLine();
        ImGui::DragFloat3("", (float *)&rotateOffset, 0.03f);
        ImGui::PopID();

        ImGui::PushID(2);
        ImGui::Text("Scale      ");
        ImGui::SameLine();
        ImGui::DragFloat3("", (float *)&scaleOffset, 0.01f);
        ImGui::PopID();

        ImGui::Separator();
        
        ImGui::Text("Texture Map Preview");

        ImVec2 uvMin = ImVec2(0.0f, 1.0f);
        ImVec2 uvMax = ImVec2(1.0f, 0.0f);
        ImVec4 tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImVec4 borderColor = ImVec4(0.247f, 0.247f, 0.282f, 1.0f);

        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImGuiIO io = ImGui::GetIO();

        ImGui::Image(diffusePreviewTexture, ImVec2(100, 100), uvMin, uvMax, tintColor, borderColor);
        if (ImGui::IsItemHovered())
        {
            // Preview needs fixing as it is incorrect!
            ImGui::BeginTooltip();
                float region_sz = 32.0f;
                float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
                float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
                float zoom = 4.0f;

                if (region_x < 0.0f) { region_x = 0.0f; }
                else if (region_x > 100.0f - region_sz) { region_x = 100.0f - region_sz; }
                if (region_y < 0.0f) { region_y = 0.0f; }
                else if (region_y > 100.0f - region_sz) { region_y = 100.0f - region_sz; }

                ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
                ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
                ImVec2 uv0 = ImVec2((region_x) / 100.0f, (region_y + region_sz) / 100.0f);
                ImVec2 uv1 = ImVec2((region_x + region_sz) / 100.0f, (region_y) / 100.0f);

                ImGui::Image(diffusePreviewTexture, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tintColor, borderColor);
            ImGui::EndTooltip();
        }
        ImGui::SameLine();
        ImGui::Text("Diffuse");

        ImGui::Image(specularPreviewTexture, ImVec2(100, 100), uvMin, uvMax, tintColor, borderColor);
        ImGui::SameLine();
        ImGui::Text("Specular");

        ImGui::Separator();

        ImGui::SliderFloat("Shininess", &shininess, 32.0f, 256.0f, "%.1f");
    ImGui::End();
}

void UI::LightSettingsWindow() 
{
    ImGui::Begin("Light Properties");
        ImGui::Text("Directional Light Properties");
        ImGui::DragFloat3("Rotation", (float*)&directionalLightRotation, 0.1f, -180.0f, 180.0f, "%.1f");
        ImGui::DragFloat3("Ambient Intensity", (float*)&directionalLightAmbient, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::DragFloat3("Diffuse Intensity", (float*)&directionalLightDiffuse, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::DragFloat3("Specular Intensity", (float*)&directionalLightSpecular, 0.1f, 0.0f, 1.0f, "%.1f");

        ImGui::Separator();

        ImGui::Text("Point Light Properties");
        ImGui::DragFloat3("Ambient Intensity", (float*)&pointLightAmbient, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::DragFloat3("Diffuse Intensity", (float*)&pointLightDiffuse, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::DragFloat3("Specular Intensity", (float*)&pointLightSpecular, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::SliderFloat("Constant", &pointLightConstant, 0.0f, 1.0f, "%.01f");
        ImGui::SliderFloat("Linear", &pointLightLinear, 0.0f, 1.0f, "%.01f");
        ImGui::SliderFloat("Quadratic", &pointLightQuadratic, 0.0f, 1.0f, "%.01f");

        ImGui::Separator();

        ImGui::Text("Spot Light Properties");
        ImGui::Checkbox("Enable Spot Light", &enableSpotLight);
        ImGui::DragFloat3("Ambient Intensity", (float*)&spotLightAmbient, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::DragFloat3("Diffuse Intensity", (float*)&spotLightDiffuse, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::DragFloat3("Specular Intensity", (float*)&spotLightSpecular, 0.1f, 0.0f, 1.0f, "%.1f");
        ImGui::SliderFloat("Constant", &spotLightConstant, 0.0f, 1.0f, "%.01f");
        ImGui::SliderFloat("Linear", &spotLightLinear, 0.0f, 1.0f, "%.01f");
        ImGui::SliderFloat("Quadratic", &spotLightQuadratic, 0.0f, 1.0f, "%.01f");
        ImGui::SliderFloat("CutOff Angle", &spotLightCutOff, 0.0f, 100.0f, "%.1f");
        ImGui::SliderFloat("Outer CutOff Angle", &spotLightOuterCutOff, 0.0f, 100.0f, "%.1f");
    ImGui::End();
}

void UI::Render(GLFWwindow* window)
{
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

// GETTERS
ImVec4 UI::GetTranslationOffset() { return translateOffset; }
ImVec4 UI::GetRotationOffset() { return rotateOffset; }
ImVec4 UI::GetScaleOffset() { return scaleOffset; }

ImVec4 UI::GetDirectionalLightRotation() { return directionalLightRotation; }
ImVec4 UI::GetDirectionalLightAmbient() { return directionalLightAmbient; }
ImVec4 UI::GetDirectionalLightDiffuse() { return directionalLightDiffuse; }
ImVec4 UI::GetDirectionalLightSpecular() { return directionalLightSpecular; }

ImVec4 UI::GetPointLightAmbient() { return pointLightAmbient; }
ImVec4 UI::GetPointLightDiffuse() { return pointLightDiffuse; }
ImVec4 UI::GetPointLightSpecular() { return pointLightSpecular; }
float UI::GetPointLightConstant() { return pointLightConstant; }
float UI::GetPointLightLinear() { return pointLightLinear; }
float UI::GetPointLightQuadratic() { return pointLightQuadratic; }

bool UI::GetSpotLightBool() { return enableSpotLight; }
ImVec4 UI::GetSpotLightAmbient() { return spotLightAmbient; }
ImVec4 UI::GetSpotLightDiffuse() { return spotLightDiffuse; }
ImVec4 UI::GetSpotLightSpecular() { return spotLightSpecular; }
float UI::GetSpotLightConstant() { return spotLightConstant; }
float UI::GetSpotLightLinear() { return spotLightLinear; }
float UI::GetSpotLightQuadratic() { return spotLightQuadratic; }
float UI::GetSpotLightCutOff() { return spotLightCutOff; }
float UI::GetSpotLightOuterCutOff() { return spotLightOuterCutOff; }

float UI::GetShininess() { return shininess; }

// SETTERS
void UI::SetDiffusePreviewTexture(unsigned int texture) { diffusePreviewTexture = (ImTextureID)(intptr_t)texture; }
void UI::SetSpecularPreviewTexture(unsigned int texture) { specularPreviewTexture = (ImTextureID)(intptr_t)texture; }

void UI::Shutdown() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}