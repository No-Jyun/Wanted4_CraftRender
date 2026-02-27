#include "Renderer.h"
#include "Core/Common.h"
#include "GraphicsContext.h"
#include <d3dcompiler.h>

namespace Craft
{
	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{
		// @Temp : 재사용하는 렌더 커멘드 해제
		auto& command = renderQueue[0];
		SafeRelease(command.vertexBuffer);
		SafeRelease(command.indexBuffer);
		SafeRelease(command.inputLayout);
		SafeRelease(command.vertexShader);
		SafeRelease(command.pixelShader);
	}

	void Renderer::Initialize()
	{
		// @Temp : 프레임워크 구성될 때까지 임시로 재사용할 리소스 생성

		// 리소스 생성할 장치
		auto& device = GraphicsContext::Get().GetDevice();

		// 정점 데이터 (3개의 점)
		float vertices[] =
		{
			0.0f, 0.5f, 0.1f,	// 첫번째 점의 위치 (3차원 좌표) x좌표, y좌표, 깊이
			0.5f, -0.5f, 0.1f,	// 두번째 점의 위치 (3차원 좌표)
			-0.5f, -0.5f, 0.1f,	// 세번째 점의 위치 (3차원 좌표)
		};

		/*
		UINT ByteWidth;
		D3D11_USAGE Usage;
		UINT BindFlags;
		UINT CPUAccessFlags;
		UINT MiscFlags;
		UINT StructureByteStride;
		*/
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = sizeof(float) * _countof(vertices);
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 서브 리소스 데이터 설정 (실제 데이터 할당)
		/*
		* // pSysMem에 설정된 데이터를 한 번에 전체 사용할 때는 아래 매개변수 2개는 0
		* // 도형 1개 그릴땐 밑에 2개 0으로 (필요없음)
			const void *pSysMem;
			UINT SysMemPitch;
			UINT SysMemSlicePitch;
		*/
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices;

		// 정점 버퍼 생성
		ID3D11Buffer* vertexBuffer = nullptr;
		HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 인덱스 (삼각형 조합할 때 사용할 순서를 지정)
		uint32_t indices[] = { 0,1,2 };

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(uint32_t) * _countof(indices);
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// 서브 리소스 데이터 설정 (실제 데이터 할당)
		/*
		* // pSysMem에 설정된 데이터를 한 번에 전체 사용할 때는 아래 매개변수 2개는 0
		* // 도형 1개 그릴땐 밑에 2개 0으로 (필요없음)
		    const void *pSysMem;
		    UINT SysMemPitch;
		    UINT SysMemSlicePitch;
		*/
		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = indices;

		// 인덱스 버퍼 생성
		ID3D11Buffer* indexBuffer = nullptr;
		result = device.CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 셰이더 컴파일
		
		// 셰이더 객체 생성

		// 입력 레이아웃 생성

		// 렌더 큐 추가
		RenderCommand command;
		command.vertexBuffer = vertexBuffer;
		command.indexBuffer = indexBuffer;
		command.indexCount = _countof(indices);
	}

	void Renderer::DrawScene()
	{

	}
}