#pragma once
#include"DxLib.h"
#include"../Object3D/Object3D.h"
#include"../block/blockManager.h"

static int LENGTH = 200;
static const char GRAPPLE_PATH[] = { "Data/Model/Grapple/grapple.mv1" };
class CGrapple :public Object3D {
private:
	VECTOR m_targetpos;

	VECTOR m_targetpos2;

	bool m_hit2;

	int m_frameIndex;		//フレームの番地

	VECTOR m_framepos;		//フレーム座標

	bool m_isShot;			//発射状態か否か
public:
	//初期化
	void Init();

	//モデルロード
	void Load();

	void Step(int hndl,CBlockManager &block);

	//グラップル発射
	void RequestShot(VECTOR pos);

	//ゲット関連=============================================

	VECTOR GetAncPos() { return m_framepos; }		//アンカーの位置の取得

	float GetLength();								//紐の長さの取得

	VECTOR GetDir();								//プレイヤーから見たアンカーへの方向ベクトル

	bool GetHit2() { return m_hit2; }				//紐が引っ掛かったかの取得

	VECTOR GetTarget2() { return m_targetpos2; }	//紐が引っ掛かった位置の取得

	bool IsShot() { return m_isShot; }				//アンカーを発射したかの取得

	//========================================================

	//セット関連=======================================================

	void SetShot(bool shot) { m_isShot = shot; }				//アンカーの発射状態の更新

	void SetTarget(VECTOR target) { m_targetpos = target; }		//アンカーを飛ばす位置の更新

	void SetHit2(bool hit) { m_hit2=hit; }						//紐が引っ掛かったかの更新

	void SetTarget2(VECTOR target) { m_targetpos2 = target; }	//紐が引っ掛かった位置の更新

	void OutShot();												//アンカーを外した時の処理

	//================================================================

};
