#include "Player.h"
#include "../Input/InputManager.h"
namespace star
{
	Player::Player() :Player("","")
	{
		//GetTransform()->Move(40, 40);
	}

	Player::Player(const tstring & name) : Player(name,"")
	{
		//GetTransform()->Move(40, 40);
	};

	Player::Player(const tstring & name,const tstring & groupTag) : Object(name, groupTag) 
	{
		GetTransform()->Move(40, 40);
	};

	Player::~Player()
	{

	}

	int delta = 0;
	void Player::Update(const Context & context)
	{
//		delta += context.dt;
		if (context.dt > 0) {
			// Move playerboard
			if (InputManager::GetInstance()->m_Keys[GLFW_KEY_A])
			{
				GetTransform()->MoveX(-1);
			}
			if (InputManager::GetInstance()->m_Keys[GLFW_KEY_D])
			{
				GetTransform()->MoveX(1);
			}

			if (InputManager::GetInstance()->m_Keys[GLFW_KEY_W])
			{
				GetTransform()->MoveY(-1);
			}

			if (InputManager::GetInstance()->m_Keys[GLFW_KEY_S])
			{
				GetTransform()->MoveY(1);
			}
		}	
	}

	void Player::Draw()
	{
		
	}
}
