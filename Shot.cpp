#include "Shot.h"
#include "Definition.h"

Shot::Shot(const VECTOR& transform, const VECTOR& speed)
{
	m_transform = transform;
	m_prevTransform = m_transform;
	m_speed = speed;
	m_boxCollider = std::make_unique<BoxCollider>(m_transform, VGet(0, 50, 0), game::COLOR_RED);
}

Shot::~Shot()
{
}

void Shot::Update()
{
	m_transform += m_speed;

	m_boxCollider->SetTransform(m_transform - m_prevTransform);
	m_prevTransform = m_transform;

}

void Shot::Draw()
{
	m_boxCollider->Draw();
}
