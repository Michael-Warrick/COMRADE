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

    ImFont *mainfont = io.Fonts->AddFontFromFileTTF("engine/resources/fonts/Noto_Sans/NotoSans-Regular.ttf", 30.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFontConfig fontConfig;
    float globalScaleFactor = 5.0f;

    fontConfig.SizePixels = 36 * globalScaleFactor;
    io.Fonts->AddFontDefault(&fontConfig)->FontSize = globalScaleFactor;

    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowBorderSize = 0;
	    style.WindowTitleAlign = ImVec2(0.5, 0.5);
        style.FramePadding = ImVec2(8, 4);

        style.Colors[ImGuiCol_TitleBg] = ImColor(55, 159 ,239, 255);
	    style.Colors[ImGuiCol_TitleBgActive] = ImColor(55, 159, 239, 255);
	    style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

	    style.Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
	    style.Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
	    style.Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

	    style.Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
	    style.Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
	    style.Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

        style.Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
	    style.Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
	    style.Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

	    style.Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
	    style.Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
	    style.Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);
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

        ImGui::Separator();
        ImGui::Text("Text Options");
        // ImGui::SliderFloat("UI Scale", &globalScaleFactor, 0.1f, 2.0f, "%.1f");

        // ImGuiIO io = ImGui::GetIO();
        // fontConfig.SizePixels = 12 * globalScaleFactor;
        // io.Fonts->AddFontDefault(&fontConfig)->FontSize = globalScaleFactor;
    ImGui::End();
}

void UI::TransformComponentWindow() 
{
    ImGui::Begin("Portal Gun Transform");
        ImGui::DragFloat3(labelPrefix("Translation").c_str(), (float *)&translateOffset, 0.01f);
        ImGui::DragFloat3(labelPrefix("Rotation").c_str(), (float *)&rotateOffset, 0.03f);
        ImGui::DragFloat3(labelPrefix("Scale").c_str(), (float *)&scaleOffset, 0.01f);

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
    ImGui::End();

    ImGui::Begin("Companion Cube Transform");
        ImGui::DragFloat3(labelPrefix("Translation").c_str(), (float *)&cubePositionOffset, 0.01f);
        ImGui::DragFloat3(labelPrefix("Rotation").c_str(), (float *)&cubeRotationOffset, 0.03f);
        ImGui::DragFloat3(labelPrefix("Scale").c_str(), (float *)&cubeScaleOffset, 0.01f);
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

ImVec4 UI::GetCubePositionOffset() { return cubePositionOffset; }
ImVec4 UI::GetCubeRotationOffset() { return cubeRotationOffset; }
ImVec4 UI::GetCubeScaleOffset() { return cubeScaleOffset; }

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

// SETTERS
void UI::SetDiffusePreviewTexture(unsigned int texture) { diffusePreviewTexture = (ImTextureID)(intptr_t)texture; }
void UI::SetSpecularPreviewTexture(unsigned int texture) { specularPreviewTexture = (ImTextureID)(intptr_t)texture; }

// PRIVATE METHODS
std::string UI::labelPrefix(const char* const label) 
{
    float width = ImGui::CalcItemWidth();

	float x = ImGui::GetCursorPosX();
	ImGui::Text(label); 
	ImGui::SameLine(); 
	ImGui::SetCursorPosX(x + width * 0.5f + ImGui::GetStyle().ItemInnerSpacing.x);
	ImGui::SetNextItemWidth(-1);

	std::string labelID = "##";
	labelID += label;

	return labelID;
}

void UI::Shutdown() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}