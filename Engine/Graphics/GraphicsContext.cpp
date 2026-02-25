#include "GraphicsContext.h"
#include "../Core/Win32Window.h"

namespace Craft
{
	GraphicsContext::GraphicsContext()
	{
	}

	GraphicsContext::~GraphicsContext()
	{
		// 자원 해제
		if (device)
		{
			// Release 함수를 통해서 자원 해제
			device->Release();
			device = nullptr;
		}

		if (context)
		{
			context->Release();
			context = nullptr;
		}

		if (swapChain)
		{
			swapChain->Release();
			swapChain = nullptr;
		}
	}

	void GraphicsContext::Initialize(uint32_t width, uint32_t height, const Win32Window& window)
	{
		// 플래그 지정
		uint32_t flag = 0;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// Direct3D API 버전 정보
		// 그래픽 카드가 지원하는지 확인하는 용도
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		// 장치 생성
		// Device / DeviceContext 생성
		/*
		* _In_opt_ IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE DriverType,
			HMODULE Software,
			UINT Flags,
			CONST D3D_FEATURE_LEVEL* pFeatureLevels,
			UINT FeatureLevels,
			UINT SDKVersion,
			ID3D11Device** ppDevice,
			D3D_FEATURE_LEVEL* pFeatureLevel,
			ID3D11DeviceContext** ppImmediateContext
		*/
		// 오류인 경우 음수값 반환됨
		HRESULT result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			&context
		);

		// 예외처리
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// SwapChain 생성
		// 스왑체인 생성해주는 객체 얻어오기
		IDXGIFactory* factory = nullptr;
		result = CreateDXGIFactory(
			__uuidof(IDXGIFactory),
			reinterpret_cast<void**>(&factory)
		);

		// 예외 처리
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 스왑체인 생성을 위한 자료 설정
		/*
		*   DXGI_MODE_DESC BufferDesc;
			DXGI_SAMPLE_DESC SampleDesc;
			DXGI_USAGE BufferUsage;
			UINT BufferCount;
			HWND OutputWindow;
			BOOL Windowed;
			DXGI_SWAP_EFFECT SwapEffect;
			UINT Flags;
		*/
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.Windowed = true;	// 창 모드로 시작
		swapChainDesc.OutputWindow = window.Handle();
		// 화면 출력용
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// 사용할 버퍼 수
		swapChainDesc.BufferCount = 2;

		// 안티-안리아싱 (Anti-Aliasing) 에 수퍼샘플링 수준 설정
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		// 버퍼 (프레임-이미지) 설정
		swapChainDesc.BufferDesc.Width = window.Width();
		swapChainDesc.BufferDesc.Height = window.Height();
		// 이미지 픽셀 포멧 (32비트-부호없고-정규화된 포멧)
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// 버퍼 교환 효과 설정
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// 스왑 체인 생성
		result = factory->CreateSwapChain(
			device,
			&swapChainDesc,
			&swapChain
		);

		// 예외 처리
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 팩토리 객체 해제
		if (factory)
		{
			factory->Release();
			factory = nullptr;
		}
		
		// 뷰포트 생성
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(window.Width());
		viewport.Height = static_cast<float>(window.Height());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
	}
}