#pragma once
#include<DxLib.h>
// カメラとプレイヤーの距離
static const float CAMERA_LENGTH = 60.0f;
// カメラの高さ（初期値）
static const float CAMERA_OFFSET_Y = 20.0f;
// カメラの注視点の高さ（初期値）
static const float TARGET_OFFSET_Y = 25.0f;

static const float SENSITIVITY = 0.05f;
class PlayCamera {
private:
	VECTOR m_camPos;      // 視点
	VECTOR m_targetPos;   // 注視点
	VECTOR m_UpVec;       // カメラの上方向
	VECTOR m_rot;
	int m_hndl;
	int m_hndl2;
	bool m_reticuleHit;
public:
	// コンストラクタ
	PlayCamera();

	// 初期化
	void Init();

	// ニアーファー設定
	void SetNearFar(float n, float f);

	//クロスヘアロード
	void Load();

	// カメラの座標計算
	// @forcus : プレイヤーの座標
	//@rotY    : プレイヤーの角度
	void Step(VECTOR forcus);

	// カメラの更新
	void Update();

	//クロスヘア描画
	void Draw();

	VECTOR GetRot() { return m_rot; }

	VECTOR GetPos() { return m_camPos; }

	VECTOR GetVec();

	VECTOR GetTarget() { return m_targetPos; }

	void ReticuleHit(bool hit) { m_reticuleHit = hit; }

	void Reset() { m_rot = { 0,DX_PI_F,0 }; }

	void Exit();
};
