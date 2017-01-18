//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include<string>
#include<fstream>
#include<iostream>

#include "Game.h"

/*
初始化环境，例如创建窗口，接收消息等等，将一些事件通知给Game
环境管理Game
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mode);

float SCREEN_WIDTH = 800;
float SCREEN_HEIGHT = 600;
std::string GAME_TITLE = "梦幻西游";

star::Game* m_pGame;

int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glfwSetKeyCallback(window, key_callback);

	m_pGame = new star::Game(GAME_TITLE);
	m_pGame->Initialize(SCREEN_WIDTH,SCREEN_HEIGHT);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		glClearColor(0.7f, 0.7f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_pGame->Update();
		m_pGame->Draw();

		glfwSwapBuffers(window);
	}
	m_pGame->End();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true,
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}