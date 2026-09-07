#include "BasicScene.h"

BasicScene::BasicScene(Application* app) : Scene(app), 
	shader("assets/Shaders/default.vert", "assets/Shaders/default.frag"),
	camera(glm::vec3(0.0f, 0.0f, 2.0f)) { }

void BasicScene::Start()
{
	glEnable(GL_DEPTH_TEST);
}

void BasicScene::Update(float deltaTime)
{
	GLFWwindow* win = app->GetGLFWWindow();
	WindowData& data = app->GetWindowData();

	camera.Inputs(win, deltaTime, data.width, data.height);
}

void BasicScene::Render()
{
	GLCall(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	glm::mat4 model = glm::mat4(1.0f);
	shader.Activate();
	shader.setMatrix("model", model);

	WindowData& data = app->GetWindowData();
	camera.Matrix(fov, 0.1f, 100.0f, shader, "camMat", data.width, data.height);
}

void BasicScene::OnScroll(double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}