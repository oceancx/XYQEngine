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
//	star::Object obj;
//	obj.BaseInitialize();
//	auto p_trans = obj.GetTransform();
//	
//	p_trans->Translate(4, 3);
//	p_trans->Scale(1, 1);
//
//	star::Context context;
//	p_trans->Update(context);
//	coutMat(p_trans->GetWorldMatrix());
//
//	vec4 tl(0, 3, 0, 1);
//	mat4 world = star::Transpose(p_trans->GetWorldMatrix());
//	tl = tl * world;
//	coutVec(tl);
//
////	star::TextureManager* p_TextureManager =  star::TextureManager::GetInstance();
//	tstring path = "E:\\mhxy_code_repo\\Engine\\assets\\images\\wall.jpg";
//	tstring name = "wall";
//	std::cout <<"what:::::"<< path << std::endl;
//
//
//	//p_TextureManager->LoadTexture(path,name);
//	//std::cout<<p_TextureManager->GetTextureID(name)<<std::endl;
//	//obj.AddComponent(new star::SpriteComponent(path, name, 1, 1));
//	//printf("w:%d h:%d\n", obj.GetTransform()->GetDimensions().x, obj.GetTransform()->GetDimensions().y);
//	
//	while (true);
//}