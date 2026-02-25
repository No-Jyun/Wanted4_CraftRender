#pragma once

#include <Windows.h>
#include <string>
#include <stdint.h>

namespace Craft
{
	// WIN32 API 로 생성하는 창 클래스
	class Win32Window
	{
	public:
		Win32Window(
			uint32_t width = 1280,
			uint32_t height = 800,
			HINSTANCE instance = nullptr,
			WNDPROC messageProcedure = nullptr
		);
		~Win32Window();

		// 초기화 함수
		bool Initialize();

		// Getter
		inline uint32_t Width() const { return width; }
		inline uint32_t Height() const { return height; }
		inline HWND GetHandle() const { return handle; }

	private:
		// 타이틀
		std::wstring title;

		// 창 등록할 때 사용할 클래스 이름
		// 운영체제에 창 등록할 때 사용할 클래스 이름 - 유일해야함
		std::wstring className = L"Craft Engine Class";

		// 크기
		uint32_t width = 0;
		uint32_t height = 0;
		
		// 창 객체 (핸들)
		HWND handle = nullptr;

		// 프로그램 포인터 (인스턴스)
		HINSTANCE instance = nullptr;

		// 메시지 처리 함수 포인터
		WNDPROC messageProcedure = nullptr;
	};
}

