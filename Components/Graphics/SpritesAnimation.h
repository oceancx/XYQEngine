#pragma once

#include "../../defines.h"
#include <vector>
#include <functional>
#include "../../Components/Graphics/SpriteComponent.h"

/*
此类要保留
对动画播放进行控制
*/
namespace star
{
	struct Context;

	class SpritesAnimation final
	{
	public:
		SpritesAnimation();
		SpritesAnimation(const tstring & name, float32 speed, int32 repeat);
		SpritesAnimation(const SpritesAnimation &);
		SpritesAnimation(SpritesAnimation &&);
		~SpritesAnimation();

		SpritesAnimation & operator=(const SpritesAnimation &);
		SpritesAnimation & operator=(SpritesAnimation &&);

		void Update(const Context & context);
		vec4 GetCurrentUV() const;

		void Play();
		void PlayAtFrame(int32 startFrame);
		void Replay();
		void Pause();
		void Stop();

		const tstring & GetName() const;
		bool IsPlaying() const;

		void SetCallback(const std::function<void()> & callback);
		void SetUserCallback(const std::function<void()> & callback);

		int32 GetCurrentFrame() const;

	private:
		tstring m_Name;
		float32 m_Speed, m_CurrentFrame;
		int32 m_Repeat;
		int32 m_CurrentRepeats;

		std::function<void()> m_Callback;
		std::function<void()> m_UserCallback;

		//std::vector<vec2> m_Frames;
		
		std::vector<SpriteInfo> m_Frames;
		
		bool m_IsPlaying;
	};
}
