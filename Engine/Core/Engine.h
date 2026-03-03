#pragma once

#include <memory>
#include <Windows.h>
#include <string>

namespace Craft 
{
	// 전방 선언
	class Win32Window;
	class GraphicsContext;

	// 엔진 설정
	struct EngineSetting
	{
		uint32_t width = 1280;
		uint32_t height = 800;
		std::wstring title = L"Craft Engine";
		float framerate = 120.0f;
		uint32_t vsync = 0;
	};

	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		// 초기화 함수
		bool Initialize(HINSTANCE instance);

		// 엔진 루프 실행 함수
		void Run();

	protected:
		// Win32 윈도우 메시지 처리 함수 (콜백 함수)
		static LRESULT CALLBACK Win32MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam);

	protected:
		// 창 객체
		std::unique_ptr<Win32Window> window;

		// 그래픽스 컨텍스트 객체 (장치 관리 등등)
		std::unique_ptr<GraphicsContext> grahicsContext;

		// 렌더러 객체 (장면 그리기 담당)
		std::unique_ptr<class Renderer> renderer;

		// 엔진 설정 변수
		EngineSetting setting;
	};
}

