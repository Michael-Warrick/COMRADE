#include "ui.hpp"

UI::UI(GLFWwindow *window, const char *glVersion)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    ImFont *mainfont = io.Fonts->AddFontFromFileTTF("engine/resources/fonts/Noto_Sans/NotoSans-Regular.ttf", 64.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImGui::GetIO().FontGlobalScale = globalFontSize * globalFontNormalizerConstant;

    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowBorderSize = 0;
        style.WindowTitleAlign = ImVec2(0.5, 0.5);
        style.FramePadding = ImVec2(8, 4);

        style.WindowMenuButtonPosition = ImGuiDir_None;

        // Current Config
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.14f, 0.17f, 1.00f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.12f, 0.15f, 0.18f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.12f, 0.15f, 0.18f, 1.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 1.00f, 0.90f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 1.00f, 0.30f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.80f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.12f, 0.15f, 0.18f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.12f, 0.15f, 0.18f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.80f, 0.80f, 1.00f, 0.30f);
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glVersion);

    // Load icons
    pauseButtonIconID = (ImTextureID)(intptr_t)pauseButtonIcon.Load("engine/resources/icons/pause_icon.png");
    playButtonIconID = (ImTextureID)(intptr_t)playButtonIcon.Load("engine/resources/icons/play_icon.png");
    removeButtonIconID = (ImTextureID)(intptr_t)removeButtonIcon.Load("engine/resources/icons/trash_icon.png");
}

void UI::SetSceneInfo(Scene scn)
{
    this->scene = scn;
}

void UI::Update()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::GetIO().FontGlobalScale = globalFontSize * globalFontNormalizerConstant;

    MenuBar();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    InteractionsBar();
    Inspector();
    RenderOptionsOverlay();
    Viewport();
    SceneHierarchy();
    ProjectFolder();
    Console();

    // ImGui::ShowDemoWindow();
}

