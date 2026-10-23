#pragma once
#include"stage_block.h"
#include"../../block/blockManager.h"
#include<DxLib.h>
#include"../../common.h"
#define STAGE_BLOCK_NUM 10
class CStageManager {
private:
	CStageBlock m_sblock[STAGE_X][STAGE_Z];
public:
	void Init(int stage);
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	VECTOR GetPos(int i,int j) { return m_sblock[i][j].GetPos(); }
	void SetBlock(int i,int j) { m_sblock[i][j].SetBlock(); }
	bool GetBlock(int i, int j) {return m_sblock[i][j].GetBlock(); }
};