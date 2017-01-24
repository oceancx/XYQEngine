#pragma once

#include "../Helpers/Singleton.h"

#include "../defines.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace star
{
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		friend Singleton<InputManager>;

		/*公有变量*/
		GLboolean              m_Keys[1024] = {0};
		double                 m_MousePos[2] = {0};
	private:
		InputManager();
		~InputManager();
		InputManager(const InputManager& t);
		InputManager(InputManager&& t);
	 	InputManager& operator=(const InputManager& t);
		InputManager& operator=(InputManager&& t);

	};

}
