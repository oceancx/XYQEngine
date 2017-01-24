#include "SpritesAnimation.h"
#include "../../Context.h"
#include "../../Helpers/Helpers.h"
#include "../../Logger.h"

namespace star
{
	SpritesAnimation::SpritesAnimation()
		: m_Name(EMPTY_STRING)
		, m_Speed(0)
		, m_CurrentFrame(0)
		, m_Repeat(0)
		, m_CurrentRepeats(0)
		, m_Callback(nullptr)
		, m_UserCallback(nullptr)
		, m_Frames()
		, m_IsPlaying(true)
	{
	}

	SpritesAnimation::SpritesAnimation(
		const tstring & name,  float32 speed,
		int32 repeat)
		: m_Name(name)
		, m_Speed(speed)
		, m_CurrentFrame(0)
		, m_Repeat(repeat)
		, m_CurrentRepeats(0)
		, m_Callback(nullptr)
		, m_UserCallback(nullptr)
		, m_Frames()
		, m_IsPlaying(true)
	{
		
	}

	SpritesAnimation::SpritesAnimation(const SpritesAnimation & yRef)
		: m_Name(yRef.m_Name)
		, m_Speed(yRef.m_Speed)
		, m_CurrentFrame(yRef.m_CurrentFrame)
		, m_Repeat(yRef.m_Repeat)
		, m_CurrentRepeats(yRef.m_CurrentRepeats)
		, m_Callback(yRef.m_Callback)
		, m_UserCallback(yRef.m_UserCallback)
		, m_Frames(yRef.m_Frames)
		, m_IsPlaying(yRef.m_IsPlaying)
	{
	}

	SpritesAnimation::SpritesAnimation(SpritesAnimation && yRef)
		: m_Name(yRef.m_Name)
		, m_Speed(yRef.m_Speed)
		, m_CurrentFrame(yRef.m_CurrentFrame)
		, m_Repeat(yRef.m_Repeat)
		, m_CurrentRepeats(yRef.m_CurrentRepeats)
		, m_Callback(yRef.m_Callback)
		, m_UserCallback(yRef.m_UserCallback)
		, m_Frames(yRef.m_Frames)
		, m_IsPlaying(yRef.m_IsPlaying)
	{
	}

	SpritesAnimation::~SpritesAnimation()
	{
		m_Frames.clear();
	}

	SpritesAnimation & SpritesAnimation::operator=(const SpritesAnimation & yRef)
	{
		m_Name = yRef.m_Name;
		m_Speed = yRef.m_Speed;
		m_CurrentFrame = yRef.m_CurrentFrame;
		m_Repeat = yRef.m_Repeat;
		m_CurrentRepeats = yRef.m_CurrentRepeats;
		m_Callback = yRef.m_Callback;
		m_UserCallback = yRef.m_UserCallback;
		m_Frames = yRef.m_Frames;
		m_IsPlaying = yRef.m_IsPlaying;

		return *this;
	}

	SpritesAnimation & SpritesAnimation::operator=(SpritesAnimation && yRef)
	{
		m_Name = yRef.m_Name;
		m_Speed = yRef.m_Speed;
		m_CurrentFrame = yRef.m_CurrentFrame;
		m_Repeat = yRef.m_Repeat;
		m_CurrentRepeats = yRef.m_CurrentRepeats;
		m_Callback = yRef.m_Callback;
		m_UserCallback = yRef.m_UserCallback;
		m_Frames = yRef.m_Frames;
		m_IsPlaying = yRef.m_IsPlaying;

		return *this;
	}

	void SpritesAnimation::Update(const Context & context)
	{
		if (m_IsPlaying)
		{
			m_CurrentFrame +=
				float32(context.time->DeltaTime().GetSeconds() * m_Speed);
			float32 size = float32(m_Frames.size());
			bool readyToGo(false);
			if (m_CurrentFrame >= size)
			{
				m_CurrentFrame = 0;
				readyToGo = true;
			}
			else if (m_CurrentFrame < 0)
			{
				m_CurrentFrame = size - 1;
				readyToGo = true;
			}
			if (readyToGo && m_Repeat != -1)
			{
				++m_CurrentRepeats;
				if (m_CurrentRepeats > m_Repeat)
				{
					m_CurrentRepeats = 0;
					m_CurrentFrame = size - 1;
					m_IsPlaying = false;
					if (m_Callback != nullptr)
					{
						m_Callback();
					}
					if (m_UserCallback != nullptr)
					{
						m_UserCallback();
					}
				}
			}
		}
	}

	vec4 SpritesAnimation::GetCurrentUV() const
	{
		vec4 uv;
		int32 currentFrame = int32(m_CurrentFrame);

		auto size = int32(m_Frames.size());
		if (currentFrame >= size)
		{
			currentFrame = size - 1;
		}
		else if (currentFrame < 0)
		{
			currentFrame = 0;
		}

		// UV Offset
		//uv.x = m_Frames[currentFrame].x;
		//uv.y = m_Frames[currentFrame].y;

		return uv;
	}

	void SpritesAnimation::Play()
	{
		m_IsPlaying = true;
	}

	void SpritesAnimation::PlayAtFrame(int32 startFrame)
	{
		m_IsPlaying = true;
		m_CurrentFrame = float32(startFrame);
	}

	void SpritesAnimation::Replay()
	{
		m_IsPlaying = true;
		m_CurrentFrame = 0;
	}

	void SpritesAnimation::Pause()
	{
		m_IsPlaying = false;
	}

	void SpritesAnimation::Stop()
	{
		m_IsPlaying = false;
		m_CurrentFrame = 0;
	}

	const tstring & SpritesAnimation::GetName() const
	{
		return m_Name;
	}

	bool SpritesAnimation::IsPlaying() const
	{
		return m_IsPlaying;
	}

	void SpritesAnimation::SetCallback(const std::function<void()> & callback)
	{
		m_Callback = callback;
	}

	void SpritesAnimation::SetUserCallback(const std::function<void()> & callback)
	{
		m_UserCallback = callback;
	}

	int32 SpritesAnimation::GetCurrentFrame() const
	{
		return int32(m_CurrentFrame);
	}
}
