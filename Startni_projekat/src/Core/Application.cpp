#include "Application.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void process_input(GLFWwindow* window);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Application::Application()
{
	lastFrameTime = 0.0f;

	window = Window::Create();

	windowData.title = "Application";
	windowData.width = 800;
	windowData.height = 600;
	windowData.VSync = true;

}

Application::~Application() {}

void Application::Run()
{
	Initialize();
	Loop();
}

void Application::Initialize()
{
	window->SetWindowSizeCallback(framebuffer_size_callback);
	window->SetScrollCallback(scroll_callback);
}

float Application::CalculateDeltaTime()
{
	const float curTime = static_cast<float>(glfwGetTime());
	const Timestep dt(curTime - lastFrameTime);
	lastFrameTime = curTime;
	return dt;
}

void Application::ChangeScene(std::unique_ptr<Scene> newScene)
{
	nextScene = std::move(newScene);
}

void Application::OnEventScroll(double xoffset, double yoffset)
{
	if (activeScene) {
		activeScene->OnScroll (xoffset, yoffset);
	}
}

void Application::Loop()
{
	while (window->IsOpen()) {
		float dt = CalculateDeltaTime();
		GLFWwindow* rawWindow = window->GetGLFWWindow();
		process_input(rawWindow);

		if (nextScene) {
			activeScene = std::move(nextScene);
			activeScene->Start();
		}

		if (activeScene) {
			activeScene->Update(dt);
			activeScene->Render();
		}

		window->Display();
		window->PollEvents();
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
	if (data) {
		data->width = width;
		data->height = height;
	}
}

static void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
	if (data && data->app) {
		data->app->OnEventScroll(xoffset, yoffset);
	}
}