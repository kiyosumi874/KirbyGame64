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
		|___|/  <-これを作る */
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
	// @brief ２つのベクトルの角度はほぼ同じか
	// @param[in] v1 調査したいベクトル1
	// @param[in] v2 調査したいベクトル2
	// @return 二つがほぼ同じ角度であれば true 異なればfalseを返す
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
	// @param[in] nowVec 現在の方向ベクトル
	// @param[in] dirVec 目標方向ベクトル
	// @return float 時計回り方向の時は+1.0 反時計回り方向の時は -1.0を返す.
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
	// @brief nowVecから aimVecに向かってdegreeVerociyの速度でY回転する.
	// @param[in] nowVec 現在の方向ベクトル
	// @param[in] aimVec 目標方向ベクトル
	//-------------------------------------------------------------------------------
	static VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity)
	{
		// 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
		float rotRadian = (DX_PI_F * degreeVerocity / 180.0f);
		rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

		// Y軸回転行列を作成する
		MATRIX yrotMat = MGetRotY(rotRadian);

		// Y軸回転する
		VECTOR rotVec;
		rotVec = VTransform(nowVec, yrotMat);

		return rotVec;
	}

}

// @brief ベクトル同士の加算
static VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = lhs.x + rhs.x;
	ret.y = lhs.y + rhs.y;
	ret.z = lhs.z + rhs.z;
	return ret;
}

// @brief ベクトル同士の減算
static VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = lhs.x - rhs.x;
	ret.y = lhs.y - rhs.y;
	ret.z = lhs.z - rhs.z;
	return ret;
}

// @brief ベクトルのスカラー倍
static VECTOR operator*(float s, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = s * rhs.x;
	ret.y = s * rhs.y;
	ret.z = s * rhs.z;
	return ret;
}

// @brief ベクトルのスカラー倍
static VECTOR operator*(const VECTOR& lhs, float s)
{
	VECTOR ret;
	ret.x = s * lhs.x;
	ret.y = s * lhs.y;
	ret.z = s * lhs.z;
	return ret;
}

// @brief += VECTORの演算子
static VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

// @brief *= VECTORのスカラー倍の複合代入演算子
static VECTOR operator*=(VECTOR& lhs, float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}