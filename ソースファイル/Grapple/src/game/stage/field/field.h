#pragma once
#include<DxLib.h>
#include"../../Object3D/Object3D.h"
#include"../../../lib/Data/Data.h"
enum tagField {
	STAGE_1,
	STAGE_2,
	STAGE_3
};
class CField :public Object3D {
private:
	tagField m_state;
public:
	void Init();
	void Load();
	int GetHndl() { return m_hndl; }
	VECTOR GetGoalPos() { return MV1GetFramePosition(m_hndl, MV1SearchFrame(m_hndl, "Goal")); }
};