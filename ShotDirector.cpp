#include "ShotDirector.h"

ShotDirector::ShotDirector()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_aliveFlagVec.emplace_back(true);
			m_countVec.emplace_back(0);
		}
	}
}

ShotDirector::~ShotDirector()
{
}

void ShotDirector::Update()
{
	if (m_map.find(game::tag::PLAYER1) != m_map.end())
	{
		auto transVec = m_map[game::tag::PLAYER1];
		if (!transVec.empty())
		{
			for (auto it : transVec)
			{
				int count = 0;
				for (auto it2 : m_boxColliderVec)
				{
					auto mapCenter = it2->GetTransform();
					auto mapSize = it2->GetSize();
					auto mapX = mapCenter.x - mapSize.x / 2;
					auto mapZ = mapCenter.z - mapSize.z / 2;
					auto mapWidth = mapX + mapSize.x;
					auto mapHeight = mapZ + mapSize.z;

					auto p1X = m_player1Transform.x - 10;
					auto p1Z = m_player1Transform.z - 10;
					auto p1Width = p1X + 20;
					auto p1Height = p1Z + 20;

					if ((it.x > mapX && it.x < mapWidth) && (it.z > mapZ && it.z < mapHeight))
					{
						if (!((p1X > mapX && p1Width < mapWidth) && (p1Z > mapZ && p1Height < mapHeight)))
						{
							m_aliveFlagVec[count] = false;
						}
					}
					count++;
				}
			}
		}
	}
	
}

void ShotDirector::Draw()
{
}

void ShotDirector::SetShotTransformVec(game::tag tag, const std::vector<VECTOR>& vec)
{
	if (m_map.find(tag) == m_map.end())
	{
		m_map.emplace(tag, vec);
	}
	else
	{
		m_map[tag] = vec;
	}
}

void ShotDirector::SetMapTransformVec(const std::vector<BoxCollider*>& boxColliderVec, const std::vector<bool>& flag)
{
	m_boxColliderVec = boxColliderVec;
	m_aliveFlagVec = flag;
}

void ShotDirector::AdjustmentFlag()
{
	int count = 0;
	for (int i = 0; i < 100; i++)
	{
		if (m_countVec[count] > 300)
		{
			m_aliveFlagVec[count] = true;
			m_countVec[count] = 0;
		}
		count++;
	}
}
