#include "Map.h"

Map::Map(const VECTOR& transform, const VECTOR& size)
	: GameObject(transform, game::tag::MAP)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_boxColliderVec.emplace_back(std::make_unique<BoxCollider>(VGet(m_transform.x * j, m_transform.y, m_transform.z * i), size, game::COLOR_BLACK));
			m_boxCollider2DVec[0].emplace_back(std::make_unique<BoxCollider>(VGet(m_transform.x * j, m_transform.y + size.y / 2.0f, m_transform.z * i - size.z / 2.0f), VAdd(size, VGet(0, size.y, -size.z)), game::COLOR_WHITE));
			m_boxCollider2DVec[1].emplace_back(std::make_unique<BoxCollider>(VGet(m_transform.x * j, m_transform.y + size.y / 2.0f, m_transform.z * i + size.z / 2.0f), VAdd(size, VGet(0, size.y, -size.z)), game::COLOR_WHITE));
			m_boxCollider2DVec[2].emplace_back(std::make_unique<BoxCollider>(VGet(m_transform.x * j - size.x / 2.0f, m_transform.y + size.y / 2.0f, m_transform.z * i), VAdd(size, VGet(-size.x, size.y, 0)), game::COLOR_WHITE));
			m_boxCollider2DVec[3].emplace_back(std::make_unique<BoxCollider>(VGet(m_transform.x * j + size.x / 2.0f, m_transform.y + size.y / 2.0f, m_transform.z * i), VAdd(size, VGet(-size.x, size.y, 0)), game::COLOR_WHITE));
			m_aliveFlag2DVec[0].emplace_back(true);
			m_aliveFlag2DVec[1].emplace_back(true);
			m_aliveFlag2DVec[2].emplace_back(true);
			m_aliveFlag2DVec[3].emplace_back(true);
			m_aliveFlagVec.emplace_back(true);
			m_aliveFlagVec2.emplace_back(true);
			m_countVec.emplace_back(0);
		}
	}
	m_prevTransform = m_transform;
}

Map::~Map()
{
}

void Map::Update()
{
	std::vector<VECTOR> tmpVec[4];

	// 0は下　1は上　2は左　3は右
	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (auto& it : m_boxCollider2DVec[i])
		{
			if (m_aliveFlagVec2[count])
			{
				tmpVec[i].emplace_back(it->GetTransform());
			}
			else
			{
				tmpVec[i].emplace_back(game::VECTOR_0);
			}
			count++;
		}

		for (auto item : m_aliveFlag2DVec[i])
		{
			item = true;
		}
	}

	{
		int count = 0;
		for (auto down : tmpVec[0])
		{
			int count2 = 0;
			for (auto up : tmpVec[1])
			{
				if (((up.x == down.x) && (up.y == down.y)) && (up.z == down.z))
				{
					m_aliveFlag2DVec[0][count]  = false;
					m_aliveFlag2DVec[1][count2] = false;
				}
				count2++;
			}
			count++;
		}
	}

	{
		int count = 0;
		for (auto down : tmpVec[2])
		{
			int count2 = 0;
			for (auto up : tmpVec[3])
			{
				if (((up.x == down.x) && (up.y == down.y)) && (up.z == down.z))
				{
					m_aliveFlag2DVec[2][count]  = false;
					m_aliveFlag2DVec[3][count2] = false;
				}

				count2++;
			}
			count++;
		}
	}


	int count = 0;
	for (auto& it : m_boxColliderVec)
	{
		if (!m_aliveFlagVec[count])
		{
			m_countVec[count]++;
			if (m_countVec[count] > 60)
			{
				m_aliveFlagVec2[count] = false;
				it->SetTransform(VGet(0, -2, 0));
			}
			auto limit = VGet(0, -300, 0);
			auto transform = it->GetTransform();
			if (m_countVec[count] > 300)
			{
				it->ResetTransform();
				m_aliveFlagVec[count] = true;
				m_aliveFlagVec2[count] = true;
			}
		}
		count++;
	}

}

void Map::Draw()
{

	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (auto& it : m_boxCollider2DVec[i])
		{
			if (m_aliveFlag2DVec[i][count])
			{
				it->Draw();
			}
			count++;
		}
	}

	{
		int count = 0;
		for (auto& it : m_boxColliderVec)
		{
			if (m_aliveFlagVec[count])
			{
				it->Draw();
			}
			else
			{
				it->Draw(game::COLOR_RED);
			}
			count++;
		}
	}
}
