#include "GraphicsManager.h"
#include "SpriteBatch.h"
#include "ScaleSystem.h"
#include "../Logger.h"
#include "../defines.h"
#include "../Scenes/SceneManager.h"
#include "../Objects/BaseCamera.h"
#include "../Scenes/BaseScene.h"
#include "../Components/CameraComponent.h"
//
//#ifdef DESKTOP
////#include <wglext.h>
//#endif
//
//#ifdef MOBILE
//#include <GLES/gl.h>
//#endif

namespace star
{
	GraphicsManager::GraphicsManager()
		: Singleton<GraphicsManager>()
		, mHorizontalViewportOffset(0)
		, mVerticalViewportOffset(0)
		, mViewProjectionMatrix()
		, mViewInverseMatrix()
		, mProjectionMatrix()
		, mScreenResolution(0, 0)
		, mViewportResolution(0, 0)
		, mbHasWindowChanged(false)
		, mIsInitialized(false)
		//#ifdef DESKTOP
		//		, mWglSwapIntervalEXT(NULL)
		//		, mWglGetSwapIntervalEXT(NULL)
		//#else
		//		, mDisplay()
		//		, mSurface()
		//		, mContext()
		//#endif
	{
		LOG(star::LogLevel::Info,
			_TT("Graphics Manager : Constructor"), STARENGINE_LOG_TAG);
	}

	GraphicsManager::~GraphicsManager()
	{
		LOG(star::LogLevel::Info,
			_TT("Graphics Manager : Destructor"), STARENGINE_LOG_TAG);
	}

	void GraphicsManager::CalculateViewPort()
	{
		vec2 screenRes = GetWindowResolution();
		vec2 workingRes = ScaleSystem::GetInstance()->GetWorkingResolution();

		float32 width = screenRes.x / workingRes.x;
		float32 height = screenRes.y / workingRes.y;

		mHorizontalViewportOffset = 0;
		mVerticalViewportOffset = 0;
		float32 aspectRatio(0);

		if (width > height)
		{
			height = screenRes.y;
			aspectRatio = (workingRes.x / workingRes.y);
			width = height * aspectRatio;

			mHorizontalViewportOffset = static_cast<int32>((screenRes.x - width) / 2);
		}
		else
		{
			width = screenRes.x;
			aspectRatio = (workingRes.y / workingRes.x);
			height = width * aspectRatio;

			mVerticalViewportOffset = static_cast<int32>((screenRes.y - height) / 2);
		}

		glViewport(mHorizontalViewportOffset, mVerticalViewportOffset, static_cast<int32>(width), static_cast<int32>(height));

		mViewportResolution.x = width;
		mViewportResolution.y = height;



		ScaleSystem::GetInstance()->CalculateScale();
	}

	void GraphicsManager::SetVSync(bool vSync)
	{
		//#ifdef DESKTOP
		//		//Enables or disables VSync.
		//		//0 = No Sync , 1+ = VSync
		//		//Default value is 1.
		//		if(!vSync)
		//		{
		//			mWglSwapIntervalEXT(0);
		//		}
		//		else
		//		{
		//			mWglSwapIntervalEXT(1);
		//		}
		//	#else
		//		LOG(LogLevel::Warning, 
		//			_TT("Setting VSync on mobile is not supported. Default VSync is enabled"),
		//			STARENGINE_LOG_TAG);
		//#endif
	}

	bool GraphicsManager::GetVSync() const
	{
		//#ifdef DESKTOP
		//		return !(mWglGetSwapIntervalEXT() == 0);
		//#else
		//		LOG(LogLevel::Warning, 
		//			_TT("Toggeling VSync on mobile is not supported. Default VSync is enabled"),
		//			STARENGINE_LOG_TAG);
		return true;
		//#endif
	}

