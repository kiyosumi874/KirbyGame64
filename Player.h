#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "Shot.h"
#include <vector>
#include <memory>
#include "Input.h"

class Player : public GameObject
{
public:
	Player(const VECTOR& transform, Input& input);
	virtual ~Player();

	virtual void Update();
	virtual void Draw();

	const std::vector<VECTOR>& GetShotVec()
	{ 
		m_shotVec2.clear();
		
		if (!m_shotVec.empty())
		{
			for (auto& item : m_shotVec)
			{
				m_shotVec2.emplace_back(item->GetTransform());
			}
		}
		


		return m_shotVec2;
	}

private:
	enum class Attack
	{
		ATTACK_UP,
		ATTACK_DOWN,
		ATTACK_LEFT,
		ATTACK_RIGHT
	};
	Attack m_attack;
	VECTOR m_prevTransform;

	std::unique_ptr<BoxCollider> m_boxCollider;
	Input* m_input;
	std::vector<std::unique_ptr<Shot>> m_shotVec;
	std::vector<VECTOR> m_shotVec2;
};
