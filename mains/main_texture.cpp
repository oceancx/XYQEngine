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
//	star::Texture2D texture(_T("E:\\mhxy_code_repo\\Engine\\assets\\images\\wall.jpg"));
//	star::Texture2D texture2(_T("E:\\mhxy_code_repo\\Engine\\assets\\images\\qinyuan.jpg"));
//	printf("w:%d h:%d\n", texture2.GetWidth(), texture2.GetHeight());
//	float ratio = texture2.GetWidth() * 1.0f / texture2.GetHeight();
//	float swRatio = screenWidth* 1.0f / screenHeight;
//	/*
//		TR x+w,y+h
//		BR x+w,y
//		BL x,y
//		TL x,y+h
//	*/
//	float x, y, w, h;
//	w = 1.0f;
//	h = swRatio / ratio;
//	x = -w/2;
//	y = -h/2;
//	
//	
//	GLfloat vertices[] = {
//		// Positions // Colors // Texture Coords
//		x+w, y+h, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
//		x+w, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
//		x, y, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
//		x, y+h, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // Top Left
//	};
//	GLuint indices[] = { // Note that we start from 0!
//		0, 1, 3, // First Triangle
//		1, 2, 3 // Second Triangle
//	};
//
//	tstring vShader(_T("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\shader_7_6.vert")),
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
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (
//				GLvoid*)0);
//			glEnableVertexAttribArray(0);
//			
//			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  8 * sizeof(GLfloat),(
//				GLvoid*)(3*sizeof(GLfloat)));
//			glEnableVertexAttribArray(1);
//
//			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid
//				*)(6 * sizeof(GLfloat)));
//			
//			glEnableVertexAttribArray(2);
//
//		glBindVertexArray(0);
//
//		shader.Bind();
//	//	glActiveTexture(GL_TEXTURE0);
//	//	glBindTexture(GL_TEXTURE_2D ,texture.GetTextureID());
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D,  texture2.GetTextureID());
//		glUniform1i(shader.GetUniformLocation("ourTexture1"), 0);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D,  texture.GetTextureID());
//		glUniform1i(shader.GetUniformLocation("ourTexture2"), 1);
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