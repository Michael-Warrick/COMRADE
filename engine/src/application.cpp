#include "application.hpp"

void Application::Run()
{
    UI ui(platformWindow.GetWindow(), "#version 410 core");
    ui.SetSceneInfo(renderer.GetScene());
    ui.SetShaderInfo(renderer.GetShaders());

    Framebuffer framebuffer(1920, 1080);

    while (platformWindow.IsOpen())
    {
        framebuffer.Bind();
        framebuffer.Clear();
        
        ui.Update();
        
        renderer.SetSceneInfo(ui.GetScene());
        // RENDER SCENE ...
        renderer.Render();
        
        framebuffer.BindColorTexture();
        
        ui.SetViewportTexture(framebuffer.GetColorTexture());
        
        framebuffer.UnbindColorTexture();
        framebuffer.Unbind();
        
        glClearColor(0.09f, 0.09f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        ui.Render();

        platformWindow.Update();
    }
}

Application::Application()
{
}

Application::~Application()
{
}