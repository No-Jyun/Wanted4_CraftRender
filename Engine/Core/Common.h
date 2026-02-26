#pragma once


// D3D 쪽의 리소스 해제할 때 사용할 함수
template<typename T>
void SafeRelease(T*& resource)
{
	if (resource)
	{
		resource->Release();
		resource = nullptr;
	}
}