#include"SelectScene.h"
#include"../../lib/collision/CollisionManager.h"
#include"../system/SoundManager.h"
#include"../../lib/input/PadInput.h"
#include"../../lib/input/input.h"
#include"../common.h"

//----------------------
// コンストラクタ
//----------------------
CSelectScene::CSelectScene()
{
	m_state = INIT;
}

//----------------------
// デストラクタ
//----------------------
CSelectScene::~CSelectScene()
{
	// 安全のためにデータ破棄処理を呼び出し
	Exit();
}

//------------------------
// 毎フレーム呼ぶ処理
//------------------------
int CSelectScene::Loop(int clearTime)
{
	// ゲームが終了したかを外部に伝えるため
	int result = 0;

	switch (m_state)
	{
	case CSelectScene::INIT:

		Init(clearTime);

		m_state = CSelectScene::LOAD;  // 次へ進む

		break;

	case CSelectScene::LOAD:

		Load();

		m_state = CSelectScene::MAIN;  // 次へ進む

		break;
	case CSelectScene::STARTWAIT:

		m_state = CSelectScene::MAIN;  // 次へ進む

		break;
	case CSelectScene::MAIN:

		Step();

		break;

	case CSelectScene::SELECT_1:

		Exit();

		m_state = CSelectScene::INIT;  // 次へ進む

		result = 1;

		break;
	case CSelectScene::SELECT_2:

		Exit();

		m_state = CSelectScene::INIT;  // 次へ進む

		result = 2;

		break;

	case CSelectScene::SELECT_3:

		Exit();

		m_state = CSelectScene::INIT;  // 次へ進む

		result = 3;

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
void CSelectScene::Draw()
{



	if (m_select == STAGE_1) {
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2 - 100, 0.7f, 0.0f, m_hndl[m_select], true);
		int clearMilliSecond = (int)m_highScore[0] / 6;

		int clearSecond = clearMilliSecond / 10;

		int clearMinute = clearSecond / 60;

		clearSecond = clearSecond % 60;

		clearMilliSecond = clearMilliSecond % 10;

		DrawFormatString(750, 700, WHITE, "%d:%02d:%d", clearMinute, clearSecond, clearMilliSecond);

	}
	else if (m_select == STAGE_2) {
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2 - 100, 0.7f, 0.0f, m_hndl[m_select], true);
		int clearMilliSecond = (int)m_highScore[1] / 6;

		int clearSecond = clearMilliSecond / 10;

		int clearMinute = clearSecond / 60;

		clearSecond = clearSecond % 60;

		clearMilliSecond = clearMilliSecond % 10;

		DrawFormatString(750, 700, WHITE, "%d:%02d:%d", clearMinute, clearSecond, clearMilliSecond);

	}
	else if (m_select == STAGE_3) {
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2 - 100, 0.7f, 0.0f, m_hndl[m_select], true);
		int clearMilliSecond = (int)m_highScore[2] / 6;

		int clearSecond = clearMilliSecond / 10;

		int clearMinute = clearSecond / 60;

		clearSecond = clearSecond % 60;

		clearMilliSecond = clearMilliSecond % 10;

		DrawFormatString(750, 700, WHITE, "%d:%02d:%d", clearMinute, clearSecond, clearMilliSecond);

	}
	DrawFormatString(730, 650, WHITE, "ステージ%d", m_select + 1);
	DrawFormatString(750, 750, WHITE, "B Push");
	DrawTriangle(100, 350, 200, 275, 200, 425, WHITE, true);
	DrawTriangle(1500, 350, 1400, 275, 1400, 425, WHITE, true);
	DrawFormatString(10, 10, WHITE, "ステージセレクト");


}

//----------------------
// 初期化
//----------------------
void CSelectScene::Init(int clearTime)
{

	if (clearTime <= 0) {

		for (int i = 0; i < 3; i++) {

			m_highScore[i] = 0;

		}
	}
	if (m_select == STAGE_1) {

		if (clearTime < m_highScore[0] || m_highScore[0] == 0) {

			m_highScore[0] = (float)clearTime;

		}
	}
	else if (m_select == STAGE_2) {

		if (clearTime < m_highScore[1] || m_highScore[1] == 0) {

			m_highScore[1] = (float)clearTime;

		}
	}
	else if (m_select == STAGE_3) {

		if (clearTime < m_highScore[2] || m_highScore[2] == 0) {

			m_highScore[2] = (float)clearTime;

		}
	}
	for (int i = 0; i < STAGE_NUM; i++) {
		m_hndl[i] = -1;
	}
	m_select = STAGE_1;
}

//----------------------
// データロード
//----------------------
void CSelectScene::Load()
{
	if (m_hndl[0] == -1) {

		for (int i = 0; i < STAGE_NUM; i++) {
			m_hndl[i] = LoadGraph(StageHndlPath[i]);
		}

	}

}

//----------------------
// タイトルのメイン処理
//----------------------
void CSelectScene::Step()
{

	if (CGamePad::IsPush_Cross(RIGHT) || CInput::IsTrg(KEY_INPUT_D)) {

		switch (m_select)
		{
		case CSelectScene::STAGE_1:

			m_select = STAGE_2;

			break;

		case CSelectScene::STAGE_2:

			m_select = STAGE_3;

			break;

		case CSelectScene::STAGE_3:

			m_select = STAGE_1;

			break;

		default:
			break;
		}
	}
	if (CGamePad::IsPush_Cross(LEFT) || CInput::IsTrg(KEY_INPUT_A)) {
		switch (m_select)
		{
		case CSelectScene::STAGE_1:

			m_select = STAGE_3;

			break;

		case CSelectScene::STAGE_2:

			m_select = STAGE_1;

			break;

		case CSelectScene::STAGE_3:

			m_select = STAGE_2;

			break;

		default:
			break;
		}
	}
	if (CInput::IsTrg(KEY_INPUT_SPACE) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B)) {
		switch (m_select)
		{
		case CSelectScene::STAGE_1:

			m_state = SELECT_1;

			break;

		case CSelectScene::STAGE_2:

			m_state = SELECT_2;

			break;

		case CSelectScene::STAGE_3:

			m_state = SELECT_3;

			break;

		default:
			break;
		}
	}

}

//----------------------
//	終了処理
//----------------------
void CSelectScene::Exit()
{
	for (int i = 0; i < STAGE_NUM; i++) {
		if (m_hndl[0] != -1) {

			DeleteGraph(m_hndl[i]);

			m_hndl[i] = -1;

		}
	}
	SoundManager::AllStop();
}