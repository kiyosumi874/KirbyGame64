#pragma once
#include "DxLib.h"

class BoxCollider
{
public:

	BoxCollider(const VECTOR& center, const VECTOR& size, unsigned int color);

	~BoxCollider();

	void Draw();
	void Draw(unsigned int color);

	void SetTransform(const VECTOR& differenceTransform);
	const VECTOR& GetTransform() const { return m_center; }
	const VECTOR& GetSize() const { return m_size; }

	void ResetTransform()
	{
		m_center = m_firstCenter;
	}

private:
	VECTOR m_center;
	VECTOR m_firstCenter;

	VECTOR m_size;
	unsigned int m_color;

};
