#pragma once
#include "Scene.h"
#include <memory>

class Input;
class ResultScene final : public Scene
{
private:
	int m_wait;
	float m_alphaVal;
#ifdef _DEBUG
	bool m_fpsDrawFlag;
#endif // _DEBUG

	void (ResultScene::* m_updater)();
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();

	void FadeinDraw();
	void NormalDraw();
	void FadeoutDraw();
public:
	ResultScene(SceneController& controller, Input& input);
	~ResultScene();
	void Update() override;
	void Draw(float fps) override;
};