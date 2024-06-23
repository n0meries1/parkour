#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>

#include "renderer.h"
#include "camera.h"
#include "Player.h"

//prototyping
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window, float deltatime);
void ProcessMouseInput(GLFWwindow* window, double xpos, double ypos);
void ProcessScrollInput(GLFWwindow* window, double xoffset, double yoffset);

// screen parameters, delta time parameters
float SCR_WIDTH, SCR_HEIGHT;
float deltatime = 0.0f;
float lastframe = 0.0f;

Player player(glm::vec3(0.0f, 5.0f, 0.0f));
camera Camera(glm::vec3(player.playerPosition.x, player.playerPosition.y + 1.0, player.playerPosition.z + 3.0f));

std::vector <glm::vec3> toDraw{
	// Obstacle 1
	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f),
	// Obstacle 2
	glm::vec3(5.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f),
	// Obstacle 3
	glm::vec3(10.0f, 2.0f, 0.0f), glm::vec3(4.0f, 1.0f, 4.0f),
	// Obstacle 4
	glm::vec3(15.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
	// Obstacle 5
	glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(3.0f, 2.0f, 3.0f),
	// Obstacle 6
	glm::vec3(25.0f, 1.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f),
	// Obstacle 7
	glm::vec3(30.0f, 2.0f, 0.0f), glm::vec3(3.0f, 2.0f, 3.0f),
	// Obstacle 8
	glm::vec3(35.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f),
	// Obstacle 9
	glm::vec3(40.0f, 2.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f),
	// Obstacle 10
	glm::vec3(45.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)
	//// Obstacle 11
	//glm::vec3(50.0f, 0.0f, 0.0f), glm::vec3(4.0f, 2.0f, 4.0f),
	//// Obstacle 12
	//glm::vec3(55.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f),
	//// Obstacle 13
	//glm::vec3(60.0f, 2.0f, 0.0f), glm::vec3(3.0f, 2.0f, 3.0f),
	//// Obstacle 14
	//glm::vec3(65.0f, 1.0f, 0.0f), glm::vec3(2.0f, 3.0f, 2.0f),
	//// Obstacle 15
	//glm::vec3(70.0f, 3.0f, 0.0f), glm::vec3(3.0f, 1.0f, 3.0f),
	//// Obstacle 16
	//glm::vec3(75.0f, 0.0f, 0.0f), glm::vec3(4.0f, 2.0f, 4.0f),
	//// Obstacle 17
	//glm::vec3(80.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f),
	//// Obstacle 18
	//glm::vec3(85.0f, 2.0f, 0.0f), glm::vec3(3.0f, 2.0f, 3.0f),
	//// Obstacle 19
	//glm::vec3(90.0f, 1.0f, 0.0f), glm::vec3(2.0f, 3.0f, 2.0f),
	//// Obstacle 20
	//glm::vec3(95.0f, 3.0f, 0.0f), glm::vec3(3.0f, 1.0f, 3.0f),
	//// Obstacle 21
	//glm::vec3(100.0f, 0.0f, 0.0f), glm::vec3(4.0f, 2.0f, 4.0f),
	//// Obstacle 22
	//glm::vec3(105.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f),
	//// Obstacle 23
	//glm::vec3(110.0f, 2.0f, 0.0f), glm::vec3(3.0f, 2.0f, 3.0f),
	//// Obstacle 24
	//glm::vec3(115.0f, 1.0f, 0.0f), glm::vec3(2.0f, 3.0f, 2.0f),
	//// Obstacle 25
	//glm::vec3(120.0f, 3.0f, 0.0f), glm::vec3(3.0f, 1.0f, 3.0f),
	//// Obstacle 26
	//glm::vec3(125.0f, 0.0f, 0.0f), glm::vec3(4.0f, 2.0f, 4.0f),
	//// Obstacle 27
	//glm::vec3(130.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f),
	//// Obstacle 28
	//glm::vec3(135.0f, 2.0f, 0.0f), glm::vec3(3.0f, 2.0f, 3.0f),
	//// Obstacle 29
	//glm::vec3(140.0f, 1.0f, 0.0f), glm::vec3(2.0f, 3.0f, 2.0f),
	//// Obstacle 30
	//glm::vec3(145.0f, 3.0f, 0.0f), glm::vec3(3.0f, 1.0f, 3.0f),
};

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

	glEnable(GL_DEPTH_TEST);
	renderer playercharacter("Resource/cubeVertex.shader", "Resource/cubeFragment.shader", "Resource/grassblock.jpg", false);
	renderer cube("Resource/cubeVertex.shader", "Resource/cubeFragment.shader", "Resource/brick.png", false);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast <float> (glfwGetTime());
		deltatime = currentFrame - lastframe;
		lastframe = currentFrame;
		ProcessInput(window, deltatime);
		player.Update(deltatime);


		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		playercharacter.DrawSprite(player, Camera, player.playerPosition, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), SCR_WIDTH, SCR_HEIGHT);

		for (int i = 0; i < toDraw.size(); i+=2)
		{
			cube.DrawSprite(player, Camera, toDraw[i], toDraw[i+1], 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), SCR_WIDTH, SCR_HEIGHT);
			player.objects.push_back(std::make_pair(toDraw[i], toDraw[i+1]));
		}

		
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

bool front, back, left, right;
void ProcessInput(GLFWwindow* window, float deltatime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	glm::vec3 direction = glm::vec3(0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		direction += Camera.m_front;
		front = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		direction -= Camera.m_front;
		back = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		direction += Camera.m_right;
		right = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		direction -= Camera.m_right;
		left = true;
	}
	
	if (front == true && glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
	{
		player.velocity.z = 0;
		player.velocity.x = 0;
		front = false;
		
	}
	if (back == true && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
	{
		player.velocity.z = 0;
		player.velocity.x = 0;
		back = false;
	}
	if (right == true && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		player.velocity.z = 0;
		player.velocity.x = 0;
		right = false;
	}
	if (left == true && glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
	{
		player.velocity.z = 0;
		player.velocity.x = 0;
		left = false;	
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		player.Jump();

	if (glm::length(direction) > 0)
	{
		direction = glm::normalize(direction);
		player.ApplyForce(direction * deltatime * 5000.0f);
	}


	
	Camera.UpdateCamera(player.playerPosition);

}

void ProcessScrollInput(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera.ProcessScrollMovement(static_cast<float>(yoffset));
	
}

