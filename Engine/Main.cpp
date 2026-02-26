#include "Core/Engine.h"

using namespace Craft;

// 엔진 실행 함수
void LaunchEngineStartup(HINSTANCE instance)
{
	Engine engine;
	engine.Initialize(instance);
	engine.Run();
}

int main()
{
	LaunchEngineStartup(GetModuleHandle(nullptr));
}

//#ifdef _WIN64
//int WINAPI WinMain(
//    _In_ HINSTANCE hInstance,
//    _In_opt_ HINSTANCE hPrevInstance,
//    _In_ LPSTR lpCmdLine,
//    _In_ int nShowCmd)
//{
//    LaunchEngineStartup(hInstance);
//
//    return 0;
//}
//#else
//int main()
//{
//	LaunchEngineStartup(GetModuleHandle(nullptr));
//}
//#endif