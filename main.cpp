#include "App.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto& app = APP;
	if (!app.Init())
	{
		return -1;
	}
	app.Run();
	app.Terminate();
	return 0;				// �\�t�g�̏I�� 
}