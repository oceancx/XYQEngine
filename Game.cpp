#include "Game.h"
#include "StarEngine.h"
#include "Graphics\ScaleSystem.h"
#include "Graphics\GraphicsManager.h"
namespace star
{
	Game::Game(std::string title)
	{
		m_Title=title;
		StarEngine::GetInstance()->SetGameTitle(m_Title);
	}

	Game::~Game()
	{

	}

	void Game::Initialize(int32 width, int32 height)
	{
		m_Width = width;
		m_Height= height;
		m_State = GAME_ACTIVE;
		std::cout << "Initialize" << std::endl;
		m_Context.time = TimeManager::GetInstance();
		ScaleSystem::GetInstance()->SetWorkingResolution(width, height);
		StarEngine::GetInstance()->Initialize(width, height);
	}
	
	void Game::Update()
	{
		std::cout << "Update" << std::endl;
		StarEngine::GetInstance()->Update(m_Context);
	}

	void Game::Draw()
	{
		std::cout << "Draw" << std::endl;
		StarEngine::GetInstance()->Draw();


	}
	
	void Game::End()
	{
		std::cout << "End" << std::endl;

	}
}