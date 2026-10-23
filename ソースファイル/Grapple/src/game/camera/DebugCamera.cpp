#include"DebugCamera.h"
#include<math.h>
#include"../common.h"


//----------------------
// コンストラクタ
//----------------------
DebugCamera::DebugCamera()
{
	m_Pos = ZERO;
	m_Rot = ZERO;
}

//----------------------
// 初期化
//----------------------
void DebugCamera::Init()
{
	m_Pos = ZERO;
	m_Rot = ZERO;
}

//------------------------
// カメラの座標計算
//------------------------
void DebugCamera::Step()
{
	// カメラの回転処理========================
	// 上下回転
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_Rot.x -= ROT_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_Rot.x += ROT_SPEED;
	}

	// 左右回転
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_Rot.y += ROT_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_Rot.y -= ROT_SPEED;
	}

	//=========================================

	// カメラの移動処理========================
	// 前進
	if (CheckHitKey(KEY_INPUT_W))
	{

		// カメラの角度がオール0度の時に進む速度

		VECTOR defaultDir = { 0.0f,0.0f,MOVE_SPEED };

		// 上記を行列に変換

		MATRIX dir = MGetTranslate(defaultDir);

		// X軸回転行列

		MATRIX rotX = MGetRotX(m_Rot.x);

		// Y軸回転行列

		MATRIX rotY = MGetRotY(m_Rot.y);

		// 各行列を合成していく

		MATRIX res = MMult(dir, rotX);

		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す

		VECTOR move;

		move.x = res.m[3][0];

		move.y = res.m[3][1];

		move.z = res.m[3][2];

		// 計算結果をカメラの現在の座標に足す

		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}

	if (CheckHitKey(KEY_INPUT_A))
	{

		// カメラの角度がオール0度の時に進む速度

		VECTOR defaultDir = { -MOVE_SPEED,0.0f,0.0f };

		// 上記を行列に変換

		MATRIX dir = MGetTranslate(defaultDir);

		// X軸回転行列

		MATRIX rotX = MGetRotX(m_Rot.x);

		// Y軸回転行列

		MATRIX rotY = MGetRotY(m_Rot.y);

		// 各行列を合成していく

		MATRIX res = MMult(dir, rotX);

		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す

		VECTOR move;

		move.x = res.m[3][0];

		move.y = res.m[3][1];

		move.z = res.m[3][2];

		// 計算結果をカメラの現在の座標に足す

		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}
	if (CheckHitKey(KEY_INPUT_S))
	{

		// カメラの角度がオール0度の時に進む速度

		VECTOR defaultDir = { 0.0f,0.0f,-MOVE_SPEED };

		// 上記を行列に変換

		MATRIX dir = MGetTranslate(defaultDir);

		// X軸回転行列

		MATRIX rotX = MGetRotX(m_Rot.x);

		// Y軸回転行列

		MATRIX rotY = MGetRotY(m_Rot.y);

		// 各行列を合成していく

		MATRIX res = MMult(dir, rotX);

		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す

		VECTOR move;

		move.x = res.m[3][0];

		move.y = res.m[3][1];

		move.z = res.m[3][2];

		// 計算結果をカメラの現在の座標に足す

		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		// カメラの角度がオール0度の時に進む速度

		VECTOR defaultDir = { MOVE_SPEED,0.0f,0.0f };

		// 上記を行列に変換

		MATRIX dir = MGetTranslate(defaultDir);

		// X軸回転行列

		MATRIX rotX = MGetRotX(m_Rot.x);

		// Y軸回転行列

		MATRIX rotY = MGetRotY(m_Rot.y);

		// 各行列を合成していく

		MATRIX res = MMult(dir, rotX);

		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す

		VECTOR move;

		move.x = res.m[3][0];

		move.y = res.m[3][1];

		move.z = res.m[3][2];

		// 計算結果をカメラの現在の座標に足す

		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}

}

//------------------------
// カメラの更新
//------------------------
void DebugCamera::Update()
{
	SetCameraPositionAndAngle(m_Pos, m_Rot.x, m_Rot.y, m_Rot.z);
}