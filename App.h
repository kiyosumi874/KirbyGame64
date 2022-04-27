#pragma once
#include "DxLib.h"
class App
{
private:
	// ↓シングルトンのためにコンストラクタをprivateに
	// さらにコピーと代入を禁止に
	App() {}
	App(const App&) = delete;
	void operator=(const App&) = delete;
public:
	// Applicationのシングルトンインスタンスを得る
	static App& GetInstance()
	{
		static App instance;
		return instance;
	}

	bool Init();

	void Run();

	void Terminate();
};

#define APP App::GetInstance()