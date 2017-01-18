#include "../defines.h"
#include "../Objects/Object.h"
//#include "../Input/Gestures/GestureManager.h"

namespace star
{
	template <typename T>
	T * BaseScene::GetObjectByName(const tstring & name) const
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareName(name))
			{
				auto pReturnObject = dynamic_cast<T*>(pObject);
				if(pReturnObject == nullptr)
				{
					LOG(LogLevel::Error,
						_TT("BaseScene::GetObjectByName: couldn't convert object '")
						+ name + _TT("' to the requested type. Returning nullptr..."),
						STARENGINE_LOG_TAG);
				}
				return pReturnObject;
			}
		}
		LOG(LogLevel::Warning,
			_TT("BaseScene::GetObjectByName: Trying to get an unknown object '")
			+ name + _TT("'."), STARENGINE_LOG_TAG);
		return nullptr;
	}

	template <typename T>
	T * BaseScene::GetGestureByName(const tstring & name) const
	{
		//return m_pGestureManager->GetGesture<T>(name);
		return nullptr;
	}
}
