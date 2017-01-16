#include "SpriteBatch.h"
#include "../Objects/Object.h"
//#include "../Scenes/SceneManager.h"
//#include "GraphicsManager.h"
//#include "../Components/CameraComponent.h"
//#include "../Objects/FreeCamera.h"
//#include "../Scenes/BaseScene.h"
#include <algorithm>
#include "../Helpers/Math.h"
#include "../Helpers/glm/glm.h"
#include "Texture2D.h"
//#include "ScaleSystem.h"
//#include "Font.h"

namespace star
{
	SpriteBatch::SpriteBatch()
		: Singleton<SpriteBatch>()
		, m_SpriteQueue()
		//, m_TextQueue()
		, m_VertexBuffer()
		, m_UvCoordBuffer()
		, m_IsHUDBuffer()
		, m_ColorBuffer()
		, m_TextureSamplerID(0)
		, m_ColorID(0)
		, m_ScalingID(0)
		, m_ViewInverseID(0)
		, m_ProjectionID(0)
		, m_ShaderPtr(nullptr)
		, m_SpriteSortingMode(SpriteSortingMode::BackToFront)
	{
	//	Initialize();
	}
	
	SpriteBatch::~SpriteBatch(void)
	{
		delete m_ShaderPtr;
	}

	void SpriteBatch::Initialize()
	{
		//Set Shader and shader variables
		tstring vShader(_T("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\engine_test.vert")),
				fShader(_T("E:\\mhxy_code_repo\\Engine\\assets\\shaders\\engine_test.frag"));

		m_ShaderPtr = new Shader(vShader, fShader);

		m_VertexID = 0;
		m_UVID = 1;
		m_ColorID = 2;
		m_IsHUDID = 3;

		m_TextureSamplerID = m_ShaderPtr->GetUniformLocation("textureSampler");
		m_ScalingID = m_ShaderPtr->GetUniformLocation("scaleMatrix");
		m_ViewInverseID = m_ShaderPtr->GetUniformLocation("viewInverseMatrix");
		m_ProjectionID = m_ShaderPtr->GetUniformLocation("projectionMatrix");


		glGenBuffers(1, &m_VBO);
		glGenVertexArrays(1, &m_VAO);

		m_ShaderPtr->Bind();
		const mat4 viewInverseMat;// = GraphicsManager::GetInstance()->GetViewInverseMatrix();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 projectionMat = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		glUniform1i(m_TextureSamplerID, 0);

		glUniformMatrix4fv(m_ScalingID, 1, GL_FALSE, ToPointerValue(model));
		glUniformMatrix4fv(m_ViewInverseID, 1, GL_FALSE, ToPointerValue(viewInverseMat));
		glUniformMatrix4fv(m_ProjectionID, 1, GL_FALSE, ToPointerValue(projectionMat));

		m_ShaderPtr->Unbind();
		
		
	}

	void SpriteBatch::Flush()
	{
		Begin();
		
		DrawSprites();
		
		//Clear vertex, uv, color and isHud buffer
//		DrawTextSprites();
		End();
	}
	
