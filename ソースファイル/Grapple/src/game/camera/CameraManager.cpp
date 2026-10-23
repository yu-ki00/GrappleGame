#include"CameraManager.h"


//----------------------
// コンストラクタ
//----------------------
CameraManager::CameraManager()
{
	// 初期カメラはプレイカメラ
	m_id = ID_PLAY;
}

//----------------------
// 初期化
//----------------------
void CameraManager::Init()
{
	// それぞれのカメラを初期化

	m_Play.Init();

	m_debug.Init();

	SetCameraNearFar(30.0f, 10000.0f);

}
void CameraManager::Load() {

	m_Play.Load();

}
//----------------------
// カメラの座標計算
//----------------------
void CameraManager::Step(VECTOR forcus)
{
#ifdef DEBUG
	if (CheckHitKey(KEY_INPUT_C))
	{

		m_id = ID_DEBUG;

	}
#endif // DEBUG

	
	if (CheckHitKey(KEY_INPUT_V))
	{

		m_id = ID_PLAY;

	}

	switch (m_id)
	{
		// ゲーム中のメインカメラ
	case ID_PLAY:

		m_Play.Step(forcus);

		break;

		// デバッグ用のカメラ
	case ID_DEBUG:

		m_debug.Step();

		break;
	}
}

//----------------------
//	カメラの更新
//----------------------
void CameraManager::Update()
{
	switch (m_id)
	{
		// ゲーム中のメインカメラ

	case ID_PLAY:

		m_Play.Update();

		break;

		// デバッグ用のカメラ

	case ID_DEBUG:

		m_debug.Update();

		break;
	}

}

void CameraManager::Draw() {
	m_Play.Draw();
}