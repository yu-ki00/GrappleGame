#pragma once
#include"../Object3D/Object3D.h"

class CBlock:public Object3D{
private:
	bool m_hit;
public:
	CBlock();
	void Init();
	void Load(int originhndl);
	void Step();
	int GetHndl() { return m_hndl; }
	MATRIX GetMatrix() { return MV1GetLocalWorldMatrix(m_hndl); }
	bool GetHit() { return m_hit; }
	void SetHit(bool hit) { m_hit = hit; }
};