#pragma once
#include<DxLib.h>
#include "Enemy.h"
#include"../../lib/Data/Data.h"
#include<vector>
using namespace std;
//定義関連--------------------------------
static const char ENEMY_MODEL_PATH[] = { "Data/Model/enemy/source/enemy.mv1" };
static const int ENEMY_NUM = 2;
//----------------------------------------


class CEnemyManager {
private:
	//プレイヤーのショット
	CEnemy m_enemy[ENEMY_NUM];
	vector<vector<VECTOR>> m_enemyPosList;

public:
	CEnemyManager();

	~CEnemyManager();

	//初期化
	void Init();

	//モデルロード
	void Load();

	void LoadCSV(const char* filename);

	//最後に動かす処理
	void Exit();

	//更新処理
	void Update();

	//毎フレーム動く処理
	void Step(VECTOR plpos, CShotManager& shot, bool isShot);

	//モデル描画
	void Draw();

	//一体一体のエネミーの取得
	CEnemy& GetEnemy(int id) { return m_enemy[id]; }

	//位置情報などの諸々をリセット
	void Reset();
};