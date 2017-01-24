#pragma once
#include "Object.h"

namespace star 
{

	class Player :public Object
	{
	public:
		/*Player();
		~Player();*/

		Player();
		explicit Player(const tstring & name);
		Player(
			const tstring & name,
			const tstring & groupTag
		) ;
		~Player();
	protected:
		void Update(const Context & context);
		void Draw();
	private:

	};

}
