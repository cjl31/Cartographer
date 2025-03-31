#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "Shader.h"
#include "Map.h"

Map map;
void processInput(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
	{
		map.robot->viewDirection = glm::vec2(0.0f, 1.0f);
		map.robot->Move();
	}
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
	{
		map.robot->viewDirection = glm::vec2(0.0f, -1.0f);
		map.robot->Move();
	}
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
	{
		map.robot->viewDirection = glm::vec2(-1.0f, 0.0f);
		map.robot->Move();
	}
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
	{
		map.robot->viewDirection = glm::vec2(1.0f, 0.0f);
		map.robot->Move();
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		map.robot->sensor.MassiveShotInDirection(map.robot->viewDirection);
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		map.robot->sensor.ShotAllDirections();
	}
}
void OnResize(GLFWwindow* win, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}

void TickerImplementation(float* _ticker)
{
	if (*_ticker <= 0.0f)
	{
		//map.robot.sensor.ShotAllDirections();
		*_ticker = 1000.0f;
	}
	(*_ticker) -= 1.0f;
}

void InitBoundsAndPushToMap(Map *map)
{
	float thickness = 0.25f;
	Shader* boundsShader = new Shader("shaders\\bounds.vert", "shaders\\bounds.frag");
	glm::vec3 color = glm::vec3(0.9f, 0.3f, 0.3f);
	Bound topBound = Bound(glm::vec2(-10.f, 5.f), glm::vec2(0.f, 5.f), thickness, boundsShader, &map->worldTransform);
	Bound bottomBound = Bound(glm::vec2(-10.f, -5.f), glm::vec2(-5.f, -5.f), thickness, boundsShader, &map->worldTransform);
	Bound leftBound = Bound(glm::vec2(-10.f, 5.f), glm::vec2(-10.f, -5.f), thickness, boundsShader, &map->worldTransform);
	Bound rightBound = Bound(glm::vec2(0, 5.f), glm::vec2(0, -0.f), thickness, boundsShader, &map->worldTransform);
	Bound bottomRightBound = Bound(glm::vec2(-5.f, -5.f), glm::vec2(0.f, -0.f), thickness, boundsShader, &map->worldTransform);
	Bound centerBound = Bound(glm::vec2(-8.f, -3.f), glm::vec2(-5.f, -3.f), thickness, boundsShader, &map->worldTransform);
	topBound.ChangeColor(color);
	bottomBound.ChangeColor(color);
	leftBound.ChangeColor(color);
	rightBound.ChangeColor(color);
	bottomRightBound.ChangeColor(color);
	color = glm::vec3(0.6f, 0.3f, 0.6f);
	centerBound.ChangeColor(color);
	(*map).addBound(topBound);
	(*map).addBound(bottomBound);
	(*map).addBound(leftBound);
	(*map).addBound(rightBound);
	(*map).addBound(bottomRightBound);
	(*map).addBound(centerBound);
}
void InitRobot(glm::vec2 _position)
{
	float size = 0.25f;
	Shader* robotShader = new Shader("shaders\\robot.vert", "shaders\\robot.frag");
	Shader* dotShader = new Shader("shaders\\dot.vert", "shaders\\dot.frag");
	map.addRobot(_position, size, robotShader, dotShader);
	map.robot->sensor.SetDotColor(glm::vec3(0.3f, 0.9f, 0.3f));
}
int main()
{
#pragma region WINDOW INITIALIZATION
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(720, 720, "OpenGL Window", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Error. Couldn't create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error. Couldn't load GLAD!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetFramebufferSizeCallback(win, OnResize);
	glViewport(0, 0, 720, 720);
	glfwSetKeyCallback(win, key_callback);
#pragma endregion
	InitBoundsAndPushToMap(&map);
	InitRobot(glm::vec2(-5.f ,0.f));
	map.worldTransform = glm::scale(map.worldTransform, glm::vec3(0.1f, 0.1f, 0.1f));

	while (!glfwWindowShouldClose(win))
	{
		glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		map.DrawEntities();

		processInput(win);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}


