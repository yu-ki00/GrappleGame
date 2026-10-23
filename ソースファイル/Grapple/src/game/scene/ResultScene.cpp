#include"ResultScene.h"
#include"../../lib/collision/CollisionManager.h"
#include"../system/SoundManager.h"
#include"../../lib/input/input.h"
#include"../../lib/input/PadInput.h"
#include"../common.h"


//----------------------
// コンストラクタ
//----------------------
CResultScene::CResultScene()
{
	m_state = INIT;
	m_time = 0;
}

//----------------------
// デストラクタ
//----------------------
CResultScene::~CResultScene()
{
	// 安全のためにデータ破棄処理を呼び出し
	Exit();
}

//------------------------
// 毎フレーム呼ぶ処理
//------------------------
int CResultScene::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int result = 0;

	switch (m_state)
	{
	case CResultScene::INIT:

		Init();

		m_state = CResultScene::LOAD;  // 次へ進む

		break;

	case CResultScene::LOAD:

		Load();

		m_state = CResultScene::MAIN;  // 次へ進む

		break;

	case CResultScene::MAIN:

		Step();

		break;

	case CResultScene::END:

		Exit();

		m_state = CResultScene::INIT;  // 次へ進む

		result = 1;

		break;

	default:

		break;
	}

	// 本編が終了したかどうかを外部に伝える
	return result;
}

//----------------------
// 描画処理
//----------------------
void CResultScene::Draw(int clearTime)
{
	//クリアタイムの計算
	m_time = clearTime;

	int clearMilliSecond = m_time / 6;

	int clearSecond = clearMilliSecond / 10;

	int clearMinute = clearSecond / 60;

	clearSecond = clearSecond % 60;

	clearMilliSecond = clearMilliSecond % 10;

	DrawFormatString(10, 10, GetColor(255, 255, 255), "リザルト");

	//クリアタイムの描画
	DrawFormatString(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, WHITE, "%02d:%02d.%d", clearMinute, clearSecond, clearMilliSecond);

	DrawFormatString(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2+50, WHITE, "B Push");

}

//----------------------
// 初期化
//----------------------
void CResultScene::Init()
{


}

//----------------------
// データロード
//----------------------
void CResultScene::Load()
{
	if (m_hndl == -1) {

		m_hndl = LoadGraph(RESULT_PATH);

	}

}

//----------------------
// タイトルのメイン処理
//----------------------
void CResultScene::Step()
{

	if (CInput::IsTrg(KEY_INPUT_SPACE) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B)) {

		m_state = END;

	}
}

//----------------------
//	終了処理
//----------------------
void CResultScene::Exit()
{
	if (m_hndl == -1) {

		DeleteGraph(m_hndl);

		m_hndl = -1;

	}

	SoundManager::AllStop();
}