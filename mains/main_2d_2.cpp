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
//#include "../Objects/Object.h"
//#include "../Graphics/TextureManager.h"
//#include "../Components/Graphics/SpriteComponent.h"
//#include "../Helpers/Math.h"
//#include "../Graphics/SpriteBatch.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action,
//	int mode);
//
//float SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
//
//void coutMat(const mat4& m4) 
//{
//	for (int i = 0; i < 4; i++) 
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			std::cout << m4[i][j] << "\t";
//		}
//		std::cout << std::endl;
//	}
//}
//
//void coutVec(vec4 v)
//{
//	for(int i=0;i<4;i++)
//	{
//		std::cout << v[i] << "\t";
//	}
//	std::cout << std::endl;
//}
//
//int main() 
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr,
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
//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	glfwSetKeyCallback(window, key_callback);
//
//	glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
//	
//	star::Object obj,obj2;
//	//	star::TextureManager* p_TextureManager =  star::TextureManager::GetInstance();
//	tstring path = "E:\\mhxy_code_repo\\Engine\\assets\\images\\bizhi.jpg";
//	tstring name = "wall";
//
//	obj.BaseInitialize();
//	obj.AddComponent(new star::SpriteComponent(path, name, 1, 1));
//	
//	tstring path2 = "E:\\mhxy_code_repo\\Engine\\assets\\images\\wall.jpg";
//	tstring name2 = "wall2";
//	obj2.BaseInitialize();
//	obj2.AddComponent(new star::SpriteComponent(path2, name2, 1, 1));
//
//	star::Context context;
//	int i = 4;
//	int j = 3;
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//		obj.BaseUpdate(context);
//		obj.GetTransform()->TranslateX(i--);
//		obj.BaseDraw();
//	
//		obj2.BaseUpdate(context);
//		obj2.GetTransform()->TranslateY(j++);
//		obj2.BaseDraw();
//
//
//		star::SpriteBatch::GetInstance()->Flush();
//		glfwSwapBuffers(window);
//	}
//	glfwTerminate();
//
//	return 0;
//
//
//	while (true);
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