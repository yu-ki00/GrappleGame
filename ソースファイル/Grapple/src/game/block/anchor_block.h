#pragma once
#include"../Object3D/Object3D.h"
#include<DxLib.h>
class CAnchorBlock:public Object3D{
private:
	bool m_hit;//レティクルとの接触判定
	bool m_anchit;//アンカーとの接触判定
	VECTOR m_startpos;
	bool m_movecomp;
	bool m_isMoveX;
	int m_movelen;
	bool m_isMoveY;

public:
	CAnchorBlock();
	void Init();
	void Load(int originhndl);
	void Step();
	int GetHndl() { return m_hndl; }
	MATRIX GetMatrix(){ return MV1GetLocalWorldMatrix(m_hndl); }
	bool GetHit() { return m_hit; }
	void SetHit(bool hit) { m_hit = hit; }
	bool GetAncHit() { return m_anchit; }
	void SetAncHit(bool hit) { m_anchit = hit; }
	void MoveX(int move);
	void MoveY(int move);
	void SetMoveX(bool ismove, int movelen);
	void SetMoveY(bool ismove, int movelen);

};