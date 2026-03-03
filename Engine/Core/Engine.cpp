#include "Engine.h"
#include "Win32Window.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"

namespace Craft
{
	Engine::Engine()
	{
	}
	
	Engine::~Engine()
	{
	}

	bool Engine::Initialize(HINSTANCE instance)
	{
		// 창 객체 생성
		window = std::make_unique<Win32Window>(
			setting.width,
			setting.height,
			setting.title,
			instance,
			Win32MessageProcedure
		);

		// 창 초기화
		if (!window->Initialize())
		{
			__debugbreak();
			return false;
		}

		// 컨텍스트 객체 생성
		grahicsContext = std::make_unique<GraphicsContext>();

		// 초기화 (unique ptr의 복사가 안되므로 역참조로 전달)
		grahicsContext->Initialize(*window);

		// 렌더러 생성
		renderer = std::make_unique<Renderer>();
		renderer->Initialize();

		return true;
	}

	void Engine::Run()
	{
		// 메시지 처리 루프
		// 창에서 발생하는 메시지 처리 루프 (게임 루프와 비슷함)
		// GetMessage - 동기 방식 (Blocking 방식)
		// PeekMessage - 비동기 방식 (Non Blocking 방식)
		// 동기 : 처리되기 전까지 다른 동작 안함
		// 비동기 : 처리되지 않아도 넘어감
		MSG msg = { };
		// 창 종료 메시지가 발생할 때까지 실행
		while (msg.message != WM_QUIT)
		{
			// 창 메시지 처리
			// 비동기 방식으로 메시지가 들어왔는지 확인
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				// 전달받은 메시지를 적절하게 변환
				TranslateMessage(&msg);

				// 변환한 메시지를 처리 함수에 전달
				DispatchMessage(&msg);
			}
			// 창 메시지가 없으면 엔진 로직 처리
			else
			{
				// 프레임 처리
				grahicsContext->BeginScene(0.6f, 0.7f, 0.8f);

				// 장면 그리기
				renderer->DrawScene();
				grahicsContext->EndScene(setting.vsync);
			}
		}
	}

	LRESULT Engine::Win32MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(handle, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(handle, &ps);
		}
		return 0;

		}
		return DefWindowProc(handle, message, wparam, lparam);
	}
}