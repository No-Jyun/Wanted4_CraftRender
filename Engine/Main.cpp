#include "Core/Win32Window.h"
#include "Graphics/GraphicsContext.h"

// 콜백 함수
// 창 메시지 처리할 때 사용
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main()
{
    // 그래픽스 프로그래밍
    // 창 (Window) 을 생성하고, API를 활용해서 창에 그림을 그리는 프로그램
    // Win32 API 활용 (창을 만드는 API)
    
    std::wstring className = L"Craft Engine Window";
    std::wstring title = L"Craft Engine";
    
    // 클라이언트 영역 창 크기
    uint32_t width = 1280;
    uint32_t height = 800;
    
    // null값을 전달하면 현재 프로그램의 포인터를 반환해줌
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // 창 생성
    Craft::Win32Window window(width, height, title, hInstance, WindowProc);

    // 초기화 (초기화 실패 시 프로그램 종료)
    if (!window.Initialize())
    {
        return -1;
    }

    // 장치 생성 테스트
    Craft::GraphicsContext context;
    context.Initialize(window);

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
            
        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
