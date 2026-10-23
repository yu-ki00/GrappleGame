#pragma once

#include<DxLib.h>
#include"../../Object3D/Object3D.h"

class CGoal :public Object3D {
public:
	void Init();
	void Load(VECTOR pos);
	void Step();
	VECTOR GetCenter();
};