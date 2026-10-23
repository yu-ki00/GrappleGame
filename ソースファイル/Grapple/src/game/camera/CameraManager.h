#pragma once
#include"PlayerCamera.h"
#include"DebugCamera.h"

// 複数のカメラを管理する
class CameraManager {
public:
	// カメラのタイプ
	enum tagCAMERA_ID
	{
		ID_PLAY,    // ゲームのメインカメラ
		ID_DEBUG,   // デバッグ用のカメラ

		ID_NUM
	};

private:
	PlayCamera m_Play;    // メインとなるカメラ
	tagCAMERA_ID m_id;    // 今どのカメラを使っているか
	DebugCamera m_debug;

public:
	// コンストラクタ
	CameraManager();

	// 初期化
	void Init();
	void Load();
	// カメラの座標計算
	// @forcus : プレイヤーの座標
	//@rotY    : プレイヤーの角度
	void Step(VECTOR forcus);

	// カメラの更新
	void Update();

	void Draw();
	// カメラのタイプ切り替え
	void ChangeCamera(tagCAMERA_ID id) { m_id = id; }
	// カメラのタイプ取得
	tagCAMERA_ID GetID() { return m_id; }
	VECTOR GetRot() { return m_Play.GetRot(); }
	VECTOR GetPos() { return m_Play.GetPos(); }
	VECTOR GetVec() { return m_Play.GetVec(); }
	VECTOR GetTarget() { return m_Play.GetTarget(); }

	void ReticuleHit(bool hit) { m_Play.ReticuleHit(hit); }
	void Reset() { m_Play.Reset(); }
};
