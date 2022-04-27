#pragma once
#include "DxLib.h"
#include "Definition.h"

class GameObject
{
public:
	GameObject() {}
	GameObject(const VECTOR& transform, game::tag tag) : m_transform (transform) , m_tag (tag) {}
	virtual ~GameObject() {}
	virtual void Update() {}
	virtual void Draw() {}

	game::tag GetTag() { return m_tag; }
	const VECTOR& GetTransform() const { return m_transform; }
protected:
	VECTOR m_transform = { 0,0,0 };
	game::tag m_tag;
};