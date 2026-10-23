#pragma once
#include<DxLib.h>
#include "Shot.h"

//’è‹`ŠÖ˜A--------------------------------
static const char PLSHOT_MODEL_PATH[] = { "aa" };
static const int SHOT_NUM = 50;
//----------------------------------------

class CShotManager {
private:
	CShot m_shot[SHOT_NUM];
public:
	CShotManager();
	~CShotManager();
	void Init();
	void Load();
	void Exit();
	void Update();
	void Step( VECTOR plpos);
	void Draw();
	void RequestShot(const VECTOR& pos, const VECTOR& speed, const VECTOR& rot);
	//’eˆê”­•ª‚Ìî•ñæ“¾
	CShot& GetShot(int id) { return m_shot[id]; }
	VECTOR GetCenter(int i) { m_shot[i].GetCenter(); }
};