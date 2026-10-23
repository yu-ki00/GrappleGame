#pragma once
#include<DxLib.h>
#include"../Object3D/Object3D.h"

static const float SHOT_SPEED = 6.0f;
//敵のショットクラス
class CShot:public Object3D {
private:
	VECTOR m_speed;
	int m_destroyTime;
	float m_radius;
	
public:
	CShot();
	~CShot();
	void Init();
	void Load(int originHndl);
	void Step(VECTOR plpos);
	void Draw();
	bool RequestShot(const VECTOR& pos, const VECTOR& speed, const VECTOR& rot);
	float GetRadius() { return m_radius; }
	VECTOR GetCenter();
	void HitCalc();
};