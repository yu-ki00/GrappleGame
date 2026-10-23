#include"TitleScene.h"
#include"../../lib/collision/CollisionManager.h"
#include"../system/SoundManager.h"
#include"../../lib/input/PadInput.h"
#include"../../lib/input/input.h"
#include"../common.h"


//----------------------
// コンストラクタ
//----------------------
CTitleScene::CTitleScene()
{

	m_state = INIT;

}

//----------------------
// デストラクタ
//----------------------
CTitleScene::~CTitleScene()
{

	// 安全のためにデータ破棄処理を呼び出し
	Exit();

}

//------------------------
// 毎フレーム呼ぶ処理
//------------------------
int CTitleScene::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int result = 0;

	switch (m_state)
	{
	case CTitleScene::INIT:

		Init();

		m_state = CTitleScene::LOAD;  // 次へ進む

		break;

	case CTitleScene::LOAD:

		Load();

		m_state = CTitleScene::MAIN;  // 次へ進む

		break;

	case CTitleScene::MAIN:




	case CTitleScene::CONTROL:
	case CTitleScene::KEYBOARD:
		Step();

		break;
	case CTitleScene::ENDWAIT:

		m_endwait++;

		if (m_endwait >= END_WAIT) {

			m_state = CTitleScene::END;  // 次へ進む

			m_endwait = 0;

		}
		break;
	case CTitleScene::END:

		Exit();

		m_state = CTitleScene::INIT;  // 次へ進む

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
void CTitleScene::Draw()
{
	switch (m_state)
	{
	case CTitleScene::INIT:
		break;
	case CTitleScene::LOAD:
		break;
	case CTitleScene::MAIN:
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 1.0f, 0.0f, m_hndl, true);
		break;
	case CTitleScene::CONTROL:
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 1.0f, 0.0f, m_controler_hndl, true);
		break;
	case CTitleScene::KEYBOARD:
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 1.0f, 0.0f, m_keyboard_hndl, true);
		break;
	case CTitleScene::ENDWAIT:
		break;
	case CTitleScene::END:
		break;
	default:
		break;
	}


}

//----------------------
// 初期化
//----------------------
void CTitleScene::Init()
{

	m_endwait = 0;
	m_hndl = -1;
	m_keyboard_hndl = -1;
	m_controler_hndl = -1;

}

//----------------------
// データロード
//----------------------
void CTitleScene::Load()
{
	if (m_hndl == -1) {

		m_hndl = LoadGraph(TITLE_PATH);

	}
	if (m_keyboard_hndl == -1)
	{
		m_keyboard_hndl = LoadGraph(KEYBOARD_PATH);
	}
	if (m_controler_hndl == -1) {
		m_controler_hndl = LoadGraph(CONTROL_PATH);
	}



}

//----------------------
// タイトルのメイン処理
//----------------------
void CTitleScene::Step()
{

	switch (m_state)
	{
	case CTitleScene::INIT:
		break;
	case CTitleScene::LOAD:
		break;
	case CTitleScene::MAIN:
		if (CInput::IsTrg(KEY_INPUT_SPACE) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B)) {

			m_state = CONTROL;

		}
		break;
	case CTitleScene::CONTROL:
		if (CInput::IsTrg(KEY_INPUT_SPACE) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B)) {

			m_state = KEYBOARD;

		}
		break;
	case CTitleScene::KEYBOARD:
		if (CInput::IsTrg(KEY_INPUT_SPACE) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B)) {

			m_state = END;

		}
		break;
	case CTitleScene::ENDWAIT:
		break;
	case CTitleScene::END:
		break;
	default:
		break;
	}
}

//----------------------
//	終了処理
//----------------------
void CTitleScene::Exit()
{
	if (m_hndl != -1) {

		DeleteGraph(m_hndl);

		m_hndl = -1;

	}
	if (m_controler_hndl != -1) {

		DeleteGraph(m_controler_hndl);

		m_controler_hndl = -1;


	}
	if (m_keyboard_hndl != -1) {

		DeleteGraph(m_keyboard_hndl);

		m_keyboard_hndl = -1;

	}

	SoundManager::AllStop();

}