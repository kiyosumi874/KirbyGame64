#pragma once
#include "Scene.h"
#include <memory>

class Input;
class PlayScene final : public Scene
{
private:
	int m_wait;
	float m_alphaVal;
#ifdef _DEBUG
	bool m_fpsDrawFlag;
#endif // _DEBUG

	void (PlayScene::* m_updater)();
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();

	void FadeinDraw();
	void NormalDraw();
	void FadeoutDraw();
public:
	PlayScene(SceneController& controller, Input& input);
	~PlayScene();
	void Update() override;
	void Draw(float fps) override;
};