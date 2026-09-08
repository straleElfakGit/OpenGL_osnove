#ifndef APPLICATION_BASE_H
#define APPLICATION_BASE_H

#include "Scene.h"
#include "Timestep.h"
#include "Window/Window.h"

class ApplicationBase
{
protected:
    float lastFrameTime;
    std::unique_ptr<Window> window;
    WindowData windowData;
    std::unique_ptr<Scene> activeScene;
    std::unique_ptr<Scene> nextScene;

    virtual void Loop() = 0;
    virtual void Initialize() = 0;

    float CalculateDeltaTime();

public:
    ApplicationBase();
    virtual ~ApplicationBase();

    void Run();
    void ChangeScene(std::unique_ptr<Scene> newScene);

    void OnEventScroll(double xoffset, double yoffset);

    WindowData& GetWindowData() { return windowData; }
    GLFWwindow* GetGLFWWindow() { return window->GetGLFWWindow(); }
};

#endif // !APPLICATION_BASE_H
