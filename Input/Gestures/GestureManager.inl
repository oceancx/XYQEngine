#include "GestureManager.h"
#include "../../Logger.h"

namespace star
{
	template <typename T>
	T * GestureManager::GetGesture(const tstring & name) const
	{
		auto it = m_GestureMap.find(name);
		
		ASSERT_LOG(it != m_GestureMap.end(),
			_TT("GestureManager::GetGesture(const tstring& tag): Gesture \"") + 
			name +
			tstring(_TT("\" not found!")),
			STARENGINE_LOG_TAG
			);

		auto returnObject = dynamic_cast<T*>((*it).second);
		if(returnObject == nullptr)
		{
			LOG(LogLevel::Error,
				_TT("BaseScene::GetGestureByName: couldn't convert object '")
				+ name + _TT("' to the requested type. Returning nullptr..."),
				STARENGINE_LOG_TAG);
		}
		return returnObject;
	}
}