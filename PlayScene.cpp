#include "PlayScene.h"
#include "ResultScene.h"
#include "Input.h"
#include "SceneController.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "ShotDirector.h"
#include <memory>

void PlayScene::FadeinUpdate()
{
	if (--m_wait == 0)
	{
		m_updater = &PlayScene::NormalUpdate;
	}
	m_alphaVal -= 8.50f;

}

void PlayScene::NormalUpdate()
{
	if (m_input->IsDown(m_input->BUTTON_ID_RETURN))
	{
		m_updater = &PlayScene::FadeoutUpdate;
		m_wait = 90;
		m_alphaVal = 0;
	}

}

void PlayScene::FadeoutUpdate()
{
	if (--m_wait == 0)
	{
		// 仮でタイトルシーン
		m_controller->ChangeScene(std::make_unique<ResultScene>(*m_controller, *m_input));
	}
	m_alphaVal += 5.68f;
}

void PlayScene::FadeinDraw()
{
#ifdef _DEBUG
	printfDx("FadeinUpdate\n");
#endif // _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaVal);
	DrawBox(0, 0, game::SCREEN_WIDTH, game::SCREEN_HEIGHT, game::COLOR_BLACK, TRUE);
}

void PlayScene::NormalDraw()
{
#ifdef _DEBUG
	printfDx("NormalUpdate\n");
#endif // _DEBUG
}

void PlayScene::FadeoutDraw()
{
#ifdef _DEBUG
	printfDx("FadeoutUpdate\n");
#endif // _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaVal);
	DrawBox(0, 0, game::SCREEN_WIDTH, game::SCREEN_HEIGHT, game::COLOR_BLACK, TRUE);
}

PlayScene::PlayScene(SceneController& controller, Input& input)
	: Scene(controller, input)
{
	m_wait = 60;
	m_alphaVal = 255.0f;
#ifdef _DEBUG
	m_fpsDrawFlag = TRUE;
#endif // _DEBUG
	m_updater = &PlayScene::FadeinUpdate;
	m_gameObject.emplace_back(std::make_unique<Camera>(VGet(274, 471, -243), VGet(0.74f, 0.0f, 0.0f), 1, 1000, *m_input));
	m_gameObject.emplace_back(std::make_unique<Map>(VGet(60, 0, 60), VGet(60, 60, 60)));
	m_gameObject.emplace_back(std::make_unique<Player>(VGet(0, 0, 0), *m_input));
	m_gameObject.emplace_back(std::make_unique<ShotDirector>());

}

PlayScene::~PlayScene()
{
	if (!m_gameObject.empty())
	{
		m_gameObject.clear();
	}
}

void PlayScene::Update()
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
	auto inst = m_gameObject[3].get();
	auto shotDirector = dynamic_cast<ShotDirector*>(inst);
	inst = m_gameObject[1].get();
	auto map = dynamic_cast<Map*>(inst);
	inst = m_gameObject[2].get();
	auto player = dynamic_cast<Player*>(inst);
	shotDirector->SetShotTransformVec(player->GetTag(), player->GetShotVec());
	shotDirector->SetMapTransformVec(map->GetBoxColliderVec(), map->GetAliveFlagVec());
	if (!m_gameObject.empty())
	{
		for (auto it = m_gameObject.begin(); it != m_gameObject.end(); it++)
		{
			it->get()->Update();
		}
	}
	shotDirector->SetCountVec(map->GetCountVec());
	shotDirector->AdjustmentFlag();
	map->SetCountVec(shotDirector->GetCountVec());
	map->SetAliveFlagVec(shotDirector->GetAliveFlagVec());
	shotDirector->SetPlayer1Transform(player->GetTransform());
	(this->*m_updater)();

}

void PlayScene::Draw(float fps)
{
	// 画面クリア
	ClearDrawScreen();
	clsDx();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// フェードイン/フェードアウトにかかわらず描画
	DrawBox(0, 0, game::SCREEN_WIDTH, game::SCREEN_HEIGHT, game::COLOR_GREEN, TRUE);
#ifdef _DEBUG
	if (m_fpsDrawFlag) { printfDx("%.1fFPS <f>で非表示\n", fps); }
	printfDx("PlayScene\n");
#endif // _DEBUG
	if (!m_gameObject.empty())
	{
		for (auto it = m_gameObject.begin(); it != m_gameObject.end(); it++)
		{
			it->get()->Draw();
		}
	}
	// フェードイン/フェードアウト/通常を分けて表示
	if (m_updater == &PlayScene::FadeinUpdate)
	{
		FadeinDraw();
	}
	if (m_updater == &PlayScene::NormalUpdate)
	{
		NormalDraw();
	}
	if (m_updater == &PlayScene::FadeoutUpdate)
	{
		FadeoutDraw();
	}

	// フリップ
	ScreenFlip();
}
