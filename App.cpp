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
	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
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

	// ���C�����[�v�ɓ���O�ɐ��x���擾���Ă���
	if (QueryPerformanceFrequency(&timeFreq) == FALSE)
	{ 
		return;
	}

	// 1�x�擾���Ă���(����v�Z�p)
	QueryPerformanceCounter(&timeStart);

	// �Q�[�����[�v
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

		// ���̎��Ԃ��擾
		QueryPerformanceCounter(&timeEnd);
		// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
		frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

		if (frameTime < game::MIN_FRAME_TIME) { // ���Ԃɗ]�T������
			// �~���b�ɕϊ�
			DWORD sleepTime = static_cast<DWORD>((game::MIN_FRAME_TIME - frameTime) * 1000);

			timeBeginPeriod(1); // ����\���グ��(�������Ȃ���Sleep�̐��x�̓K�^�K�^)
			Sleep(sleepTime);   // �Q��
			timeEndPeriod(1);   // �߂�

			// ���T�Ɏ����z��(�������Ȃ���fps���ςɂȂ�?)
			continue;
		}

		if (frameTime > 0.0)
		{ // �o�ߎ��Ԃ�0���傫��(�������Ȃ��Ɖ��̌v�Z�Ń[�����Z�ɂȂ�Ǝv���)
			fps = (fps * 0.99f) + (0.01f / frameTime); // ����fps���v�Z
#ifdef _DEBUG
// �f�o�b�O�p(�f�o�b�K��FSP�o��)
#ifdef UNICODE
			std::wstringstream stream;
#else
			std::stringstream stream;
#endif
			stream << fps << " FPS" << std::endl;
			// �J�E���^�t����10���1��o�́A�Ƃ��ɂ��Ȃ��ƌ��Â炢������
			OutputDebugString(stream.str().c_str());
#endif // _DEBUG
		}

		timeStart = timeEnd; // ����ւ�
	}
}

void App::Terminate()
{
	// Effekseer���I������B
	Effkseer_End();
	DxLib_End();
}
