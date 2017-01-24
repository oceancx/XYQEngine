#include "StarEngine.h"
#include "Graphics/GraphicsManager.h"
//#include "Graphics/SpriteAnimationManager.h"
#include "Graphics/SpriteBatch.h"
//#include "Graphics/FontManager.h"
#include "Graphics/ScaleSystem.h"
#include "Scenes/SceneManager.h"
//#include "Input/InputManager.h"
#include "Context.h"
#include "Logger.h"
//#include "Sound/AudioManager.h"
#include "Helpers/TimerManager.h"
//#include "AI/Pathfinding/PathFindManager.h"
//#include "Physics/Collision/CollisionManager.h"
#include "Helpers/Debug/DebugDraw.h"
#include "Helpers\Rect.h"

#include "Components\CameraComponent.h"
#include "Objects\Object.h"
#include "Objects\Player.h"
#include "Scenes\BaseScene.h"

#include "Graphics\Font.h"

#include "Components\Graphics\SpriteArrayComponent.h"
namespace star
{
	StarEngine * StarEngine::m_pEngine = nullptr;

	StarEngine::~StarEngine()
	{
	}

	StarEngine*  StarEngine::GetInstance()
	{
		if(m_pEngine == nullptr)
		{
			m_pEngine = new StarEngine();
		}
		return m_pEngine;
	}
	
	Font font;
	
	void RenderText(std::wstring text,int x,int y)
	{
		for (int i = 0; i < text.size(); i++)
		{
			wchar_t& c = text[i];
			const CharacterInfo& cinfo = font.GetCharacterInfo(c);
			GLfloat xpos = x ;
			GLfloat ypos = y;

			GLfloat w = cinfo.vertexDimensions.x;
			GLfloat h = cinfo.vertexDimensions.y;
			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			glBindTexture(GL_TEXTURE_2D, cinfo.textureId);
			GLuint VBO;
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (((int)w )>> 6); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	Player* obj;
	BaseScene* scene;
	
	void StarEngine::Initialize(int32 window_width, int32 window_height)
	{
		std::random_device seeder;
		m_RandomEngine.seed(seeder());

		//Only for windows we need to pas the window paramaters
		//for android these will be fetched when setting up the OpenGL context
		//within the Graphics Manager

		GraphicsManager::GetInstance()->Initialize(window_width,window_height);
		GraphicsManager::GetInstance()->SetWindowDimensions(window_width, window_height);

	//	AudioManager::GetInstance()->Start();
		GraphicsManager::GetInstance()->CalculateViewPort();
		SpriteBatch::GetInstance()->Initialize();
		DebugDraw::GetInstance()->Initialize();
		
		obj = new Player("obj");
		obj->AddComponent(new CameraComponent());
		obj->BaseInitialize();
		tstring playerPath = _T("E:\\mhxy_code_repo\\Engine\\assets\\fonts\\simsun.ttc");
		tstring playerName = _T("ËÎÌו");
		obj->AddComponent(new TextComponent(
			playerPath,
			playerName,
			14
		));


	/*	tstring playerPath = _T("E:\\mhxy_code_repo\\Engine\\assets\\animation\\mhxy3_");
		tstring playerName = _T("Player");
		obj->AddComponent(new SpriteArrayComponent(
			playerPath,
			playerName,
			1,1
		));*/


	
		//auto camera = obj.GetComponent<CameraComponent>(true);
		//tstring playerPath = _T("E:\\mhxy_code_repo\\Engine\\assets\\animation\\mhxy3_");
		//tstring playerName = _T("Player");
		

		scene = new BaseScene("JYC");
		scene->AddObject(obj);
	//	scene->BaseInitialize();


	
		/*FT_Library ft;
		FT_Init_FreeType(&ft);
		font.Init(_T( "E:\\mhxy_code_repo\\Engine\\assets\\fonts\\simsun.ttc"), 48, ft);
*/
		SceneManager::GetInstance()->AddScene(scene);
		SceneManager::GetInstance()->SetActiveScene("JYC");

	}

	void StarEngine::Update(const Context & context)
	{
		m_FPS.Update(context);
		SceneManager::GetInstance()->Update(context);
		GraphicsManager::GetInstance()->Update();
	//	InputManager::GetInstance()->EndUpdate();
		Logger::GetInstance()->Update(context);
		//'obj.BaseUpdate(context);
		m_bInitialized = true;

		//scene->BaseUpdate(context);
		std::cout << "Engine Update" << std::endl;
	}

	void StarEngine::Draw()
	{
		GraphicsManager::GetInstance()->StartDraw();
		if(m_bInitialized)
		{
			SceneManager::GetInstance()->Draw();
		}
		GraphicsManager::GetInstance()->StopDraw();
	/*	Color c = Color(0xff, 0, 0, 1);
		DebugDraw::GetInstance()->DrawLine(vec2(0.0f,0.0f),vec2(20.0f,20.0f), c);
		DebugDraw::GetInstance()->DrawPoint(vec2(50, 50), 30, Color(0xff, 0, 0, 1));
*/
		//scene->BaseDraw();

		std::cout << "Engine Draw" << std::endl;
	}

	void StarEngine::End()
	{
	//	FontManager::GetInstance()->EraseFonts();
		DebugDraw::DeleteSingleton();
		ScaleSystem::DeleteSingleton();
	//	FontManager::DeleteSingleton();
	//	SpriteAnimationManager::DeleteSingleton();
	//	TextureManager::DeleteSingleton();
		GraphicsManager::DeleteSingleton();
		SpriteBatch::DeleteSingleton();
	//	AudioManager::DeleteSingleton();
	//	PathFindManager::DeleteSingleton();
		SceneManager::DeleteSingleton();
		Logger::DeleteSingleton();
		TimeManager::DeleteSingleton();
	}
	
	void StarEngine::SetActive()
	{
	//	AudioManager::GetInstance()->ResumeAllSounds();
	}

	void StarEngine::SetInactive()
	{
	//	AudioManager::GetInstance()->PauseAllSounds();
	}

	int32 StarEngine::GetCurrentFPS() const
	{
		return m_FPS.CurrentFPS;
	}

	int32 StarEngine::GetPreviousFPS() const
	{
		return m_FPS.PreviousFPS;
	}

	void StarEngine::SetGameTitle(const tstring & title)
	{
		m_Title = title;
		m_TitleHasUpdated = true;
	}

	void StarEngine::SetGameSubTitle(const tstring & title)
	{
		m_SubTitle = title;
		m_TitleHasUpdated = true;
	}
	
	const tstring & StarEngine::GetGameTitle()
	{
		return m_Title;
	}

	bool StarEngine::HasTitleUpdated() const
	{
		return m_TitleHasUpdated;
	}

	void StarEngine::ResetTitleUpdateMark()
	{
		m_TitleHasUpdated = false;
	}

	std::mt19937& StarEngine::GetMt19937Engine()
	{
		return m_RandomEngine;
	}

	void StarEngine::Quit()
	{

	}

	StarEngine::StarEngine()
		: m_FPS()
		, m_Title(EMPTY_STRING)
		, m_SubTitle(EMPTY_STRING)
		, m_TitleHasUpdated(false) 
		, m_bInitialized (false)
		, m_RandomEngine()
	{

	}

}
