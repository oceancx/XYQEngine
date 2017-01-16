#pragma once

#include "defines.h"
#include "Helpers/FPS.h"
#include <memory>

#include <random>


namespace star
{
	struct Context;

	class StarEngine final
	{
	public:
		~StarEngine();

		static StarEngine * GetInstance();
		void Initialize(int32 window_width, int32 window_height);

		void Update(const Context & context);
		void Draw();
		void End();

		void SetActive();
		void SetInactive();

		int32 GetCurrentFPS() const;
		int32 GetPreviousFPS() const;

		void SetGameTitle(const tstring & title);
		void SetGameSubTitle(const tstring & title);

		const tstring & GetGameTitle();

		bool HasTitleUpdated() const;
		void ResetTitleUpdateMark();

		std::mt19937& GetMt19937Engine();

		void Quit();


	private:
		static StarEngine * m_pEngine;
		FPS m_FPS;
		tstring m_Title, m_SubTitle;
		bool m_TitleHasUpdated;
		std::mt19937 m_RandomEngine;


		bool m_bInitialized;
		StarEngine();

		StarEngine(const StarEngine &);
		StarEngine(StarEngine &&);
		StarEngine & operator=(const StarEngine &);
		StarEngine & operator=(StarEngine &&);
	};
}
