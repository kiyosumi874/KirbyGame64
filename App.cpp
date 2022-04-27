#include "App.h"
#include "SceneController.h"
#include "Input.h"
#include "Definition.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include <sstream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")



bool App::Init()
{
	SetMainWindowText("Game");
	SetGraphMode(game::SCREEN_WIDTH, game::SCREEN_HEIGHT, 32);
	ChangeWindowMode(TRUE);
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);
	return true;
}

void App::Run()
{
	auto input = std::make_unique<Input>();
	auto sceneCon = std::make_unique<SceneController>(*input.get());
	float frameTime = 0;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;
	float fps = 0;

	// メインループに入る前に精度を取得しておく
	if (QueryPerformanceFrequency(&timeFreq) == FALSE)
	{ 
		return;
	}

	// 1度取得しておく(初回計算用)
	QueryPerformanceCounter(&timeStart);

	// ゲームループ
	while (true)
	{
		if (ProcessMessage() == -1)
		{
			break;
		}

		if (!sceneCon->SceneUpdate(fps))
		{
			break;
		}

		// 今の時間を取得
		QueryPerformanceCounter(&timeEnd);
		// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
		frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

		if (frameTime < game::MIN_FRAME_TIME) { // 時間に余裕がある
			// ミリ秒に変換
			DWORD sleepTime = static_cast<DWORD>((game::MIN_FRAME_TIME - frameTime) * 1000);

			timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度はガタガタ)
			Sleep(sleepTime);   // 寝る
			timeEndPeriod(1);   // 戻す

			// 次週に持ち越し(こうしないとfpsが変になる?)
			continue;
		}

		if (frameTime > 0.0)
		{ // 経過時間が0より大きい(こうしないと下の計算でゼロ除算になると思われ)
			fps = (fps * 0.99f) + (0.01f / frameTime); // 平均fpsを計算
#ifdef _DEBUG
// デバッグ用(デバッガにFSP出す)
#ifdef UNICODE
			std::wstringstream stream;
#else
			std::stringstream stream;
#endif
			stream << fps << " FPS" << std::endl;
			// カウンタ付けて10回に1回出力、とかにしないと見づらいかもね
			OutputDebugString(stream.str().c_str());
#endif // _DEBUG
		}

		timeStart = timeEnd; // 入れ替え
	}
}

void App::Terminate()
{
	// Effekseerを終了する。
	Effkseer_End();
	DxLib_End();
}
