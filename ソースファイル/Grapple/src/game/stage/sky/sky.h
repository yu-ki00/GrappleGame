#pragma once
#include<DxLib.h>


class CSky {
private:
	VECTOR m_pos;
	VECTOR m_rot;
	VECTOR m_scale;

	int m_hndl;
public:
	void Init();
	void Load();
	void Step(VECTOR pos);
	void Update();
	void Draw();
	void Exit();
};
