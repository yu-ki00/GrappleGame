#pragma once
#include"../Object3D/Object3D.h"

enum Move {
	STAY,
	Move_X,
	Move_Y
};
class CDamageBlock:public Object3D{
private:
	bool m_hit;
	Move m_state;
	VECTOR m_startpos;
	bool m_movecomp;
public:
	CDamageBlock();
	void Init();
	void Load(int originhndl);
	void Step();
	int GetHndl() { return m_hndl; }
	MATRIX GetMatrix() { return MV1GetLocalWorldMatrix(m_hndl); }
	bool GetHit() { return m_hit; }
	void SetHit(bool hit) { m_hit = hit; }
	void MoveX(int move);
	void MoveY(int muve);
};