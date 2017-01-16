#pragma once

#include "defines.h"
#include "BaseGame.h"
#include "Context.h"
/*
游戏管理类 有begin end update draw
持有Engine的引用，用Engine来对游戏状态更新
Game管理Engine
*/
namespace star
{	
	enum GameState {
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

	class Game :public BaseGame
	{
	public:
		Game(std::string title="");
		~Game();

		//  初始化 做一些全局变量初始化 由program调用 游戏状态变为开始
		void Initialize(int32, int32);

		// 
		void Update();

		void Draw();

		void End();

		std::string GetTitle(){return m_Title;}

	private:
		std::string m_Title;
		int32 m_Width;
		int32 m_Height;
		GameState m_State;
		Context m_Context;

		Game & operator=(const Game&);
		Game & operator=(Game&&);
		Game(const Game &);
		Game(Game &&);
	};
}
