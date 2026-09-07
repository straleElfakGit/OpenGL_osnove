#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Scene.h"
#include "Timestep.h"
#include "Window/Window.h"

class Application
{
private:
	float lastFrameTime;
	std::unique_ptr<Window> window;
    WindowData windowData;
    std::unique_ptr<Scene> activeScene;
    std::unique_ptr<Scene> nextScene;

    void Loop();
    void Initialize();

    float CalculateDeltaTime();

public:
    Application();
    ~Application();

    void Run();
    void ChangeScene(std::unique_ptr<Scene> newScene);

    void OnEventScroll(double xoffset, double yoffset);

    WindowData& GetWindowData() { return windowData; }
    GLFWwindow* GetGLFWWindow() { return window->GetGLFWWindow(); }
};

#endif // APPLICATION_H