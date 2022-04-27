#pragma once
#include "GameObject.h"
#include "Input.h"

class Camera final : public GameObject
{
public:
	Camera(VECTOR transform, VECTOR target, float nearr, float farr, Input& input);
	~Camera() override;
	void Update() override;
	void Draw() override;
private:
	float m_near;
	float m_far;
	VECTOR m_rotate;
	Input* m_input;
};