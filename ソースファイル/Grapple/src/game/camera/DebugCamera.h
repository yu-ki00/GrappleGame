#pragma once
#include<DxLib.h>

static const float ROT_SPEED = 0.05f;   // カメラの回転速度
static const float MOVE_SPEED = 5.0f;
class DebugCamera {
private:
	VECTOR m_Pos;      // カメラの視点
	VECTOR m_Rot;      // カメラの回転角度

public:
	// コンストラクタ
	DebugCamera();

	// 初期化
	void Init();

	// カメラの座標計算
	void Step();

	// カメラの更新
	void Update();
};
