#pragma once
#include"block.h"
#include"anchor_block.h"
#include"damage_block.h"
#include<DxLib.h>
#include"../../lib/Data/Data.h"
#include<iostream>
#include <fstream> 
#include <sstream>
#include <string>  
#include <vector>  
#include <cstdlib> 

using namespace std;

static const char BLUE_BLOCK_PATH[] = "Data/Model/block/block.mv1";
static const char RED_BLOCK_PATH[] = "Data/Model/block/red.mv1";
static const char WHITE_BLOCK_PATH[] = "Data/Model/block/white.mv1";
enum Blocktag {
	BLUE_BLOCK,
	WHITE_BLOCK,
	RED_BLOCK,

	BLOCK_NUM
};
struct BLOCK_DATA
{
	int stage;
	Blocktag type;
	VECTOR pos;
};
class CBlockManager {
private:
	int m_stage;
	vector<CBlock> m_block;
	vector<CDamageBlock> m_damaBlock;
	vector<CAnchorBlock> m_ancBlock;

	vector<BLOCK_DATA> m_blockData;
public:
	void Init();
	void LoadCSV(const char* filename, int stage_num);
	void Load(int stagehndl);
	void Step();
	void Update();
	void Draw();
	void Exit();
	bool GetHit(int i) { return m_ancBlock[i].GetHit(); }
	void SetHit(bool hit, int i) { m_ancBlock[i].SetHit(hit); }
	bool GetAncHit(int i) { return m_ancBlock[i].GetAncHit(); }
	void SetAncHit(bool hit, int i) { m_ancBlock[i].SetAncHit(hit); }
	vector<CBlock>& GetBlue() { return m_block; }
	vector<CDamageBlock>& GetRed() { return m_damaBlock; }
	vector<CAnchorBlock>& GetWhite() { return m_ancBlock; }
};