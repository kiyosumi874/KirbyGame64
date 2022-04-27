#pragma once
#include "DxLib.h"
#include "BoxCollider.h"
#include "Definition.h"
#include <memory>

class Shot
{
public:
	Shot(const VECTOR& transform, const VECTOR& speed);
	~Shot();

	void Update();
	void Draw();

	const VECTOR& GetTransform() const { return m_transform; }
private:
	VECTOR m_transform;
	VECTOR m_prevTransform;
	VECTOR m_speed;

	std::unique_ptr<BoxCollider> m_boxCollider;
};

