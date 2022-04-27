#include "App.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto& app = APP;
	if (!app.Init())
	{
		return -1;
	}
	app.Run();
	app.Terminate();
	return 0;				// ソフトの終了 
}