#include "application.hpp"

void Application::Run()
{
    Framebuffer framebuffer(1920, 1080);
    
    UI ui(platformWindow.GetWindow(), "#version 410 core");
    Scene& scene = renderer.GetScene();

    ui.SetSceneInfo(scene);
    ui.SetShaderInfo(renderer.GetShaders());

    while (platformWindow.IsOpen())
    {
        framebuffer.Bind();
        framebuffer.Clear();
        
        ui.Update();
        
        renderer.SetSceneInfo(scene);
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