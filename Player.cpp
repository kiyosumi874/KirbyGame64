#include "Player.h"

Player::Player(const VECTOR& transform, Input& input)
	: GameObject (transform, game::tag::PLAYER1)
{
	m_prevTransform = m_transform;
	m_input = &input;
	m_boxCollider = std::make_unique<BoxCollider>(VGet(m_transform.x, m_transform.y + 50, m_transform.z), VGet(20, 40, 20), game::COLOR_BLUE);
	m_attack = Attack::ATTACK_UP;
}

Player::~Player()
{
}

void Player::Update()
{
	if (m_input->IsPress(m_input->BUTTON_ID_W))
	{
		m_transform = VAdd(m_transform, VGet(0, 0, 2));
		m_attack = Attack::ATTACK_UP;
	}
	if (m_input->IsPress(m_input->BUTTON_ID_A))
	{
		m_transform = VAdd(m_transform, VGet(-2, 0, 0));
		m_attack = Attack::ATTACK_LEFT;
	}
	if (m_input->IsPress(m_input->BUTTON_ID_S))
	{
		m_transform = VAdd(m_transform, VGet(0, 0, -2));
		m_attack = Attack::ATTACK_DOWN;
	}
	if (m_input->IsPress(m_input->BUTTON_ID_D))
	{
		m_transform = VAdd(m_transform, VGet(2, 0, 0));
		m_attack = Attack::ATTACK_RIGHT;
	}

	if (m_input->IsDown(m_input->BUTTON_ID_SPACE))
	{
		const float shotSpeed = 16.0;
		switch (m_attack)
		{
		case Player::Attack::ATTACK_UP:
			m_shotVec.emplace_back(std::make_unique<Shot>(VAdd(m_transform, VGet(0, 50, 0)), VGet(0, 0, shotSpeed)));
			break;
		case Player::Attack::ATTACK_DOWN:
			m_shotVec.emplace_back(std::make_unique<Shot>(VAdd(m_transform, VGet(0, 50, 0)), VGet(0, 0, -shotSpeed)));
			break;
		case Player::Attack::ATTACK_LEFT:
			m_shotVec.emplace_back(std::make_unique<Shot>(VAdd(m_transform, VGet(0, 50, 0)), VGet(-shotSpeed, 0, 0)));
			break;
		case Player::Attack::ATTACK_RIGHT:
			m_shotVec.emplace_back(std::make_unique<Shot>(VAdd(m_transform, VGet(0, 50, 0)), VGet(shotSpeed, 0, 0)));
			break;
		default:
			break;
		}
	}

	if (!m_shotVec.empty())
	{
		for (auto& it : m_shotVec)
		{
			it->Update();
		}
	}

	m_boxCollider->SetTransform(m_transform - m_prevTransform);
	m_prevTransform = m_transform;
}

void Player::Draw()
{
	if (!m_shotVec.empty())
	{
		for (auto& it : m_shotVec)
		{
			it->Draw();
		}
	}
	m_boxCollider->Draw();
}
