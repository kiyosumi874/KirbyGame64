#pragma once
#include "DxLib.h"
#include "Definition.h"
#include "GameObject.h"
#include <vector>
#include <memory>
class Input;
class SceneController;
///�V�[���Ǘ��̂��߂̊��N���X
///(�������z�N���X)
class Scene
{
protected:
	SceneController* m_controller;
	Input* m_input;
	std::vector<std::unique_ptr<GameObject>> m_gameObject;
public:
	Scene(SceneController& controller, Input& input) : m_controller(&controller) , m_input(&input){}
	virtual ~Scene() {}

	///�V�[���̍X�V���s��
	virtual void Update() = 0;

	///�`�悵�����`��
	virtual void Draw(float fps) = 0;

};