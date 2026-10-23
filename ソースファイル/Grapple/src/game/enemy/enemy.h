#pragma once
#include<Dxlib.h>
#include"../Object3D/Object3D.h"
#include"../shot/ShotManager.h"

static const int SHOT_WAIT = 40;

static const int DETECTION_RANGE = 300;
class CEnemy :public Object3D {
private:

	int m_shotWait;//çUåÇÇÃë“ã@éûä‘

public:

	void Init();

	void Step(VECTOR plpos, CShotManager& shot,bool isShot);

	void Load(int hndl);

	void Reset();
};