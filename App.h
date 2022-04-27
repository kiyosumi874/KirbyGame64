#pragma once
#include "DxLib.h"
class App
{
private:
	// ���V���O���g���̂��߂ɃR���X�g���N�^��private��
	// ����ɃR�s�[�Ƒ�����֎~��
	App() {}
	App(const App&) = delete;
	void operator=(const App&) = delete;
public:
	// Application�̃V���O���g���C���X�^���X�𓾂�
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