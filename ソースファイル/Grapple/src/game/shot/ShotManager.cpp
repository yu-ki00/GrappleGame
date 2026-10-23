#include"ShotManager.h"
#include"../System/SoundManager.h"

CShotManager::CShotManager() {

}
CShotManager::~CShotManager() {

}
void CShotManager::Init() {
	for (int i = 0; i < SHOT_NUM; i++) {
		m_shot[i].Init();
	}
}
void CShotManager::Load() {

	int hndl = MV1LoadModel(PLSHOT_MODEL_PATH);

	for (int i = 0; i < SHOT_NUM; i++) {

		m_shot[i].Load(hndl);
	}
	MV1DeleteModel(hndl);
}
void CShotManager::Step( VECTOR plpos) {

	for (int i = 0; i < SHOT_NUM; i++)
		m_shot[i].Step(plpos);

}
void CShotManager::Draw() {

	for (int i = 0; i < SHOT_NUM; i++)
		m_shot[i].Draw();

}
void CShotManager::Update() {

	for (int i = 0; i < SHOT_NUM; i++)
		m_shot[i].Update();

}
void CShotManager::Exit() {

	for (int i = 0; i < SHOT_NUM; i++)
		m_shot[i].Exit();

}
void CShotManager::RequestShot(const VECTOR& pos, const VECTOR& speed, const VECTOR& rot) {

	for (int i = 0; i < SHOT_NUM; i++) {
		if (m_shot[i].RequestShot(pos, speed, rot)) {
			break;
		}
	}
}