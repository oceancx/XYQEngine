#pragma once

#include "../defines.h"
#include "../Helpers/Singleton.h"

//#include <Windows.h>
#define GLEW_STATIC
#include <GL\glew.h>


namespace star
{
	class GraphicsManager final : public Singleton<GraphicsManager>
	{
	public:
		friend Singleton<GraphicsManager>;

		void Initialize(int32 screenWidth, int32 screenHeight);


		void StartDraw();
		void StopDraw();
		void Update();

		int32 GetWindowWidth() const;
		int32 GetWindowHeight() const;

		int32 GetViewportWidth() const;
		int32 GetViewportHeight() const;

		int32 GetScreenWidth() const;
		int32 GetScreenHeight() const;

		const mat4& GetViewInverseProjectionMatrix() const;
		const mat4& GetViewMatrix() const;
		const mat4& GetViewInverseMatrix() const;
		const mat4& GetProjectionMatrix() const;

		float32 GetWindowAspectRatio() const;

		const vec2 & GetWindowResolution() const;
		const vec2 & GetViewportResolution() const;
		const vec2 & GetScreenResolution() const;

		float32 GetViewportAspectRatio() const;

		int32 GetHorizontalViewportOffset() const;
		int32 GetVerticalViewportOffset() const;

		void SetWindowDimensions(int32 width, int32 height);
		void SetHasWindowChanged(bool isTrue);
		bool GetHasWindowChanged() const;
		void CalculateViewPort();

		void SetVSync(bool VSync);
		bool GetVSync() const;

	private:
		GraphicsManager();
		~GraphicsManager();

		void InitializeOpenGLStates();

	
		bool InitializeOpenGLFunctors();

		int32 mHorizontalViewportOffset,
			mVerticalViewportOffset;

		mat4 mViewProjectionMatrix;
		mat4 mViewMatrix;
		mat4 mViewInverseMatrix;
		mat4 mProjectionMatrix;
		vec2 mScreenResolution, mViewportResolution;
		bool mbHasWindowChanged;
		bool mIsInitialized;


		GraphicsManager(const GraphicsManager& yRef);
		GraphicsManager(GraphicsManager&& yRef);
		GraphicsManager& operator=(const GraphicsManager& yRef);
		GraphicsManager& operator=(GraphicsManager&& yRef);
	};
}
