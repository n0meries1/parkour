#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

#include "renderer.h"
#include "camera.h"

//prototyping
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window, float deltatime);
void ProcessMouseInput(GLFWwindow* window, double xpos, double ypos);
void ProcessScrollInput(GLFWwindow* window, double xoffset, double yoffset);

// screen parameters, delta time parameters
float SCR_WIDTH, SCR_HEIGHT;
float deltatime = 0.0f;
float lastframe = 0.0f;

camera Camera(glm::vec3(0.0f,0.0f,0.0f));

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
	SCR_WIDTH = static_cast <unsigned int> (mode->width);
	SCR_HEIGHT = static_cast <unsigned int> (mode->height);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Parkour Game", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Window Creation Failed" << std::endl;
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, ProcessMouseInput);
	glfwSetScrollCallback(window, ProcessScrollInput);
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	renderer cube("Resource/cubeVertex.shader", "Resource/cubeFragment.shader");
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast <float> (glfwGetTime());
		deltatime = currentFrame - lastframe;
		lastframe = currentFrame;
		ProcessInput(window, deltatime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.DrawSprite(Camera, glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0.5f, 1.0f, 1.0f), SCR_WIDTH, SCR_HEIGHT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool firstMouse = true;
float lastX = SCR_WIDTH;
float lastY = SCR_HEIGHT;

void ProcessMouseInput(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	Camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void ProcessInput(GLFWwindow* window, float deltatime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Camera.ProcessKeyboardMovement(FORWARD, deltatime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Camera.ProcessKeyboardMovement(BACKWARD, deltatime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Camera.ProcessKeyboardMovement(RIGHT, deltatime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Camera.ProcessKeyboardMovement(LEFT, deltatime);

}

void ProcessScrollInput(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera.ProcessScrollMovement(static_cast<float>(yoffset));
	
}
