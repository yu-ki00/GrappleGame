#pragma once
#include<DxLib.h>
#include"../Object3D/Object3D.h"
#include"../grapple/grapple.h"
#include"../block/blockManager.h"
#include"../common.h"
#include"../../lib/input/Mouse.h"

static const VECTOR PLAYER_SIZE = { 15.0f,20.0f,15.0f };
static const VECTOR START_POS = { 200.0f,50.0f,BLOCK_SIZE * 3 };
static const char PLAYER_PATH[] = { "Data/Model/Player/player.mv1" };
static const float JUMP_SPEED = 100.0f;	//ジャンプ速度
const float MOVE_ACCEL = 800.0f;		//移動加速度
const float FRICTION = 5.0f;			//地面摩擦
static const float MAX_SPEED = 100.0f;	//最大速度
static const float AIR_DRAG = 8.0f;		//空気抵抗係数
static const int INERTIAL_BOOST = 150;	//慣性ジャンプ
static const float ANIM_SPD = 1.0f;		//アニメーション再生速度
static const float AIR_ACCEL = 20.0f;	//空中加速
static const float AIR_CONTROL = 10.0f;	//空中制御	

class CPlayer :public Object3D {
public:
	enum tagSTATE {
		WAIT,
		WALK,
		GRAPPLE


	};
private:

	VECTOR m_speed;		//移動速度

	VECTOR m_size;		//プレイヤーサイズ

	bool m_isGround;	//着地しているか

	VECTOR m_velocity;	//速度ベクトル

	float m_Accel;		//加速度

	//アニメーション関連（まだ動かない）======

	typedef struct {
		float m_endFrame;	// アニメ全再生時間
		float m_frame;		// アニメ再生時間
		float m_speed;		// アニメ再生速度
		int m_hndl;			// アニメハンドル
		int m_id;			// 再生中のアニメID
		int m_state;		// アニメの状態
	}ANIM_DATA;

	ANIM_DATA m_animData;	//アニメーション関連

	int m_animindex;

	tagSTATE m_state;	//現在の状態

	void DetachAnim();

	void RequestAnim(int animID, float animSpd);

	void RequestAnimLoop(int animID, float animSpd);

	void UpdateAnim();

	//=========================================

	//プレイヤーの地上の移動
	bool MoveExec(float dt);

	//グラップル中の移動
	void MoveSwing(VECTOR ancpos, float dt, float ropelength);
	//ジャンプ処理
	void JumpExec();

	void GrappleJump();
public:
	CPlayer();

	//初期化
	void Init();

	//ロード
	void Load();

	//毎フレーム動かす処理
	void Step(VECTOR camera_rot, float dt, VECTOR ancpos, bool isShot, CGrapple& grapple);

	//描画
	void Draw();

	void Reset();


	//SET関係 ================================================

	//速度ベクトルのリセット
	void ResetVelocity_Y() { m_velocity.y = 0.0f; }

	void ResetVelocity_X() { m_velocity.x = 0.0f; }

	void ResetVelocity_Z() { m_velocity.z = 0.0f; }

	//接地判定の更新
	void IsGround(bool isGround) { m_isGround = isGround; }

	//===========================================================

	//Get関連 ====================================================

	//モデルハンドルの取得
	int GetHndl() { return m_hndl; }

	//接地判定の取得
	bool GetGround() { return m_isGround; }

	//プレイヤーの中点の取得
	VECTOR GetCenter();

	//プレイヤーの半径の取得
	float GetRadius() { return m_size.y / 2; }

	//プレイヤーのサイズの取得
	VECTOR GetSize() { return m_size; }

	VECTOR GetVelocity() { return m_velocity; }
	//============================================================


};

