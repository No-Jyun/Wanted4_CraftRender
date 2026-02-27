#pragma once

#include <vector>
#include <d3d11.h>

namespace Craft
{
	// 렌더 명령 (Render Command)
	struct RenderCommand
	{
		// 정점 (Vertex) 버퍼 (Buffer - 메모리 덩어리)
		ID3D11Buffer* vertexBuffer = nullptr;
		// 색인 (인덱스 - Index) 버퍼 (옵션)
		ID3D11Buffer* indexBuffer = nullptr;
		// 입력 (정점 데이터) 의 생김새 (GL : VertexBufferObject)
		ID3D11InputLayout* inputLayout = nullptr;

		// 필수 셰이더 (VS / PS) (없으면 화면 안나옴)
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;

		// 인덱스 개수 (indexCount)
		// vertexBuffer 와 연결된 색인을 어디까지 그릴지 지정
		uint32_t indexCount = 0;
	};

	// DrawCall 담당
	// RHI - Render Hardware Interface : 그래픽 카드
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		// 초기화
		void Initialize();

		// DrawCall 발생 처리
		// -> 렌더링 파이프라인 실행(구동)
		void DrawScene();

	private:
		// 렌더 큐(Queue)
		std::vector<RenderCommand> renderQueue;

	};
}
