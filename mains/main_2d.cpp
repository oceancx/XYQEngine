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
//#include "../Graphics/Texture2D.h"
//#include "../Helpers/Helpers.h"
//#include "../Helpers/glm/glm.h"
//#include "../Helpers/Math.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action,
//	int mode);
//
//GLuint VBO;
//GLuint EBO;
//GLuint VAO;
//
//GLuint m_VertexID,
//m_UVID,
//m_IsHUDID;
//
//GLuint	m_TextureSamplerID,
//m_ColorID,
//m_ScalingID,
//m_ViewInverseID,
//m_ProjectionID;
//
//float SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
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
//	tstring vShader(_TT("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\engine_test.vert")),
//		fShader(_TT("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\engine_test.frag"));
//	
//	star::Shader* m_ShaderPtr = new star::Shader(vShader, fShader);
//	star::Texture2D texture(_TT("E:\\mhxy_code_repo\\Engine\\assets\\images\\wall.jpg"));
//
//	GLfloat tw, th;
//	tw = texture.GetWidth();
//	th = texture.GetHeight();
//	GLfloat tx, ty;
//	tx = 40, ty = 50;
//	std::vector<GLfloat> positions = {
//		0,th,0,1,
//		tw,th,0,1,
//		0,0,0,1,
//		tw,th,0,1,
//		tw,0,0,1,
//		0,0,0,1,
//	};
//
//	std::vector<GLfloat> toors= {
//		0,1,
//		1,1,
//		0,0,
//		1,1,
//		1,0,
//		0,0,
//	};
//
//	std::vector<GLfloat> colors = {
//
//		0.8f,0.8f,0.8f,1.0f,
//		0.8f,0.8f,0.8f,1.0f,
//		0.8f,0.8f,0.8f,1.0f,
//
//		0.8f,0.8f,0.8f,1.0f,
//		0.8f,0.8f,0.8f,1.0f,
//		0.8f,0.8f,0.8f,1.0f,
//	};
//
//
//	std::vector<GLfloat> huds= {
//		1,
//		1,
//		1,
//
//		1,
//		1,
//		1,
//	};
//
//	m_TextureSamplerID = m_ShaderPtr->GetUniformLocation("textureSampler");
//	m_ScalingID = m_ShaderPtr->GetUniformLocation("scaleMatrix");
//	m_ViewInverseID = m_ShaderPtr->GetUniformLocation("viewInverseMatrix");
//	m_ProjectionID = m_ShaderPtr->GetUniformLocation("projectionMatrix");
// 
//	//Set uniforms
//	glUniform1i(m_TextureSamplerID, 0);
//	glm::mat4 model;
//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//	
//	glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, 0.0f,SCREEN_HEIGHT , -1.0f, 1.0f);
//	
//	glm::mat4 viewInverseMat;
//	
//	glGenBuffers(1, &VBO);
//	glGenVertexArrays(1, &VAO);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	int a = (positions.size() + toors.size() + colors.size() + huds.size()) * sizeof(GLfloat);
//	glBufferData(GL_ARRAY_BUFFER, (positions.size() + toors.size() + colors.size() + huds.size()) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
//	int b = positions.size() * sizeof(GLfloat);
//	glBufferSubData(GL_ARRAY_BUFFER, 0,
//		positions.size() * sizeof(GLfloat),
//		&positions[0]);
//
//	int c = toors.size() * sizeof(GLfloat);
//	glBufferSubData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat),
//		toors.size() * sizeof(GLfloat),
//		&toors[0]);
//
//	int d = colors.size() * sizeof(GLfloat);
//	glBufferSubData(GL_ARRAY_BUFFER, (positions.size() + toors.size()) * sizeof(GLfloat),
//		colors.size() * sizeof(GLfloat),
//		&colors[0]);
//
//	int e = huds.size() * sizeof(GLfloat);
//	glBufferSubData(GL_ARRAY_BUFFER, (positions.size() + toors.size() + colors.size()) * sizeof(GLfloat),
//		huds.size() * sizeof(GLfloat),
//		&huds[0]);
//
//	glBindVertexArray(VAO);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	glEnableVertexAttribArray(3);
//
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,
//		//	&positions[0]
//		(GLvoid*)0
//	);
//
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (
//		//	&toors[0]
//		GLvoid*)(positions.size() * sizeof(GLfloat)
//			));
//
//	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (
//		GLvoid*)((positions.size() + toors.size()) * sizeof(GLfloat)
//			//&colors[0]
//			));
//
//	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (
//		GLvoid*)((positions.size() + toors.size() + colors.size()) * sizeof(GLfloat)
//			//	&huds[0]
//			));
//
//	glBindVertexArray(0);
//	
//	m_ShaderPtr->Bind();
//
//	//mat4 scaleMat =star::Scale(1.0f, 1.0f, 0);
//	glUniformMatrix4fv(m_ScalingID, 1, GL_FALSE, star::ToPointerValue(model));
//	glUniformMatrix4fv(m_ProjectionID, 1, GL_FALSE, star::ToPointerValue(projection));
//	glUniformMatrix4fv(m_ViewInverseID, 1, GL_FALSE, star::ToPointerValue(viewInverseMat));
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		glClear(GL_COLOR_BUFFER_BIT);
//		
//		
//
//		glActiveTexture(GL_TEXTURE0);
//		
//		glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
//
//		glBindVertexArray(VAO);
//		
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//	//	glDrawArrays(GL_TRIANGLES, 6, 6);
//	glBindVertexArray(0);
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