#include"EnemyManager.h"



CEnemyManager::CEnemyManager() {
	Init();
}
CEnemyManager::~CEnemyManager() {
	Exit();
}
void CEnemyManager::Init() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_enemy[i].Init();
	}
}
void CEnemyManager::Load() {

	int stagedata = Data::GetInstance()->GetStage();

	//ファイル読み込み
	LoadCSV("Data/StageData/Enemypos.csv");

	int stageindex = stagedata - 1;

	int hndl = MV1LoadModel(ENEMY_MODEL_PATH);

	for (int i = 0; i < ENEMY_NUM; i++) {

		m_enemy[i].Load(hndl);

		if (stageindex < m_enemyPosList.size() &&
			i < m_enemyPosList[stageindex].size()) {

			m_enemy[i].SetActive(true);

			m_enemy[i].SetPos(m_enemyPosList[stageindex][i]);

		}
		else {

			m_enemy[i].SetActive(false);
		}

	}

	MV1DeleteModel(hndl);
}

void CEnemyManager::LoadCSV(const char* filename) {
	//既存のデータをクリア
	m_enemyPosList.clear();

	int hndl = FileRead_open(filename);
	//読み込みが失敗したら終了
	if (hndl == 0) {
		return;
	}

	char line[256];

	FileRead_gets(line, sizeof(line), hndl);

	//1行ずつ読む
	while (FileRead_gets(line, sizeof(line), hndl) != NULL) {
		
		int stage;
		float x, y, z;

		//CSV読み取り
		if (sscanf_s(line, "%d,%f,%f,%f", &stage, &x, &y, &z) != 4) {
			continue;//読み取り失敗はスキップ
		}

		if (m_enemyPosList.size() < stage) {

			m_enemyPosList.resize(stage);
		}

		//座標追加
		m_enemyPosList[stage - 1].push_back(VGet(x, y, z));
	}
	FileRead_close(hndl);

}
void CEnemyManager::Step(VECTOR plpos, CShotManager& shot, bool isShot) {
	for (int i = 0; i < ENEMY_NUM; i++)

		m_enemy[i].Step(plpos, shot,  isShot);

}

void CEnemyManager::Draw() {

	for (int i = 0; i < ENEMY_NUM; i++) {

		m_enemy[i].Draw();

	}

}

void CEnemyManager::Update() {

	for (int i = 0; i < ENEMY_NUM; i++) {

		m_enemy[i].Update();

	}
}
void CEnemyManager::Exit() {

	for (int i = 0; i < ENEMY_NUM; i++)

		m_enemy[i].Exit();

}

void CEnemyManager::Reset() {

	for (int i = 0; i < ENEMY_NUM; i++) {

		m_enemy[i].Reset();

	}
}