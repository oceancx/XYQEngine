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
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//void do_movement();
//
//
//int WIDTH = 960, HEIGHT = 800;
//
//// Camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//GLfloat fov= 45.0f;
//GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
//GLfloat pitch = 0.0f;
//GLfloat lastX = WIDTH / 2.0;
//
//
//GLfloat lastY = HEIGHT / 2.0;
//bool keys[1024];
//
//// Deltatime
//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
//GLfloat lastFrame = 0.0f;  	// Time of last frame
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
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr,
//		nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	// GLFW Options
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//	glViewport(0, 0, WIDTH, HEIGHT);
//	glfwSetKeyCallback(window, key_callback);
//
//	glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
//
//	star::Texture2D texture2(_TT("E:\\mhxy_code_repo\\Engine\\assets\\images\\wall.jpg"));
//	star::Texture2D texture(_TT("E:\\mhxy_code_repo\\Engine\\assets\\images\\qinyuan.jpg"));
//	printf("w:%d h:%d\n", texture2.GetWidth(), texture2.GetHeight());
//	float ratio = texture2.GetWidth() * 1.0f / texture2.GetHeight();
//	float swRatio = WIDTH* 1.0f / HEIGHT;
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
//	tstring vShader(_TT("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\shader_9_7.vert")),
//		fShader(_TT("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\shader_7_6.frag"));
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
//		// Calculate deltatime of current frame
//		GLfloat currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		glfwPollEvents();
//		do_movement();
//
//
//		glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		
//
//		glBindVertexArray(VAO);
//			glBindBuffer(GL_ARRAY_BUFFER, VBO);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3,
//				GL_STATIC_DRAW);
//
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (
//				GLvoid*)0);
//			glEnableVertexAttribArray(0);
//
//			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (
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
//		// Camera/View transformation
//		glm::mat4 view;
//		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//
//		glm::mat4 projection;
//
//		projection = glm::perspective(fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f,
//			100.0f);
//
//		GLint modelLoc = shader.GetUniformLocation("model");
//		GLint viewLoc = shader.GetUniformLocation("view");
//		GLint perspectiveLoc = shader.GetUniformLocation("projection");
//
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		glBindVertexArray(VAO);
//		for (GLuint i = 0; i < 10; i++)
//		{
//			glm::mat4 model;
//			GLfloat angle = 20.0f * i;
//			model = glm::translate(model, cubePositions[i]);
//			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
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
//// Is called whenever a key is pressed/released via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//			keys[key] = true;
//		else if (action == GLFW_RELEASE)
//			keys[key] = false;
//	}
//}
//void do_movement()
//{
//	// Camera controls
//	GLfloat cameraSpeed = 5.0f * deltaTime;
//	if (keys[GLFW_KEY_W])
//		cameraPos += cameraSpeed * cameraFront;
//	if (keys[GLFW_KEY_S])
//		cameraPos -= cameraSpeed * cameraFront;
//	if (keys[GLFW_KEY_A])
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	if (keys[GLFW_KEY_D])
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}
//
//bool firstMouse = true;
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
//	lastX = xpos;
//	lastY = ypos;
//
//	GLfloat sensitivity = 0.05;	// Change this value to your liking
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	// Make sure that when pitch is out of bounds, screen doesn't get flipped
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//
//	glm::vec3 front;
//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	front.y = sin(glm::radians(pitch));
//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//	cameraFront = glm::normalize(front);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	if (fov >= 1.0f && fov <= 45.0f)
//		fov -= yoffset;
//	if (fov <= 1.0f)
//		fov = 1.0f;
//	if (fov >= 45.0f)
//		fov = 45.0f;
//}