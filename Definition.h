#pragma once
#include "DxLib.h"

namespace game
{
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;
	constexpr unsigned int COLOR_RED = 4294901760;
	constexpr unsigned int COLOR_GREEN = 4278255360;
	constexpr unsigned int COLOR_BLUE = 4278190335;
	constexpr unsigned int COLOR_BLACK = 4278190080;
	constexpr unsigned int COLOR_WHITE = 4294967295;
	constexpr float MIN_FRAME_TIME = 1.0f / 30.0f;
	const VECTOR VECTOR_0 = VGet(0.0f, 0.0f, 0.0f);

	enum class tag
	{
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		BULLET,
		MAP,
		CAMERA

	};

	/*   ___
		/___/|
		|___|/  <-�������� */
	static void DrawBox3D(VECTOR vec1, VECTOR vec2, unsigned int color = COLOR_GREEN)
	{
		auto pos1 = vec1;
		auto pos2 = pos1;

		pos2.x = pos1.x + vec2.x;
		DrawLine3D(pos1, pos2, color);

		pos2.x = pos1.x;
		pos2.y = pos1.y + vec2.y;
		DrawLine3D(pos1, pos2, color);

		pos2.y = pos1.y;
		pos2.z = pos1.z + vec2.z;
		DrawLine3D(pos1, pos2, color);

		pos1.x = vec1.x + vec2.x;
		pos1.y = vec1.y + vec2.y;
		pos2 = pos1;

		pos2.x = pos1.x - vec2.x;
		DrawLine3D(pos1, pos2, color);

		pos2.x = pos1.x;
		pos2.y = pos1.y - vec2.y;
		DrawLine3D(pos1, pos2, color);

		pos2.y = pos1.y;
		pos2.z = pos1.z + vec2.z;
		DrawLine3D(pos1, pos2, color);

		pos1 = vec1;
		pos1.y = vec1.y + vec2.y;
		pos1.z = vec1.z + vec2.z;
		pos2 = pos1;

		pos2.x = pos1.x + vec2.x;
		DrawLine3D(pos1, pos2, color);

		pos2.x = pos1.x;
		pos2.y = pos1.y - vec2.y;
		DrawLine3D(pos1, pos2, color);

		pos2.y = pos1.y;
		pos2.z = pos1.z - vec2.z;
		DrawLine3D(pos1, pos2, color);
		
		pos1 = vec1;
		pos1.x = vec1.x + vec2.x;
		pos1.z = vec1.z + vec2.z;
		pos2 = pos1;

		pos2.x = pos1.x - vec2.x;
		DrawLine3D(pos1, pos2, color);

		pos2.x = pos1.x;
		pos2.y = pos1.y + vec2.y;
		DrawLine3D(pos1, pos2, color);

		pos2.y = pos1.y;
		pos2.z = pos1.z - vec2.z;
		DrawLine3D(pos1, pos2, color);

	}

	//-------------------------------------------------------------------------------
	// @brief �Q�̃x�N�g���̊p�x�͂قړ�����
	// @param[in] v1 �����������x�N�g��1
	// @param[in] v2 �����������x�N�g��2
	// @return ����قړ����p�x�ł���� true �قȂ��false��Ԃ�
	//-------------------------------------------------------------------------------
	static bool IsNearAngle(const VECTOR& v1, const VECTOR& v2)
	{
		float dot = VDot(v1, v2);
		if (dot > 0.99f)
		{
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------------
	// @param[in] nowVec ���݂̕����x�N�g��
	// @param[in] dirVec �ڕW�����x�N�g��
	// @return float ���v�������̎���+1.0 �����v�������̎��� -1.0��Ԃ�.
	//-------------------------------------------------------------------------------
	static float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
	{
		VECTOR axis;
		axis = VCross(nowVec, dirVec);
		if (axis.y < 0.0f)
		{
			return -1.0f;
		}
		return 1.0f;
	}

	//-------------------------------------------------------------------------------
	// @brief nowVec���� aimVec�Ɍ�������degreeVerociy�̑��x��Y��]����.
	// @param[in] nowVec ���݂̕����x�N�g��
	// @param[in] aimVec �ڕW�����x�N�g��
	//-------------------------------------------------------------------------------
	static VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity)
	{
		// �p���x�i�x���j�����W�A���p�ɕϊ��A�E��肩����肩�𒲂ׂ�
		float rotRadian = (DX_PI_F * degreeVerocity / 180.0f);
		rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

		// Y����]�s����쐬����
		MATRIX yrotMat = MGetRotY(rotRadian);

		// Y����]����
		VECTOR rotVec;
		rotVec = VTransform(nowVec, yrotMat);

		return rotVec;
	}

}

// @brief �x�N�g�����m�̉��Z
static VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = lhs.x + rhs.x;
	ret.y = lhs.y + rhs.y;
	ret.z = lhs.z + rhs.z;
	return ret;
}

// @brief �x�N�g�����m�̌��Z
static VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = lhs.x - rhs.x;
	ret.y = lhs.y - rhs.y;
	ret.z = lhs.z - rhs.z;
	return ret;
}

// @brief �x�N�g���̃X�J���[�{
static VECTOR operator*(float s, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = s * rhs.x;
	ret.y = s * rhs.y;
	ret.z = s * rhs.z;
	return ret;
}

// @brief �x�N�g���̃X�J���[�{
static VECTOR operator*(const VECTOR& lhs, float s)
{
	VECTOR ret;
	ret.x = s * lhs.x;
	ret.y = s * lhs.y;
	ret.z = s * lhs.z;
	return ret;
}

// @brief += VECTOR�̉��Z�q
static VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

// @brief *= VECTOR�̃X�J���[�{�̕���������Z�q
static VECTOR operator*=(VECTOR& lhs, float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}