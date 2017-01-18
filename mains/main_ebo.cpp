////GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
//// GLFW
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "../Graphics/Shader.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include "../Helpers/Helpers.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action,
//	int mode);
//
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr,
//		nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//	glfwSetKeyCallback(window, key_callback);
//
//	glClearColor(0.7f, 0.3f, 0.3f, 1.0f);	
//
//
//	GLfloat vertices[] = {
//		0.5f, 0.5f, 0.0f, // Top Right
//		0.5f, -0.5f, 0.0f, // Bottom Right
//		-0.5f, -0.5f, 0.0f, // Bottom Left
//		-0.5f, 0.5f, 0.0f // Top Left
//	};
//	GLuint indices[] = { // Note that we start from 0!
//		0, 1, 3, // First Triangle
//		1, 2, 3 // Second Triangle
//	};
//
//	tstring vShader(_T("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\simple_shader.ver")),
//		fShader(_T("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\simple_shader.frg"));
//	star::Shader shader(vShader, fShader);
//
//
//	GLuint VBO;
//	glGenBuffers(1, &VBO);
//
//	GLuint EBO;
//	glGenBuffers(1, &EBO);
//
//	GLuint VAO;
//	glGenVertexArrays(1, &VAO);
//	
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		glClear(GL_COLOR_BUFFER_BIT);
//		
//		glBindVertexArray(VAO);
//	
//			glBindBuffer(GL_ARRAY_BUFFER, VBO);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
//				GL_STATIC_DRAW);
//	
//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
//				GL_STATIC_DRAW);
//	
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (
//				GLvoid*)0);
//			glEnableVertexAttribArray(0);
//	
//		glBindVertexArray(0);
//
//		shader.Bind();
//
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//	glfwTerminate();
//
//	return 0;
//}
//
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action,
//	int mode)
//{
//	// When a user presses the escape key, we set the WindowShouldClose property to true,
//	// closing the application
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//}