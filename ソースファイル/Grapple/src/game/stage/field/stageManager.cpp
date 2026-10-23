#include"stageManager.h"
static const char STAGE_BLOCK_PATH[] = "Data/Model/block/normal.mv1";

void CStageManager::Init(int stage) {
	for (int i = 0; i < STAGE_X; i++) {
		for (int j = 0; j < STAGE_Z; j++) {
			m_sblock[i][j].Init();
		}
	}
	if (stage == 1) {
		for (int i = 0; i < STAGE_X; i++) {
			for (int j = 0; j < STAGE_Z; j++) {
				if (j >= 8 && j <= 70) {
				}
				else
					m_sblock[i][j].SetBlock();
				m_sblock[i][j].SetPos(VGet(i * 20 + 10, -10, j * 20 + 10));
				if (i == 0 || i == 19) {
					m_sblock[i][j].SetPos(VGet(i * 20 + 10, 10, j * 20 + 10));
				}
			}
		}
	}
	else if (stage == 2) {
		for (int i = 0; i < STAGE_X; i++) {
			for (int j = 0; j < STAGE_Z; j++) {
				if (j >= 8 && j <= 70) {
				}
				else
					m_sblock[i][j].SetBlock();
				m_sblock[i][j].SetPos(VGet(i * 20 + 10, -10, j * 20 + 10));
				if (i == 0 || i == 19) {
					m_sblock[i][j].SetPos(VGet(i * 20 + 10, 10, j * 20 + 10));
				}
				if (j > 70) {
					m_sblock[i][j].SetPos(VGet(i * 20 + 10, 790, j * 20 + 10));
				}
			}
		}
	}
	else if (stage == 3) {
		for (int i = 0; i < STAGE_X; i++) {
			for (int j = 0; j < STAGE_Z; j++) {
				if (j >= 8 && j <= 70) {
				}
				else
					m_sblock[i][j].SetBlock();
				m_sblock[i][j].SetPos(VGet(i * 20 + 10, -10, j * 20 + 10));
				if (i == 0 || i == 19) {
					m_sblock[i][j].SetPos(VGet(i * 20 + 10, 10, j * 20 + 10));
				}
			}
		}
	}
}
void CStageManager::Load() {
	int hndl = MV1LoadModel(STAGE_BLOCK_PATH);
	for (int i = 0; i < STAGE_X; i++) {
		for (int j = 0; j < STAGE_Z; j++) {
			m_sblock[i][j].Load(hndl);


		}
	}
	MV1DeleteModel(hndl);
}
void CStageManager::Step() {
	for (int i = 0; i < STAGE_X; i++) {
		for (int j = 0; j < STAGE_Z; j++) {
			m_sblock[i][j].Step();
		}
	}
}
void CStageManager::Draw() {
	for (int i = 0; i < STAGE_X; i++) {
		for (int j = 0; j < STAGE_Z; j++) {
			if (m_sblock[i][j].GetBlock()) {
				m_sblock[i][j].Draw();
			}
		}
	}
}
void CStageManager::Update() {
	for (int i = 0; i < STAGE_X; i++) {
		for (int j = 0; j < STAGE_Z; j++) {
			m_sblock[i][j].Update();
		}
	}
}
void CStageManager::Exit() {
	for (int i = 0; i < STAGE_X; i++) {
		for (int j = 0; j < STAGE_Z; j++) {
			m_sblock[i][j].Exit();
		}
	}
}