#include "TitleScene.h"
#include "PlayScene.h"
#include "Input.h"
#include "SceneController.h"
#include "Camera.h"

void TitleScene::FadeinUpdate()
{
	if (--m_wait == 0)
	{
		m_updater = &TitleScene::NormalUpdate;
	}
	m_alphaVal -= 8.50f;
}

void TitleScene::NormalUpdate()
{
	if (m_input->IsDown(m_input->BUTTON_ID_RETURN))
	{
		m_updater = &TitleScene::FadeoutUpdate;
		m_wait = 90;
		m_alphaVal = 0;
	}
}

void TitleScene::FadeoutUpdate()
{
	if (--m_wait == 0)
	{
		// 仮でタイトルシーン
		m_controller->ChangeScene(std::make_unique<PlayScene>(*m_controller, *m_input));
	}
	m_alphaVal += 5.68f;
}

void TitleScene::FadeinDraw()
{
#ifdef _DEBUG
	printfDx("FadeinUpdate\n");
#endif // _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaVal);
	DrawBox(0, 0, game::SCREEN_WIDTH, game::SCREEN_HEIGHT, game::COLOR_BLACK, TRUE);
}

void TitleScene::NormalDraw()
{
#ifdef _DEBUG
	printfDx("NormalUpdate\n");
#endif // _DEBUG
}

void TitleScene::FadeoutDraw()
{
#ifdef _DEBUG
	printfDx("FadeoutUpdate\n");
#endif // _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaVal);
	DrawBox(0, 0, game::SCREEN_WIDTH, game::SCREEN_HEIGHT, game::COLOR_BLACK, TRUE);
}

TitleScene::TitleScene(SceneController& controller, Input& input)
	: Scene(controller, input)
{
	m_wait = 60;
	m_alphaVal = 255.0f;
#ifdef _DEBUG
	m_fpsDrawFlag = TRUE;
#endif // _DEBUG
	m_updater = &TitleScene::FadeinUpdate;
}

TitleScene::~TitleScene()
{
	if (!m_gameObject.empty())
	{
		m_gameObject.clear();
	}
}

void TitleScene::Update()
{
	m_input->Update();
	if (m_input->IsDown(m_input->BUTTON_ID_ESC))
	{
		m_controller->PopScene();
		return;
	}

#ifdef _DEBUG
	if (m_input->IsDown(m_input->BUTTON_ID_F))
	{
		m_fpsDrawFlag ^= TRUE;
	}
#endif // _DEBUG
	if (!m_gameObject.empty())
	{
		for (auto it = m_gameObject.begin(); it != m_gameObject.end(); it++)
		{
			it->get()->Update();
		}
	}
	

	(this->*m_updater)();
}

void TitleScene::Draw(float fps)
{
	// 画面クリア
	ClearDrawScreen();
	clsDx();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// フェードイン/フェードアウトにかかわらず描画
	DrawBox(0, 0, game::SCREEN_WIDTH, game::SCREEN_HEIGHT, game::COLOR_RED, TRUE);
#ifdef _DEBUG
	if (m_fpsDrawFlag) { printfDx("%.1fFPS <f>で非表示\n", fps); }
	printfDx("TitleScene\n");
#endif // _DEBUG
	if (!m_gameObject.empty())
	{
		for (auto it = m_gameObject.begin(); it != m_gameObject.end(); it++)
		{
			it->get()->Draw();
		}
	}
	

	// フェードイン/フェードアウト/通常を分けて表示
	if (m_updater == &TitleScene::FadeinUpdate)
	{
		FadeinDraw();
	}
	if (m_updater == &TitleScene::NormalUpdate)
	{
		NormalDraw();
	}
	if (m_updater == &TitleScene::FadeoutUpdate)
	{
		FadeoutDraw();
	}

	// フリップ
	ScreenFlip();
}