void UI::MenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "CTRL+O"))
            {
                // Setup Native File Dialog
                NFD_Init();

                nfdchar_t *outPath;
                nfdfilteritem_t filterItem[2] = {{"Source code", "c,cpp,cc"}, {"Headers", "h,hpp"}};
                nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 2, NULL);
                if (result == NFD_OKAY)
                {
                    puts("Success!");
                    puts(outPath);
                    NFD_FreePath(outPath);
                }
                else if (result == NFD_CANCEL)
                {
                    puts("User pressed cancel.");
                }
                else
                {
                    printf("Error: %s\n", NFD_GetError());
                }

                NFD_Quit();
            }
            if (ImGui::MenuItem("Open Recent"))
            {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save", "CTRL+S"))
            {
            }
            if (ImGui::MenuItem("Save As", "CTRL+Shift+S"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z"))
            {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
            {
            } // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X"))
            {
            }
            if (ImGui::MenuItem("Copy", "CTRL+C"))
            {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V"))
            {
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Preferences"))
            {
                if (ImGui::MenuItem("Renderering"))
                {
                    showRenderOptionsOverlay = true;
                }

                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();
}

void UI::InteractionsBar()
{
    ImGui::Begin("Interactions Bar");

    ImVec2 windowSize = ImGui::GetWindowSize();

    // Calculate the X position to center the buttons
    ImVec2 buttonSize(20, 20);
    float buttonSpacing = 10.0f;
    float totalButtonWidth = (buttonSize.x + buttonSpacing) * 2.0f - buttonSpacing;
    float centerPosX = (windowSize.x - totalButtonWidth) / 2.0f;

    ImGui::SetCursorPosX(centerPosX);

    if (ImGui::ImageButton("Play", playButtonIconID, buttonSize, ImVec2(0, 1), ImVec2(1, 0), ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1)))
    {
        gameIsRunning = true;
    }

    ImGui::SameLine();

    if (ImGui::ImageButton("Pause", pauseButtonIconID, buttonSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1)))
    {
        gameIsRunning = false;
    }

    // End the ImGui window
    ImGui::End();
}

void UI::RenderOptionsOverlay()
{
    if (showRenderOptionsOverlay)
    {
        ImGui::SetNextWindowBgAlpha(0.85f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoResize;

        ImGui::Begin("Rendering Options", &showRenderOptionsOverlay, window_flags);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

        ImVec2 closeButtonSize(20, 20);

        ImGui::PopStyleVar(2);

        if (ImGui::Button("X", closeButtonSize))
        {
            showRenderOptionsOverlay = false;
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Checkbox("Vertical Synchronisation", &vSyncEnabled);
        ImGui::TextWrapped("WARNING: Disabling Vertical Synchronisation may cause screen-tearing!");

        if (vSyncEnabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        ImGui::Separator();

        ImGui::ColorEdit3("Clear Color", (float *)&clearColor);
        ImGui::Checkbox("Wireframe", &renderWireframe);
        ImGui::SameLine();
        ImGui::Checkbox("Points", &renderPoints);
        ImGui::SameLine();
        ImGui::Checkbox("Depth", &renderDepthBuffer);
        scene.SetDepthBuffer(renderDepthBuffer);

        if (renderWireframe)
        {
            glLineWidth(3.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else if (renderPoints)
        {
            glPointSize(5.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        ImGui::Separator();

        ImVec2 buttonSize(40, 40);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 25.0f);

        ImGui::Text("Text Options");

        if (ImGui::Button("+", buttonSize))
        {
            globalFontSize += 0.5f;
        }

        ImGui::SameLine();

        ImGui::Text("Font Size: %.1f", globalFontSize);

        ImGui::SameLine();

        if (ImGui::Button("-", buttonSize))
        {
            globalFontSize -= 0.5f;
        }

        ImGui::PopStyleVar(2);

        ImGui::End();
        ImGui::PopStyleVar();
    }
}

void UI::Inspector()
{
    ImGui::Begin("Inspector");

    std::shared_ptr<GameObject> currentGameObject;

    for (int i = 0; i < scene.GetGameObjects().size(); i++)
    {
        std::shared_ptr<GameObject> gameObject = scene.GetGameObjects()[i];
        std::vector<std::shared_ptr<Component>> components = gameObject->GetComponents();

        if (gameObject->IsSelected())
        {
            currentGameObject = gameObject;

            bool isActive = gameObject->IsActive();
            ImGui::Checkbox("Active", &isActive);
            gameObject->SetActive(isActive);

            ImGui::SameLine();
            // Editable name of the game object
            char name[64];
            strcpy(name, gameObject->GetName().c_str());
            ImGui::InputText("##", name, 64);
            gameObject->SetName(name);

            ImGui::Separator();

            std::vector<int> componentsToDelete;
            for (int k = 0; k < components.size(); ++k)
            {
                if (components[k]->GetType() == ComponentType::Transform)
                {
                    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        ImGui::Indent();
                        UI::TransformComponentWindow(*gameObject);
                        ImGui::Unindent();

                        ImGui::Separator();
                    }

                    ImGui::Spacing();
                }

                if (components[k]->GetType() == ComponentType::DirectionalLight)
                {
                    if (ImGui::CollapsingHeader("Directional Light", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        ImGui::Indent();
                        UI::DirectionalLightComponentWindow(*gameObject);
                        ImGui::Unindent();

                        ImGui::Separator();
                    }

                    ImGui::Spacing();
                }

                if (components[k]->GetType() == ComponentType::MeshRenderer)
                {
                    if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        ImGui::Indent();
                        ImVec2 buttonSize(20, 20);
                        if (ImGui::ImageButton("Remove", removeButtonIconID, buttonSize, ImVec2(0, 1), ImVec2(1, 0), ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1)))
                        {
                            componentsToDelete.push_back(k);

                            std::cout << componentsToDelete.size() << std::endl;
                        }
                        UI::MeshRendererComponentWindow(*gameObject);
                        ImGui::Unindent();

                        ImGui::Separator();
                    }
                }

                if (components[k]->GetType() == ComponentType::Script)
                {
                    if (ImGui::CollapsingHeader("Script", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        ImGui::Indent();
                        UI::ScriptComponentWindow(*gameObject);
                        ImGui::Unindent();

                        ImGui::Separator();
                    }
                }
            }

            for (int k = componentsToDelete.size() - 1; k >= 0; k--)
            {
                components.erase(components.begin() + componentsToDelete[k]);
            }

            gameObject->SetComponents(components);

            ImGui::Dummy(ImVec2(0, 10));

            // Center the button and add a border to it and make it rounded
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 25.0f);

            addComponentButtonPos = ImGui::GetCursorScreenPos(); // adjust as necessary
            addComponentButtonSize = ImVec2(256, 40);            // adjust as necessary
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - addComponentButtonSize.x) / 2.0f);

            if (ImGui::Button("Add Component", addComponentButtonSize))
            {
                showAvailableComponentsWindow = true;
            }

            ImGui::PopStyleVar(2);

            if (showAvailableComponentsWindow)
            {
                componentSelectionWindowSize = ImVec2(256, 320);
                componentSelectionWindowPos = addComponentButtonPos + ImVec2((ImGui::GetWindowSize().x - addComponentButtonSize.x) / 2.0f, 0 + addComponentButtonSize.y);

                ImGui::SetNextWindowPos(componentSelectionWindowPos);
                ImGui::SetNextWindowSize(componentSelectionWindowSize);

                ImGui::SetCursorPosX((ImGui::GetWindowSize().x - addComponentButtonSize.x) / 2.0f);

                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);

                ImGui::Begin("Component", &showAvailableComponentsWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);

                if (ImGui::MenuItem("Mesh Renderer"))
                {
                    gameObject->AddComponent(std::make_shared<MeshRenderer>(std::make_shared<Model>("engine/resources/models/primatives/Cube.obj"), std::make_shared<Shader>(shaders.at("default"))));
                }
                ImGui::Separator();
                if (ImGui::BeginMenu("New Script"))
                {
                    if (ImGui::MenuItem("Native (C++)"))
                    {
                        showCppScriptCreateModal = true;
                    }

                    if (ImGui::MenuItem("C#"))
                    {
                        // gameObject->AddComponent(std::make_shared<Script>());
                    }
                    if (ImGui::MenuItem("Python"))
                    {
                        // gameObject->AddComponent(std::make_shared<Script>());
                    }

                    ImGui::EndMenu();
                }

                ImGui::End();

                ImGui::PopStyleVar();
            }

            ImGui::PopStyleVar(2);
        }
    }

    // Always center this window when appearing
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (showCppScriptCreateModal)
    {
        ImGui::OpenPopup("Create Native (C++) Script");
    }

    if (ImGui::BeginPopupModal("Create Native (C++) Script", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Native (C++) scripts are compiled and run at runtime.\nThis allows for the fastest possible performance.\n\n");
        ImGui::Separator();

        ImGui::Dummy(ImVec2(0, 10));

        static char scriptName[128] = "NewScript";
        ImGui::InputText(labelPrefix("Name:").c_str(), scriptName, IM_ARRAYSIZE(scriptName));

        ImGui::Dummy(ImVec2(0, 10));

        ImGui::Separator();

        if (UI::ButtonCenteredOnLine("OK", ImVec2(100, 40), 0.25f))
        {
            std::regex pattern("^[a-zA-Z0-9]+$");

            if (std::regex_match(scriptName, pattern))
            {
                ImGui::CloseCurrentPopup();
                showCppScriptCreateModal = false;

                if (currentGameObject)
                {
                    currentGameObject->AddComponent(std::make_shared<Script>(scriptName));
                    currentGameObject->GetComponent<Script>()->SetLanguage(Script::Language::Native);
                    currentGameObject->GetComponent<Script>()->SetPath("path/to/script");
                }
            }

            else
            {
                ImGui::OpenPopup("Error###InvalidScriptName");
            }
        }

        if (ImGui::BeginPopupModal("Error###InvalidScriptName", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Invalid script name.\nScript name must only contain alphanumeric characters and no spaces.\n\nExample: \"MyScript\"");
            ImGui::Separator();
            if (ButtonCenteredOnLine("OK", ImVec2(100, 40), 0.5f))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::SetItemDefaultFocus();

        ImGui::SameLine();
        if (ButtonCenteredOnLine("Cancel", ImVec2(100, 40), 1.0f))
        {
            ImGui::CloseCurrentPopup();
            showCppScriptCreateModal = false;
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}

void UI::TransformComponentWindow(GameObject gameObject)
{
    // Position
    float position[3] = {
        gameObject.GetComponent<Transform>()->GetPosition().x(),
        gameObject.GetComponent<Transform>()->GetPosition().y(),
        gameObject.GetComponent<Transform>()->GetPosition().z()};
    UI::DragFloatN_Colored("Position        ", position, 3, 0.01f, -FLT_MAX, FLT_MAX, "%.2f", 1.0f);
    gameObject.GetComponent<Transform>()->SetPosition(position[0], position[1], position[2]);

    // Rotation
    float rotation[3] = {
        gameObject.GetComponent<Transform>()->GetRotation().x(),
        gameObject.GetComponent<Transform>()->GetRotation().y(),
        gameObject.GetComponent<Transform>()->GetRotation().z()};
    UI::DragFloatN_Colored("Rotation       ", rotation, 3, 0.01f, -FLT_MAX, FLT_MAX, "%.2f", 1.0f);
    gameObject.GetComponent<Transform>()->SetRotation(rotation[0], rotation[1], rotation[2]);

    // Scale
    float scale[3] = {
        gameObject.GetComponent<Transform>()->GetScale().x(),
        gameObject.GetComponent<Transform>()->GetScale().y(),
        gameObject.GetComponent<Transform>()->GetScale().z()};
    UI::DragFloatN_Colored("Scale             ", scale, 3, 0.01f, -FLT_MAX, FLT_MAX, "%.2f", 1.0f);
    gameObject.GetComponent<Transform>()->SetScale(scale[0], scale[1], scale[2]);
}

void UI::MeshRendererComponentWindow(GameObject gameObject)
{
    std::string currentModelName = gameObject.GetComponent<MeshRenderer>()->GetModel()->GetName();

    if (ImGui::BeginCombo(labelPrefix("Mesh: ").c_str(), currentModelName.c_str()))
    {
        std::vector<std::string> modelNames = scene.GetModelNames();
        for (int i = 0; i < modelNames.size(); i++)
        {
            std::string modelName = modelNames[i];
            bool isSelected = (currentModelName == modelName);
            if (ImGui::Selectable(modelName.c_str(), isSelected))
            {
                gameObject.GetComponent<MeshRenderer>()->SetModel(std::make_shared<Model>(modelName.c_str()));
            }
            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::Separator();

        if (ImGui::Selectable("Add New Mesh..."))
        {
            NFD_Init();

            nfdchar_t *outPath;
            nfdfilteritem_t filterItem[1] = {{"OBJ files", "obj"}};
            nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);
            if (result == NFD_OKAY)
            {
                puts("Success!");
                puts(outPath);

                gameObject.GetComponent<MeshRenderer>()->SetModel(std::make_shared<Model>(outPath));

                // if not already in the list of model names, add it
                if (std::find(modelNames.begin(), modelNames.end(), outPath) == modelNames.end())
                {
                    modelNames.push_back(outPath);
                }

                NFD_FreePath(outPath);
            }
            else if (result == NFD_CANCEL)
            {
                puts("User pressed cancel.");
            }
            else
            {
                printf("Error: %s\n", NFD_GetError());
            }

            NFD_Quit();
        }

        ImGui::EndCombo();
    }

    if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick))
    {
        ImGui::Text("Diffuse:");
        ImGui::Indent(50.0f);
        for (int i = 0; i < gameObject.GetComponent<MeshRenderer>()->GetModel()->GetTextures().size(); i++)
        {
            std::shared_ptr<Texture> texture = std::make_shared<Texture>(gameObject.GetComponent<MeshRenderer>()->GetModel()->GetTextures()[i]);
            if (texture->Type == "texture_diffuse")
            {
                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImVec2 uvMin = ImVec2(0.0f, 0.0f);
                ImVec2 uvMax = ImVec2(1.0f, 1.0f);
                ImVec4 tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                ImVec4 borderColor = ImVec4(hexToImVec4("#eeeeee"));
                ImVec2 imageSize = ImVec2(50, 50);

                ImGui::Image((void *)(intptr_t)texture->ID, imageSize, uvMin, uvMax, tintColor, borderColor);
            }
        }
        ImGui::Unindent(50.0f);

        ImGui::Text("Normal:");
        ImGui::Indent(50.0f);
        for (int i = 0; i < gameObject.GetComponent<MeshRenderer>()->GetModel()->GetTextures().size(); i++)
        {
            std::shared_ptr<Texture> texture = std::make_shared<Texture>(gameObject.GetComponent<MeshRenderer>()->GetModel()->GetTextures()[i]);
            if (texture->Type == "texture_normal")
            {
                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImVec2 uvMin = ImVec2(0.0f, 0.0f);
                ImVec2 uvMax = ImVec2(1.0f, 1.0f);
                ImVec4 tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                ImVec4 borderColor = ImVec4(hexToImVec4("#eeeeee"));
                ImVec2 imageSize = ImVec2(50, 50);

                ImGui::Image((void *)(intptr_t)texture->ID, imageSize, uvMin, uvMax, tintColor, borderColor);
            }
        }
        ImGui::Unindent(50.0f);

        ImGui::Text("Roughness:");
        ImGui::Indent(50.0f);
        for (int i = 0; i < gameObject.GetComponent<MeshRenderer>()->GetModel()->GetTextures().size(); i++)
        {
            std::shared_ptr<Texture> texture = std::make_shared<Texture>(gameObject.GetComponent<MeshRenderer>()->GetModel()->GetTextures()[i]);
            if (texture->Type == "texture_roughness")
            {
                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImVec2 uvMin = ImVec2(0.0f, 0.0f);
                ImVec2 uvMax = ImVec2(1.0f, 1.0f);
                ImVec4 tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                ImVec4 borderColor = ImVec4(hexToImVec4("#eeeeee"));
                ImVec2 imageSize = ImVec2(50, 50);

                ImGui::Image((void *)(intptr_t)texture->ID, imageSize, uvMin, uvMax, tintColor, borderColor);
            }
        }
        ImGui::Unindent(50.0f);
    }
}

void UI::DirectionalLightComponentWindow(GameObject gameObject)
{
    float directionalLightRotation[3] = {
        gameObject.GetComponent<DirectionalLight>()->GetDirection().x,
        gameObject.GetComponent<DirectionalLight>()->GetDirection().y,
        gameObject.GetComponent<DirectionalLight>()->GetDirection().z};
    DragFloatN_Colored("Direction", directionalLightRotation, 3, 0.01f, -1.0f, 1.0f, "%.2f", 1.0f);
    gameObject.GetComponent<DirectionalLight>()->SetDirection(glm::vec3(directionalLightRotation[0], directionalLightRotation[1], directionalLightRotation[2]));

    float directionalLightAmbient[3] = {
        gameObject.GetComponent<DirectionalLight>()->GetAmbient().x,
        gameObject.GetComponent<DirectionalLight>()->GetAmbient().y,
        gameObject.GetComponent<DirectionalLight>()->GetAmbient().z};
    DragFloatN_Colored("Ambient Intensity", directionalLightAmbient, 3, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    gameObject.GetComponent<DirectionalLight>()->SetAmbient(glm::vec3(directionalLightAmbient[0], directionalLightAmbient[1], directionalLightAmbient[2]));

    float directionalLightDiffuse[3] = {
        gameObject.GetComponent<DirectionalLight>()->GetDiffuse().x,
        gameObject.GetComponent<DirectionalLight>()->GetDiffuse().y,
        gameObject.GetComponent<DirectionalLight>()->GetDiffuse().z};
    DragFloatN_Colored("Diffuse Intensity", directionalLightDiffuse, 3, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    gameObject.GetComponent<DirectionalLight>()->SetDiffuse(glm::vec3(directionalLightDiffuse[0], directionalLightDiffuse[1], directionalLightDiffuse[2]));

    float directionalLightSpecular[3] = {
        gameObject.GetComponent<DirectionalLight>()->GetSpecular().x,
        gameObject.GetComponent<DirectionalLight>()->GetSpecular().y,
        gameObject.GetComponent<DirectionalLight>()->GetSpecular().z};
    DragFloatN_Colored("Specular Intensity", directionalLightSpecular, 3, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    gameObject.GetComponent<DirectionalLight>()->SetSpecular(glm::vec3(directionalLightSpecular[0], directionalLightSpecular[1], directionalLightSpecular[2]));
}

void UI::ScriptComponentWindow(GameObject gameObject)
{
    ImGui::Text("Name: %s", gameObject.GetComponent<Script>()->GetScriptName().c_str());
    ImGui::Text("Path: %s", gameObject.GetComponent<Script>()->GetPath().c_str());
}

void UI::Viewport()
{
    ImGui::Begin("Scene");
    viewportSize = ImGui::GetContentRegionAvail();

    // Calculate the aspect ratio of the image and the content region
    float imageAspectRatio = (float)1920 / (float)1080;
    float contentRegionAspectRatio = viewportSize.x / viewportSize.y;

    glViewport(0, 0, 1920, 1080);

    // Scale the image horizontally if the content region is wider than the image
    if (contentRegionAspectRatio > imageAspectRatio)
    {
        float imageWidth = viewportSize.y * imageAspectRatio;
        float xPadding = (viewportSize.x - imageWidth) / 2;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xPadding);
        ImGui::Image((ImTextureID)(intptr_t)viewportTexture, ImVec2(imageWidth, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
    }
    // Scale the image vertically if the content region is taller than the image
    else
    {
        float imageHeight = viewportSize.x / imageAspectRatio;
        float yPadding = (viewportSize.y - imageHeight) / 2;
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + yPadding);
        ImGui::Image((ImTextureID)(intptr_t)viewportTexture, ImVec2(viewportSize.x, imageHeight), ImVec2(0, 1), ImVec2(1, 0));
    }

    ImGui::End();
}

void UI::SceneHierarchy()
{
    ImGui::Begin("Hierarchy");

    const char *gameObjectNames[] = {"Empty", "Cube", "Sphere", "Plane", "Cylinder", "Cone"};

    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

    if (ImGui::Button("Create [+]"))
    {
        ImGui::OpenPopup("create_game_object_popup");
    }

    ImGui::PopStyleVar(2);

    if (ImGui::BeginPopup("create_game_object_popup"))
    {
        ImGui::Text("Game Objects");
        ImGui::Separator();
        for (int i = 0; i < IM_ARRAYSIZE(gameObjectNames); i++)
        {
            if (ImGui::Selectable(gameObjectNames[i]))
            {
                if (strcmp(gameObjectNames[i], "Empty") == 0)
                {
                    // When creating a new game object, we need to give it a unique name
                    // We can do this by appending the number of game objects in the scene to the name
                    std::string gameObjectName = "Empty";

                    // Calculate the number of game objects in the scene with the name Empty
                    int numberOfEmptyGameObjects = 0;
                    std::regex pattern("Empty( \\(\\d+\\))?"); // regular expression to match "Empty" or "Empty (number)"

                    for (const auto &gameObject : scene.GetGameObjects())
                    {
                        std::string name = gameObject->GetName();
                        if (std::regex_match(name, pattern))
                        {
                            numberOfEmptyGameObjects++;
                        }
                    }

                    if (numberOfEmptyGameObjects > 0)
                    {
                        gameObjectName += " (" + std::to_string(numberOfEmptyGameObjects) + ")";
                    }

                    scene.AddGameObject(std::make_shared<GameObject>(gameObjectName.c_str()));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
                }

                else if (strcmp(gameObjectNames[i], "Cube") == 0)
                {
                    std::string gameObjectName = "Cube";

                    int numberOfCubeGameObjects = 0;
                    std::regex pattern("Cube( \\(\\d+\\))?");

                    for (const auto &gameObject : scene.GetGameObjects())
                    {
                        std::string name = gameObject->GetName();
                        if (std::regex_match(name, pattern))
                        {
                            numberOfCubeGameObjects++;
                        }
                    }

                    if (numberOfCubeGameObjects > 0)
                    {
                        gameObjectName += " (" + std::to_string(numberOfCubeGameObjects) + ")";
                    }

                    scene.AddGameObject(std::make_shared<GameObject>(gameObjectName.c_str()));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<MeshRenderer>(std::make_shared<Model>("engine/resources/models/primatives/Cube.obj"), std::make_shared<Shader>(shaders.at("default"))));
                }

                else if (strcmp(gameObjectNames[i], "Sphere") == 0)
                {
                    std::string gameObjectName = "Sphere";

                    int numberOfSphereGameObjects = 0;
                    std::regex pattern("Sphere( \\(\\d+\\))?");

                    for (const auto &gameObject : scene.GetGameObjects())
                    {
                        std::string name = gameObject->GetName();
                        if (std::regex_match(name, pattern))
                        {
                            numberOfSphereGameObjects++;
                        }
                    }

                    if (numberOfSphereGameObjects > 0)
                    {
                        gameObjectName += " (" + std::to_string(numberOfSphereGameObjects) + ")";
                    }

                    scene.AddGameObject(std::make_shared<GameObject>(gameObjectName.c_str()));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<MeshRenderer>(std::make_shared<Model>("engine/resources/models/primatives/Sphere.obj"), std::make_shared<Shader>(shaders.at("default"))));
                }

                else if (strcmp(gameObjectNames[i], "Plane") == 0)
                {
                    std::string gameObjectName = "Plane";

                    int numberOfPlaneGameObjects = 0;
                    std::regex pattern("Plane( \\(\\d+\\))?");

                    for (const auto &gameObject : scene.GetGameObjects())
                    {
                        std::string name = gameObject->GetName();
                        if (std::regex_match(name, pattern))
                        {
                            numberOfPlaneGameObjects++;
                        }
                    }

                    if (numberOfPlaneGameObjects > 0)
                    {
                        gameObjectName += " (" + std::to_string(numberOfPlaneGameObjects) + ")";
                    }

                    scene.AddGameObject(std::make_shared<GameObject>(gameObjectName.c_str()));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<MeshRenderer>(std::make_shared<Model>("engine/resources/models/primatives/Plane.obj"), std::make_shared<Shader>(shaders.at("default"))));
                }

                else if (strcmp(gameObjectNames[i], "Cylinder") == 0)
                {
                    std::string gameObjectName = "Cylinder";

                    int numberOfCylinderGameObjects = 0;
                    std::regex pattern("Cylinder( \\(\\d+\\))?");

                    for (const auto &gameObject : scene.GetGameObjects())
                    {
                        std::string name = gameObject->GetName();
                        if (std::regex_match(name, pattern))
                        {
                            numberOfCylinderGameObjects++;
                        }
                    }

                    if (numberOfCylinderGameObjects > 0)
                    {
                        gameObjectName += " (" + std::to_string(numberOfCylinderGameObjects) + ")";
                    }

                    scene.AddGameObject(std::make_shared<GameObject>(gameObjectName.c_str()));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<MeshRenderer>(std::make_shared<Model>("engine/resources/models/primatives/Cylinder.obj"), std::make_shared<Shader>(shaders.at("default"))));
                }

                else if (strcmp(gameObjectNames[i], "Cone") == 0)
                {
                    std::string gameObjectName = "Cone";

                    int numberOfConeGameObjects = 0;
                    std::regex pattern("Cone( \\(\\d+\\))?");

                    for (const auto &gameObject : scene.GetGameObjects())
                    {
                        std::string name = gameObject->GetName();
                        if (std::regex_match(name, pattern))
                        {
                            numberOfConeGameObjects++;
                        }
                    }

                    if (numberOfConeGameObjects > 0)
                    {
                        gameObjectName += " (" + std::to_string(numberOfConeGameObjects) + ")";
                    }

                    scene.AddGameObject(std::make_shared<GameObject>(gameObjectName.c_str()));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
                    scene.GetGameObject(gameObjectName.c_str())->AddComponent(std::make_shared<MeshRenderer>(std::make_shared<Model>("engine/resources/models/primatives/Cone.obj"), std::make_shared<Shader>(shaders.at("default"))));
                }
            }
        }
        ImGui::EndPopup();
    }

    if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (int i = 0; i < scene.GetGameObjects().size(); i++)
        {
            std::shared_ptr<GameObject> gameObject = scene.GetGameObjects()[i];

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

            if (gameObject->GetChildren().size() == 0)
            {
                flags |= ImGuiTreeNodeFlags_Leaf;
            }

            if (gameObject->IsSelected())
            {
                flags |= ImGuiTreeNodeFlags_Selected;
            }

            bool nodeOpen = ImGui::TreeNodeEx(gameObject->GetName().c_str(), flags);

            if (ImGui::IsItemClicked())
            {
                // Unselect all GameObjects except the newly selected one
                for (int j = 0; j < scene.GetGameObjects().size(); j++)
                {
                    std::shared_ptr<GameObject> other = scene.GetGameObjects()[j];
                    if (gameObject != other)
                    {
                        other->SetSelected(false);
                    }
                }

                gameObject->SetSelected(true);
            }

            if (nodeOpen)
            {
                for (int j = 0; j < gameObject->GetChildren().size(); j++)
                {
                    std::shared_ptr<GameObject> child = gameObject->GetChildren()[j];

                    ImGuiTreeNodeFlags childFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

                    if (child->GetChildren().size() == 0)
                    {
                        childFlags |= ImGuiTreeNodeFlags_Leaf;
                    }

                    if (child->IsSelected())
                    {
                        childFlags |= ImGuiTreeNodeFlags_Selected;
                    }

                    bool childNodeOpen = ImGui::TreeNodeEx(child->GetName().c_str(), childFlags);

                    if (ImGui::IsItemClicked())
                    {
                        // Unselect all GameObjects except the newly selected one
                        for (int k = 0; k < scene.GetGameObjects().size(); k++)
                        {
                            std::shared_ptr<GameObject> other = scene.GetGameObjects()[k];
                            if (child != other)
                            {
                                other->SetSelected(false);
                            }
                        }

                        child->SetSelected(true);
                    }

                    if (childNodeOpen)
                    {
                        ImGui::TreePop();
                    }
                }

                ImGui::TreePop();
            }
        }
        ImGui::End();
    }
}

void UI::ProjectFolder()
{
    ImGui::Begin("Project");
    ImGui::End();
}

void UI::Console()
{
    ImGui::Begin("Console");
    ImGui::BeginChild("Console Buttons");
    ImGui::Button("Clear");
    ImGui::SameLine();

    ImGui::Button("Errors");
    ImGui::SameLine();
    ImGui::Button("Warnings");
    ImGui::SameLine();
    ImGui::Button("Messages");
    ImGui::Separator();
    ImGui::EndChild();

    ImGui::BeginChild("Terminal Container");
    ImGui::Text(">_");
    ImGui::Button("PRESS ME");
    ImGui::EndChild();
    ImGui::End();
}

void UI::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();
    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

// GETTERS
bool UI::GetDepthBufferBool() { return renderDepthBuffer; }
float UI::GetViewportWidth() { return viewportSize.x; }
float UI::GetViewportHeight() { return viewportSize.y; }

bool UI::GetGameState() { return gameIsRunning; }

// SETTERS
void UI::SetViewportTexture(unsigned int colorBufferTexture) { viewportTexture = colorBufferTexture; }
void UI::SetShaderInfo(std::unordered_map<std::string, Shader> shaders) { this->shaders = shaders; }

// PRIVATE METHODS
std::string UI::labelPrefix(const char *const label)
{
    float width = ImGui::CalcItemWidth();

    float x = ImGui::GetCursorPosX();
    ImGui::Text("%s", label);
    ImGui::SameLine();
    ImGui::SetCursorPosX(x + width * 0.5f + ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::SetNextItemWidth(-1);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);

    std::string labelID = "##";
    labelID += label;

    return labelID;
}

bool UI::DragFloatN_Colored(const char *label, float *v, int components, float v_speed, float v_min, float v_max, const char *display_format, float power)
{
    ImGuiWindow *window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext &g = *GImGui;
    bool value_changed = false;
    ImGui::BeginGroup();
    ImGui::PushID(label);
    ImGui::TextUnformatted(label, ImGui::FindRenderedTextEnd(label));
    ImGui::SameLine();
    ImGui::PushMultiItemsWidths(components, ImGui::CalcItemWidth());
    for (int i = 0; i < components; i++)
    {
        static const ImU32 colors[] = {
            0xBB0000FF, // red
            0xBB00FF00, // green
            0xBBFF0000, // blue
            0xBBFFFFFF, // white for alpha?
        };

        ImGui::PushID(i);
        value_changed |= ImGui::DragFloat("##v", &v[i], v_speed, v_min, v_max, display_format, power);

        const ImVec2 min = ImGui::GetItemRectMin();
        const ImVec2 max = ImGui::GetItemRectMax();
        const float spacing = g.Style.FrameRounding;
        const float halfSpacing = spacing / 2;

        // This is the main change
        window->DrawList->AddLine({min.x + spacing, max.y - halfSpacing}, {max.x - spacing, max.y - halfSpacing}, colors[i], 4);

        ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);
        ImGui::PopID();
        ImGui::PopItemWidth();
    }
    ImGui::PopID();
    ImGui::EndGroup();

    return value_changed;
}

ImVec4 UI::hexToImVec4(std::string hex)
{
    std::string colorString = hex.substr(1);

    int r, g, b;

    r = std::stoi(colorString.substr(0, 2), 0, 16);
    g = std::stoi(colorString.substr(2, 2), 0, 16);
    b = std::stoi(colorString.substr(4, 2), 0, 16);

    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

bool UI::ButtonCenteredOnLine(const char *label, ImVec2 buttonSize, float alignment)
{
    ImGuiStyle &style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(label).x + buttonSize.x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * alignment;
    if (off > 0.0f)
    {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    }

    return ImGui::Button(label, buttonSize);
}

void UI::Shutdown()
{
    // free the textures
    pauseButtonIcon.Free();
    playButtonIcon.Free();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

UI::~UI()
{
    Shutdown();
}