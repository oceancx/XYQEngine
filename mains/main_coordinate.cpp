////GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
//// GLFW
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "../Graphics/Shader.h"
//#include "../Graphics/Texture2D.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include "../Helpers/Helpers.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action,
//	int mode);
//
//
//int screenWidth = 960, screenHeight = 800;
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr,
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
//	glViewport(0, 0, screenWidth, screenHeight);
//	glfwSetKeyCallback(window, key_callback);
//
//	glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
//
//	star::Texture2D texture2(_T("E:\\mhxy_code_repo\\Engine\\assets\\images\\wall.jpg"));
//	star::Texture2D texture(_T("E:\\mhxy_code_repo\\Engine\\assets\\images\\qinyuan.jpg"));
//	printf("w:%d h:%d\n", texture2.GetWidth(), texture2.GetHeight());
//	float ratio = texture2.GetWidth() * 1.0f / texture2.GetHeight();
//	float swRatio = screenWidth* 1.0f / screenHeight;
//	/*
//	TR x+w,y+h
//	BR x+w,y
//	BL x,y
//	TL x,y+h
//	*/
//	float x, y, w, h;
//	w = 1.0f;
//	h = swRatio / ratio;
//	x = -w / 2;
//	y = -h / 2;
//
//
//	GLfloat vertices[] = {
//		// Positions // Colors // Texture Coords
//		x + w, y + h, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
//		x + w, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
//		x, y, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
//		x, y + h, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // Top Left
//	};
//	GLuint indices[] = { // Note that we start from 0!
//		0, 1, 3, // First Triangle
//		1, 2, 3 // Second Triangle
//	};
//
//	GLfloat vertices2[] = {
//		// Positions // Colors // Texture Coords
//		x + w, y + h, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
//		x + w, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
//		x, y, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
//		x, y + h, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // Top Left
//	};
//	
//	GLfloat vertices3[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//	glm::vec3 cubePositions[] = {
//		glm::vec3(0.0f, 0.0f, 0.0f),
//		glm::vec3(2.0f, 5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3(2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f, 3.0f, -7.5f),
//		glm::vec3(1.3f, -2.0f, -2.5f),
//		glm::vec3(1.5f, 2.0f, -2.5f),
//		glm::vec3(1.5f, 0.2f, -1.5f),
//		glm::vec3(-1.3f, 1.0f, -1.5f)
//	};
//
//	tstring vShader(_T("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\shader_9_7.vert")),
//		fShader(_T("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\shader_7_6.frag"));
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
//	glEnable(GL_DEPTH_TEST);
//	while (!glfwWindowShouldClose(window))
//	{
//		glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glfwPollEvents();
//
//		glBindVertexArray(VAO);
//
//			glBindBuffer(GL_ARRAY_BUFFER, VBO);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3,
//				GL_STATIC_DRAW);
//
//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
//				GL_STATIC_DRAW);
//
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (
//				GLvoid*)0);
//			glEnableVertexAttribArray(0);
//
//			glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (
//				GLvoid*)(3 * sizeof(GLfloat)));
//			glEnableVertexAttribArray(2);
//
//		glBindVertexArray(0);
//
//		shader.Bind();
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture2.GetTextureID());
//		glUniform1i(shader.GetUniformLocation("ourTexture"), 0);
//		
//
//		glm::mat4 view;
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//		
//		glm::mat4 projection;
//		projection = glm::perspective(45.0f, screenWidth *1.0f/ screenHeight, 0.1f,
//			100.0f);
//		
//		GLint modelLoc = shader.GetUniformLocation( "model");
//		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//		GLint viewLoc = shader.GetUniformLocation("view");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//
//		GLint perspectiveLoc = shader.GetUniformLocation("projection");
//		glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		glBindVertexArray(VAO);
//		for (GLuint i = 0; i < 10; i++)
//		{
//			glm::mat4 model;
//			model = glm::translate(model, cubePositions[i]);
//			GLfloat angle = (GLfloat)glfwGetTime() * 20.0f * (i+1);
//			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		glBindVertexArray(0);
//
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