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
#include "Scenes\BaseScene.h"
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
	Object* obj;
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
		
		obj = new Object("obj");
		obj->AddComponent(new CameraComponent());
		obj->BaseInitialize();
		//auto camera= obj.GetComponent<CameraComponent>(true);
		
		scene = new BaseScene("JYC");
		scene->AddObject(obj);
	//	scene->BaseInitialize();

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
