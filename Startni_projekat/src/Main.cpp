#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Texture.h"
#include "Camera/Camera.h"
#include "Buffers/VBO.h"
#include "Buffers/VAO.h"
#include "Buffers/EBO.h"
#include "ErrorHandler.h"

void local_terminate(int exitNumber, const char* message);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float fov = 45.0f;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangel", NULL, NULL);
	if (window == NULL)
		local_terminate(-1, "Prozor nije kreiran.");

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);

	gladLoadGL();

	Shader shaderProgram("assets/Shaders/default.vert", "assets/Shaders/default.frag");

	glEnable(GL_DEPTH_TEST);

	Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		process_input(window);
		camera.Inputs(window, deltaTime, SCR_WIDTH, SCR_HEIGHT);

		GLCall(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 model = glm::mat4(1.0f);

		shaderProgram.Activate();
		shaderProgram.setMatrix("model", model);
		camera.Matrix(fov, 0.1f, 100.0f, shaderProgram, "camMat", SCR_WIDTH, SCR_HEIGHT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void local_terminate(int exitNumber, const char* message) {
	std::cout << message << std::endl;
	glfwTerminate();
	exit(exitNumber);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
