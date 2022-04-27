#include "BoxCollider.h"
#include "Definition.h"

BoxCollider::BoxCollider(const VECTOR& center, const VECTOR& size, unsigned int color)
{
	m_center = center;
	m_firstCenter = m_center;
	m_size = size;
	m_color = color;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Draw()
{
	float x = m_center.x - m_size.x / 2.0f;
	float y = m_center.y - m_size.y / 2.0f;
	float z = m_center.z - m_size.z / 2.0f;
	auto pos1 = VGet(x, y, z);
	auto pos2 = pos1;
	pos2.x += m_size.x;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.y += m_size.y;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.z += m_size.z;
	DrawLine3D(pos1, pos2, m_color);

	x = m_center.x + m_size.x / 2.0f;
	y = m_center.y - m_size.y / 2.0f;
	z = m_center.z + m_size.z / 2.0f;
	pos1 = VGet(x, y, z);
	pos2 = pos1;
	pos2.x -= m_size.x;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.y += m_size.y;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.z -= m_size.z;
	DrawLine3D(pos1, pos2, m_color);

	x = m_center.x - m_size.x / 2.0f;
	y = m_center.y + m_size.y / 2.0f;
	z = m_center.z + m_size.z / 2.0f;
	pos1 = VGet(x, y, z);
	pos2 = pos1;
	pos2.x += m_size.x;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.y -= m_size.y;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.z -= m_size.z;
	DrawLine3D(pos1, pos2, m_color);

	x = m_center.x + m_size.x / 2.0f;
	y = m_center.y + m_size.y / 2.0f;
	z = m_center.z - m_size.z / 2.0f;
	pos1 = VGet(x, y, z);
	pos2 = pos1;
	pos2.x -= m_size.x;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.y -= m_size.y;
	DrawLine3D(pos1, pos2, m_color);
	pos2 = pos1;
	pos2.z += m_size.z;
	DrawLine3D(pos1, pos2, m_color);

}

void BoxCollider::Draw(unsigned int color)
{
	float x = m_center.x - m_size.x / 2.0f;
	float y = m_center.y - m_size.y / 2.0f;
	float z = m_center.z - m_size.z / 2.0f;
	auto pos1 = VGet(x, y, z);
	auto pos2 = pos1;
	pos2.x += m_size.x;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.y += m_size.y;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.z += m_size.z;
	DrawLine3D(pos1, pos2, color);

	x = m_center.x + m_size.x / 2.0f;
	y = m_center.y - m_size.y / 2.0f;
	z = m_center.z + m_size.z / 2.0f;
	pos1 = VGet(x, y, z);
	pos2 = pos1;
	pos2.x -= m_size.x;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.y += m_size.y;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.z -= m_size.z;
	DrawLine3D(pos1, pos2, color);

	x = m_center.x - m_size.x / 2.0f;
	y = m_center.y + m_size.y / 2.0f;
	z = m_center.z + m_size.z / 2.0f;
	pos1 = VGet(x, y, z);
	pos2 = pos1;
	pos2.x += m_size.x;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.y -= m_size.y;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.z -= m_size.z;
	DrawLine3D(pos1, pos2, color);

	x = m_center.x + m_size.x / 2.0f;
	y = m_center.y + m_size.y / 2.0f;
	z = m_center.z - m_size.z / 2.0f;
	pos1 = VGet(x, y, z);
	pos2 = pos1;
	pos2.x -= m_size.x;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.y -= m_size.y;
	DrawLine3D(pos1, pos2, color);
	pos2 = pos1;
	pos2.z += m_size.z;
	DrawLine3D(pos1, pos2, color);
}

void BoxCollider::SetTransform(const VECTOR& differenceTransform)
{
	m_center += differenceTransform;
}