	void SpriteBatch::Begin()
	{
		//Create Vertexbuffer
//		SortSprites(m_SpriteSortingMode);
		CreateSpriteQuads();
		
		m_ShaderPtr->Bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		int vbsize = m_VertexBuffer.size() * sizeof(GLfloat);
		int tbsize = m_UvCoordBuffer.size() * sizeof(GLfloat);
		int cbsize = m_ColorBuffer.size() * sizeof(GLfloat);
		int hbsize = m_IsHUDBuffer.size() * sizeof(GLfloat);

		glBufferData(GL_ARRAY_BUFFER, (vbsize + tbsize + cbsize + hbsize), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0,
			vbsize,
			&m_VertexBuffer[0]);
		glBufferSubData(GL_ARRAY_BUFFER, vbsize,
			tbsize,
			&m_UvCoordBuffer[0]);
		glBufferSubData(GL_ARRAY_BUFFER, vbsize + tbsize,
			cbsize,
			&m_ColorBuffer[0]);
		glBufferSubData(GL_ARRAY_BUFFER, vbsize + tbsize + cbsize,
			hbsize,
			&m_IsHUDBuffer[0]);

		
		glBindVertexArray(m_VAO);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,
				(GLvoid*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,
				(GLvoid*)(vbsize));
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0,
				(GLvoid*)(vbsize + tbsize));
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0,
				(GLvoid*)(vbsize + tbsize + cbsize));
		glBindVertexArray(0);

		
		
	}
	
	void SpriteBatch::DrawSprites()
	{			
		uint32 batchStart(0);
		uint32 batchSize(0);
		GLuint texture(0);
		for(const SpriteInfo* currentSprite : m_SpriteQueue)
		{	
			//If != -> Flush
			if(texture != currentSprite->textureID)
			{
				FlushSprites(batchStart, batchSize, texture);

				batchStart += batchSize;
				batchSize = 0;

				texture = currentSprite->textureID;
			}
			++batchSize;
		}	
		FlushSprites(batchStart, batchSize, texture);
	}

	void SpriteBatch::FlushSprites(uint32 start, uint32 size, uint32 texture)
	{
		if(size > 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, start * 6, size * 6);	
			glBindVertexArray(0);
		}
	}
	
	void SpriteBatch::End()
	{
		//Unbind attributes and buffers
		glDisableVertexAttribArray(m_VertexID);
		glDisableVertexAttribArray(m_UVID);
		glDisableVertexAttribArray(m_IsHUDID);
		glDisableVertexAttribArray(m_ColorID);
		m_ShaderPtr->Unbind();

		m_SpriteQueue.clear();
	//	m_TextQueue.clear();

		m_VertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_IsHUDBuffer.clear();
		m_ColorBuffer.clear();
	}

	void SpriteBatch::DrawTextSprites()
	{	
		//CreateTextQuads();

		////FlushText once per TextComponent (same font)
		////Check per text how many characters -> Forloop drawing
		//int32 startIndex(0);
		//for(const TextInfo* text : m_TextQueue)
		//{
		//	GLuint* textures = text->font->GetTextures();

		//	const tchar *start_line = text->text.c_str();
		//	for(int32 i = 0 ; start_line[i] != 0 ; ++i) 
		//	{
		//		if(start_line[i] > FIRST_REAL_ASCII_CHAR)
		//		{
		//			glBindTexture(GL_TEXTURE_2D, textures[start_line[i]]);

		//			//Set attributes and buffers
		//			glVertexAttribPointer(m_VertexID, 4, GL_FLOAT, 0, 0,
		//				reinterpret_cast<GLvoid*>(&m_VertexBuffer.at(0)));
		//			glVertexAttribPointer(m_UVID, 2, GL_FLOAT, 0, 0, 
		//				reinterpret_cast<GLvoid*>(&m_UvCoordBuffer.at(0)));
		//			glVertexAttribPointer(m_IsHUDID, 1, GL_FLOAT, 0, 0,
		//				reinterpret_cast<GLvoid*>(&m_IsHUDBuffer.at(0)));
		//			glVertexAttribPointer(m_ColorID, 4, GL_FLOAT, 0, 0,
		//				reinterpret_cast<GLvoid*>(&m_ColorBuffer.at(0)));
		//			glDrawArrays(GL_TRIANGLES, startIndex * 6, 6);
		//		}
		//		++startIndex;
		//	}
		//}
	}

	void SpriteBatch::CreateSpriteQuads()
	{	
		//for every sprite that has to be drawn, push back all vertices 
		//(VERTEX_AMOUNT per sprite) into the vertexbuffer and all uvcoords 
		//(UV_AMOUNT per sprite) into the uvbuffer and the isHUD bool
		/*
		*  TL    TR
		*   0----1 
		*   |   /| 
		*   |  / |
		*   | /  |
		*   |/   |
		*   2----3
		*  BL    BR
		*/

		for(const SpriteInfo* sprite : m_SpriteQueue)
		{
			mat4 transformMat = Transpose(sprite->transformPtr->GetWorldMatrix());

			vec4 TL = vec4(0, sprite->vertices.y, 0, 1);
			Mul(TL, transformMat, TL);

			vec4 TR = vec4(sprite->vertices.x, sprite->vertices.y, 0, 1);
			Mul(TR, transformMat, TR);

			vec4 BL = vec4(0, 0, 0, 1);
			Mul(BL, transformMat, BL);

			vec4 BR = vec4(sprite->vertices.x, 0, 0, 1);
			Mul(BR, transformMat, BR);

			//0
			m_VertexBuffer2.push_back(TL);

			//1
			m_VertexBuffer2.push_back(TR);

			//2
			m_VertexBuffer2.push_back(BL);

			//1
			m_VertexBuffer2.push_back(TR);

			//3
			m_VertexBuffer2.push_back(BR);

			//2
			m_VertexBuffer2.push_back(BL);

			//Push back all uv's

			//0
			m_UvCoordBuffer.push_back(sprite->uvCoords.x);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);

			//1
			m_UvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);

			//2
			m_UvCoordBuffer.push_back(sprite->uvCoords.x);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y);

			//1
			m_UvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);

			//3
			m_UvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y);

			//2
			m_UvCoordBuffer.push_back(sprite->uvCoords.x);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y);

			//bool & color buffer
			for(uint32 i = 0; i < 6; ++i)
			{
				m_IsHUDBuffer.push_back(float32(sprite->bIsHud));
			//	m_IsHUDBuffer.push_back(1);
				//rgba
				m_ColorBuffer2.push_back(sprite->colorMultiplier);
				m_ColorBuffer.push_back(sprite->colorMultiplier.r);
				m_ColorBuffer.push_back(sprite->colorMultiplier.g);
				m_ColorBuffer.push_back(sprite->colorMultiplier.b);
				m_ColorBuffer.push_back(sprite->colorMultiplier.a);
			}
		}
		
		for (auto a : m_VertexBuffer2) 
		{
			m_VertexBuffer.push_back(a.x);
			m_VertexBuffer.push_back(a.y);
			m_VertexBuffer.push_back(a.z);
			m_VertexBuffer.push_back(a.w);
			std::cout << " x : " << a.x << " y: " << a.y << " z: " << a.z << " w:" << a.w << std::endl;
		}
		m_VertexBuffer2.clear();
		m_ColorBuffer2.clear();
		
	}

	void SpriteBatch::CreateTextQuads()
	{
		//for every sprite that has to be drawn, push back all vertices 
		//(VERTEX_AMOUNT per sprite) into the vertexbuffer and all uvcoords 
		//(UV_AMOUNT per sprite) into the uvbuffer and the isHUD bool
		/*
		*  TL    TR
		*   0----1 
		*   |   /| 
		*   |  / |
		*   | /  |
		*   |/   |
		*   2----3
		*  BL    BR
		*/
		//for(const TextInfo* text : m_TextQueue)
		//{
		//	//Variables per textcomponent
		//	mat4 transformMat, offsetMatrix; 
		//	const mat4& worldMat = text->transformPtr->GetWorldMatrix();
		//	int32 line_counter(0);
		//	int32 offsetX(text->horizontalTextOffset.at(line_counter));
		//	int32 offsetY(0);
		//	int32 fontHeight(text->font->GetMaxLetterHeight() + text->font->GetMinLetterHeight());
		//	for(auto it : text->text)
		//	{
		//		const CharacterInfo& charInfo = text->font->GetCharacterInfo(static_cast<suchar>(it));
		//		offsetMatrix = Translate
		//			(vec3(
		//				offsetX, 
		//				offsetY + charInfo.letterDimensions.y + text->textHeight - fontHeight, 
		//				0));
		//		offsetX += charInfo.letterDimensions.x;

		//		transformMat = Transpose(worldMat * offsetMatrix);

		//		vec4 TL = vec4(0, charInfo.vertexDimensions.y, 0, 1);
		//		Mul(TL, transformMat, TL);

		//		vec4 TR = vec4(charInfo.vertexDimensions.x, charInfo.vertexDimensions.y, 0, 1);
		//		Mul(TR, transformMat, TR);

		//		vec4 BL = vec4(0, 0, 0, 1);
		//		Mul(BL, transformMat, BL);

		//		vec4 BR = vec4(charInfo.vertexDimensions.x, 0, 0, 1);
		//		Mul(BR, transformMat, BR);

		//		//0
		//		m_VertexBuffer.push_back(TL);

		//		//1
		//		m_VertexBuffer.push_back(TR);

		//		//2
		//		m_VertexBuffer.push_back(BL);

		//		//1
		//		m_VertexBuffer.push_back(TR);

		//		//3
		//		m_VertexBuffer.push_back(BR);

		//		//2
		//		m_VertexBuffer.push_back(BL);

		//		//Push back all uv's

		//		//0
		//		m_UvCoordBuffer.push_back(0);
		//		m_UvCoordBuffer.push_back(0);

		//		//1
		//		m_UvCoordBuffer.push_back(charInfo.uvDimensions.x);
		//		m_UvCoordBuffer.push_back(0);

		//		//2
		//		m_UvCoordBuffer.push_back(0);
		//		m_UvCoordBuffer.push_back(charInfo.uvDimensions.y);

		//		//1
		//		m_UvCoordBuffer.push_back(charInfo.uvDimensions.x);
		//		m_UvCoordBuffer.push_back(0);

		//		//3
		//		m_UvCoordBuffer.push_back(charInfo.uvDimensions.x);
		//		m_UvCoordBuffer.push_back(charInfo.uvDimensions.y);

		//		//2
		//		m_UvCoordBuffer.push_back(0);
		//		m_UvCoordBuffer.push_back(charInfo.uvDimensions.y);

		//		//bool & color buffer
		//		for(uint32 i = 0; i < 6; ++i)
		//		{
		//			m_IsHUDBuffer.push_back(float32(text->bIsHud));
		//			//rgba
		//			m_ColorBuffer.push_back(text->colorMultiplier);
		//		}

		//		if(it == _T('\n'))
		//		{
		//			offsetY -= text->font->GetMaxLetterHeight() + text->verticalSpacing;
		//			++line_counter;
		//			offsetX = text->horizontalTextOffset.at(line_counter);
		//		}
		//	}
		//}
	}

	void SpriteBatch::SortSprites(SpriteSortingMode mode)
	{
		switch(mode)
		{
		case SpriteSortingMode::BackToFront:
			std::sort(m_SpriteQueue.begin(), m_SpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
			{
				return a->transformPtr->GetWorldPosition().l < b->transformPtr->GetWorldPosition().l;
			});
			break;
		case SpriteSortingMode::FrontToBack:
			std::sort(m_SpriteQueue.begin(), m_SpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
			{
				return a->transformPtr->GetWorldPosition().l > b->transformPtr->GetWorldPosition().l;
			});
			break;
		case SpriteSortingMode::TextureID:
			std::sort(m_SpriteQueue.begin(), m_SpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
			{
				return a->textureID < b->textureID;
			});
			break;
		default:
			ASSERT_LOG(
				false,
				_T("SpriteBatch::SortSprites: Please implement this SpriteSortingMode"),
				STARENGINE_LOG_TAG
				);
			break;
		}
	}

	void SpriteBatch::AddSpriteToQueue(const SpriteInfo* spriteInfo)
	{
		m_SpriteQueue.push_back(spriteInfo);		
	}

	/*void SpriteBatch::AddTextToQueue(const TextInfo* text)
	{
		m_TextQueue.push_back(text);
	}*/

	void SpriteBatch::SetSpriteSortingMode(SpriteSortingMode mode)
	{
		m_SpriteSortingMode = mode;
	}
}
