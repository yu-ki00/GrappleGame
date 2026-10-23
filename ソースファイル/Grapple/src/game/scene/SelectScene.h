#pragma once
#include<DxLib.h>

static const char StageHndlPath[3][128] = { "Data/graphics/stage1.png","Data/graphics/stage2.png" ,"Data/graphics/stage3.png" };
class CSelectScene {
public:
	enum tagStage {
		STAGE_1,
		STAGE_2,
		STAGE_3
	};
private:
	enum tagSelectScene {
		INIT,
		LOAD,
		STARTWAIT,
		MAIN,
		SELECT_1,
		SELECT_2,
		SELECT_3
	};

	int m_hndl[3];

	tagSelectScene m_state;

	tagStage m_select;

	float m_highScore[3];

public:
	CSelectScene();

	~CSelectScene();

	int Loop(int clearTime);

	void Draw();
private:
	void Init(int clearTime);

	void Load();

	void Step();

	void Exit();
};