#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include <memory>
#include <vector>

class Map : public GameObject
{
public:
	Map(const VECTOR& transform, const VECTOR& size);
	~Map() override;

	void Update() override;
	void Draw() override;

	const std::vector<BoxCollider*>& GetBoxColliderVec() 
	{ 
		m_boxColliderVec2.clear();

		if (!m_boxColliderVec.empty())
		{
			for (auto& item : m_boxColliderVec)
			{
				m_boxColliderVec2.emplace_back(item.get());
			}
		}

		return m_boxColliderVec2;
	}
	const std::vector<bool>& GetAliveFlagVec() { return m_aliveFlagVec; }
	const std::vector<int>& GetCountVec() { return m_countVec; }
	void SetCountVec(const std::vector<int>& vec) { m_countVec = vec; }

	void SetAliveFlagVec(const std::vector<bool>& flag) { m_aliveFlagVec = flag; }
private:
	std::vector<std::unique_ptr<BoxCollider>> m_boxColliderVec;
	std::vector<BoxCollider*> m_boxColliderVec2;
	std::vector<bool> m_aliveFlagVec;
	std::vector<bool> m_aliveFlagVec2;
	std::vector<int> m_countVec;
	std::vector<std::unique_ptr<BoxCollider>> m_boxCollider2DVec[4];
	std::vector<bool> m_aliveFlag2DVec[4];
	VECTOR m_prevTransform;

};
