#pragma once

#include <d3d11.h>		// Direct3D 11 일반적인 내용
#include <dxgi.h>		// DXGI 장치 관련 (스왑체인)
#include <string>

// 장치 (= 그래픽 카드)
// Direct3D 에서 "장치"로 다루는 객체는 3개
// Device : 리소스 생성 전담
// DeviceContext : 생성된 리소스를 그래픽 카드에 할당 (바인딩) / 드로우콜
// SwapChain (스왑 체인) : 백버퍼-프론트버퍼 교환
// RenderTargetView (렌터 타겟 뷰) : 화면에 그릴 프레임 (이미지) 리소스
// View (뷰) : 특별한 리소스. CPU <-> GPU 간의 소통을 위해 사용
// -> CPU 에서 리소스를 생성하면 이걸 본따서 GPU 에서 복제본을 만들고 사용함
// 포워드 렌더러 (Forward Renderer) -> 우리는 이걸
// 디퍼드 렌더러 (Deferred Renderer) 

namespace Craft
{
	// 전방선언
	class Win32Window;

	// 그래픽스 관련 기능을 제공 및 리소스 관리
	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		// 초기화
		void Initialize(const Win32Window& window);

		// 프레임 준비 함수
		void BeginScene(float red, float green, float blue);

		// 나중에 Renderer에서 DrawScene(또는 DrawFrame) 함수가 호출될 예정

		// 완성된 프레임을 모니터에 보내는 (체인 변경) 함수
		// vsync가 0이면 수직 동기화 안함. 1이면 모니터 수직 동기화 사용
		void EndScene(uint32_t vsync);

	private:
		// 장치 생성
		void CreateDevice();
		void CreateSwapChain(const Win32Window& window);
		void CreateViewport(const Win32Window& window);

		// 렌더 타겟 뷰 생성
		void CreateRenderTargetView();

	private:
		// 장치류
		// Direct3D 리소스는 포인터로만 다룰 수 있음
		// 생성/해제를 API에 요청
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swapChain = nullptr;

		// 리소스
		// RTV - 그리기 대상 리소스
		ID3D11RenderTargetView* renderTargetView = nullptr;

		// 뷰포트
		D3D11_VIEWPORT viewport = {};

		// 화면 크기
		uint32_t width = 0;
		uint32_t height = 0;
	};
}
