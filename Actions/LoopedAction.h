#pragma once

#include "Action.h"
#include <functional>

namespace star
{
	class Object;

	class LoopedAction : public Action
	{
	public:
		LoopedAction(float32 seconds);
		LoopedAction(
			const tstring & name,
			float32 seconds
			);

		virtual ~LoopedAction();

		virtual void Initialize();

		virtual void Restart();
		virtual void Pause();
		virtual void Resume();

	protected:
		std::function<void()> m_Callback;
		float32 m_Seconds;

	private:
		static uint64 ID_COUNTER;
		tstring m_UniqueID;

		LoopedAction & operator=(const LoopedAction&);
		LoopedAction & operator=(LoopedAction&&);
		LoopedAction(const LoopedAction&);
		LoopedAction(LoopedAction&&);
	};
}
