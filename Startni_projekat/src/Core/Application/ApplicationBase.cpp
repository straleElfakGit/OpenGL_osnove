#include "ApplicationBase.h"

ApplicationBase::ApplicationBase()
{
	lastFrameTime = 0.0f;

	window = Window::Create();

	windowData.title = "Application";
	windowData.width = 800;
	windowData.height = 600;
	windowData.VSync = true;
}

ApplicationBase::~ApplicationBase() { }

void ApplicationBase::Run()
{
	Initialize();
	Loop();
}

float ApplicationBase::CalculateDeltaTime()
{
	const float curTime = static_cast<float>(glfwGetTime());
	const Timestep dt(curTime - lastFrameTime);
	lastFrameTime = curTime;
	return dt;
}

void ApplicationBase::ChangeScene(std::unique_ptr<Scene> newScene)
{
	nextScene = std::move(newScene);
}

void ApplicationBase::OnEventScroll(double xoffset, double yoffset)
{
	if (activeScene) {
		activeScene->OnScroll(xoffset, yoffset);
	}
}