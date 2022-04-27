#pragma once
#include "GameObject.h"
#include "Definition.h"
#include "BoxCollider.h"

#include <vector>
#include <map>
#include <memory>

class ShotDirector : public GameObject
{
public:
	ShotDirector();
	~ShotDirector() override;

	void Update() override;
	void Draw() override;

	void SetShotTransformVec(game::tag tag, const std::vector<VECTOR>& vec);
	void SetMapTransformVec(const std::vector<BoxCollider*>& boxColliderVec, const std::vector<bool>& flag);

	void SetPlayer1Transform(const VECTOR& transform) { m_player1Transform = transform; }

	const std::vector<bool>& GetAliveFlagVec() const { return m_aliveFlagVec; }
	void SetAliveFlagVec(const std::vector<bool>& vec) { m_aliveFlagVec = vec; }
	void SetCountVec(const std::vector<int>& vec) { m_countVec = vec; }
	const std::vector<int>& GetCountVec() { return m_countVec; }
	void AdjustmentFlag();

private:

	// Žó‚¯Žæ‚é‚à‚Ì
	std::map<game::tag, std::vector<VECTOR>> m_map;

	std::vector<BoxCollider*> m_boxColliderVec;
	std::vector<bool> m_aliveFlagVec;
	std::vector<int> m_countVec;

	VECTOR m_player1Transform;
};
