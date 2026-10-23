#pragma once
#include<DxLib.h>

class Object3D {
protected:
	VECTOR m_pos;		//座標

	VECTOR m_scale;		//モデルサイズ

	VECTOR m_rot;		//モデル角度

	int m_hndl;			//モデルハンドル

	bool m_isActive;	//生存判定

public:
	Object3D();
	virtual void Init(void);//初期化

	virtual void Update(void);//更新

	virtual void Draw(void);//描画

	virtual void Exit(void);//終了

	VECTOR GetPos(void) { return m_pos; }//座標の取得

	void SetPos(VECTOR pos) { m_pos = pos; }//座標の指定

	bool GetActive() { return m_isActive; }

	VECTOR GetRot() { return m_rot; }

	void SetActive(bool active) { m_isActive = active; }


	void SetRot(VECTOR rot) { m_rot = rot; }

};
