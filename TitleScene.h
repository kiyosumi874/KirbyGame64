#pragma once
#include "Scene.h"
#include <memory>

class Input;
class TitleScene final : public Scene
{
private:
	int m_wait;
	float m_alphaVal;
#ifdef _DEBUG
	bool m_fpsDrawFlag;
#endif // _DEBUG

	void (TitleScene::* m_updater)();
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();

	void FadeinDraw();
	void NormalDraw();
	void FadeoutDraw();

public:
	TitleScene(SceneController& controller, Input& input);
	~TitleScene();
	void Update() override;
	void Draw(float fps) override;
};