	void GraphicsManager::Initialize(int32 screenWidth, int32 screenHeight)
	{
		if (!mIsInitialized)
		{
			mScreenResolution.x = float32(screenWidth);
			mScreenResolution.y = float32(screenHeight);
			//glewInit();

			//LOG(star::LogLevel::Info,
			//	_TT("Graphics Manager : Initializing OpenGL Functors"),
			//	STARENGINE_LOG_TAG);
			//if (!InitializeOpenGLFunctors())
			//{
			//	LOG(star::LogLevel::Error,
			//		_TT("Graphics Manager : Graphics card doesn't support VSync option!!"),
			//		STARENGINE_LOG_TAG);
			//}

			//SetVSync(true);

			////Initializes base GL state.
			////DEPTH_TEST is default disabled
			//InitializeOpenGLStates();
			mIsInitialized = true;
		}
	}

	void GraphicsManager::InitializeOpenGLStates()
	{
		//glDisable(GL_DEPTH_TEST);
	//	glClearColor(0.f, 0.f, 0.f, 1.0f);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_BLEND);
	}

	void GraphicsManager::StartDraw()
	{
	//	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	}

	void GraphicsManager::StopDraw()
	{

	}

	void GraphicsManager::Update()
	{
		if (SceneManager::GetInstance()->GetActiveScene())
		{
			auto projectionObject(SceneManager::GetInstance()->GetActiveScene()->GetActiveCamera());
			if (projectionObject)
			{
				const mat4& projection = projectionObject->GetComponent<CameraComponent>()
					->GetProjection();
				const mat4& view = projectionObject->GetComponent<CameraComponent>()
					->GetView();
				const mat4& viewInverse = projectionObject->GetComponent<CameraComponent>()
					->GetViewInverse();
				mProjectionMatrix = projection;
				mViewMatrix = view;
				mViewInverseMatrix = viewInverse;
				mViewProjectionMatrix = projection * viewInverse;
			}
		}
	}

	int32 GraphicsManager::GetWindowWidth() const
	{
		return int32(mScreenResolution.x);
	}

	int32 GraphicsManager::GetWindowHeight() const
	{
		return int32(mScreenResolution.y);
	}

	int32 GraphicsManager::GetViewportWidth() const
	{
		return int32(mViewportResolution.x);
	}

	int32 GraphicsManager::GetViewportHeight() const
	{
		return int32(mViewportResolution.y);
	}

	int32 GraphicsManager::GetScreenWidth() const
	{
		return int32(ScaleSystem::GetInstance()->GetWorkingResolution().x);
	}

	int32 GraphicsManager::GetScreenHeight() const
	{
		return int32(ScaleSystem::GetInstance()->GetWorkingResolution().y);
	}

	const mat4& GraphicsManager::GetViewInverseProjectionMatrix() const
	{
		return mViewProjectionMatrix;
	}

	const mat4& GraphicsManager::GetProjectionMatrix() const
	{
		return mProjectionMatrix;
	}

	const mat4& GraphicsManager::GetViewMatrix() const
	{
		return mViewMatrix;
	}

	const mat4& GraphicsManager::GetViewInverseMatrix() const
	{
		return mViewInverseMatrix;
	}

	float32 GraphicsManager::GetWindowAspectRatio() const
	{
		return mScreenResolution.x / mScreenResolution.y;
	}

	const vec2 & GraphicsManager::GetWindowResolution() const
	{
		return mScreenResolution;
	}

	const vec2 & GraphicsManager::GetViewportResolution() const
	{
		return mViewportResolution;
	}

	const vec2 & GraphicsManager::GetScreenResolution() const
	{
		return ScaleSystem::GetInstance()->GetWorkingResolution();
	}

	float32 GraphicsManager::GetViewportAspectRatio() const
	{
		return mViewportResolution.x / mViewportResolution.y;
	}

	int32 GraphicsManager::GetHorizontalViewportOffset() const
	{
		return mHorizontalViewportOffset;
	}

	int32 GraphicsManager::GetVerticalViewportOffset() const
	{
		return mVerticalViewportOffset;
	}

	void GraphicsManager::SetWindowDimensions(int32 width, int32 height)
	{
		mScreenResolution.x = float32(width);
		mScreenResolution.y = float32(height);
		CalculateViewPort();
	}

	void GraphicsManager::SetHasWindowChanged(bool isTrue)
	{
		mbHasWindowChanged = isTrue;
		if (isTrue)
		{
			CalculateViewPort();
		}
	}

	bool GraphicsManager::GetHasWindowChanged() const
	{
		return mbHasWindowChanged;
	}

}