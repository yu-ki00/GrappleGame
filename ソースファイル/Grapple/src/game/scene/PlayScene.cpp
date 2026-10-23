#include"PlayScene.h"
#include"../../lib/collision/CollisionManager.h"
#include"../system/SoundManager.h"
#include"../../lib/input/input.h"
#include"../common.h"
#include"../../lib/input/PadInput.h"

//----------------------
// コンストラクタ
//----------------------
CPlayScene::CPlayScene()
{
	m_state = INIT;

	m_player.Init();

	m_goal.Init();

	m_block.Init();

	m_enemy.Init();

	m_grapple.Init();

	m_sky.Init();

	m_field.Init();

	//ステージのクリアタイム関連------
	m_clearFrame = 0;

	m_clearMilliSecond = 0;

	m_clearSecond = 0;

	m_clearMinute = 0;
	//--------------------------------

	m_LineHndl = -1;

}

//----------------------
// デストラクタ
//----------------------
CPlayScene::~CPlayScene()
{
	// 安全のためにデータ破棄処理を呼び出し
	Exit();
}

//------------------------
// 毎フレーム呼ぶ処理
//------------------------
int CPlayScene::Loop()
{
	int stagedata = Data::GetInstance()->GetStage();
	// ゲームが終了したかを外部に伝えるための値

	int result = 0;

	m_nowTime = GetNowCount();
	m_dt = (m_nowTime - m_prevTime) / 1000.0f;
	switch (m_state)
	{
	case CPlayScene::INIT:

		Init();

		m_state = CPlayScene::LOAD;  // 次へ進む
		break;

	case CPlayScene::LOAD:
		Load();
		m_state = CPlayScene::MAIN;  // 次へ進む
		break;

	case CPlayScene::MAIN:
	{
		bool active = false;

		Step();
		break;

	}
	case CPlayScene::END:
		Exit();
		m_state = CPlayScene::INIT;  // 次へ進む
		result = 1;
		break;
	case CPlayScene::RETURN:
		m_state = CPlayScene::INIT;
		result = 2;
		break;
	default:
		break;
	}
	m_prevTime = GetNowCount();
	// 本編が終了したかどうかを外部に伝える
	return result;
}

//----------------------
// 描画処理
//----------------------
void CPlayScene::Draw()
{
	switch (m_state)
	{
	case CPlayScene::INIT:
		break;
	case CPlayScene::LOAD:
		break;
	case CPlayScene::MAIN: {
		m_sky.Draw();

		m_field.Draw();

		m_shot.Draw();

		m_goal.Draw();

		m_enemy.Draw();

		m_block.Draw();

		m_grapple.Draw();

		m_player.Draw();
		VECTOR plspeed = m_player.GetVelocity();

		plspeed.y = 0.0f;
		float speed = VSize(plspeed);
		//プレイヤーが一定のスピード以上になったら集中線を出す
		if (speed >= 160)
			if (m_player.GetVelocity().y > 20) {

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);

				DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 1.0f, 0.0f, m_LineHndl, true);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}

		if (m_camera.GetID() == CameraManager::ID_PLAY)
			m_camera.Draw();
		DrawFormatString(750, 30, WHITE, "%02d:%02d.%d", m_clearMinute, m_clearSecond, m_clearMilliSecond);

#ifdef DEBUG
		DrawLine3D(m_camera.GetTarget(), VAdd(m_camera.GetTarget(), VScale(m_camera.GetVec(), LENGTH)), RED);

		DrawFormatString(10, 100, RED, "%.2f,%f,%.2f", m_player.GetPos().x, m_player.GetPos().y, m_player.GetPos().z);

		VECTOR ancpos = m_grapple.GetAncPos();

		DrawFormatString(10, 200, RED, "%.2f,%.2f,%.2f", ancpos.x, ancpos.y, ancpos.z);

		if (m_grapple.GetHit2()) {

			ancpos = m_grapple.GetTarget2();

		}

		DrawSphere3D(m_grapple.GetTarget2(), 30, 16, GREEN, GREEN, false);

		DrawFormatString(10, 300, RED, "%.2f,%.2f,%.2f", m_grapple.GetTarget2().x, m_grapple.GetTarget2().y, m_grapple.GetTarget2().z);

		if (CCollisionManager::CheckReleaseRopeToBlock(m_grapple, m_block, m_player)) {

			DrawFormatString(10, 400, RED, "HIT");

		}
		if (m_player.GetGround())

			DrawFormatString(10, 400, RED, "hit");

#endif // DEBUG
	}
						 break;
	case CPlayScene::END:
		break;
	default:
		break;
	}
}


//----------------------
// 初期化
//----------------------
void CPlayScene::Init()
{
	m_clearTime = 0;

	m_clearFrame = 0;

	m_clearMilliSecond = 0;

	m_clearSecond = 0;

	m_clearMinute = 0;

	m_enemy.Init();

	m_shot.Init();

	m_player.Init();

	m_camera.Init();

	m_grapple.Init();

	m_sky.Init();

	m_field.Init();

	m_block.Init();

	m_goal.Init();

}

//----------------------
// データロード
//----------------------
void CPlayScene::Load()
{
	m_field.Load();

	m_block.Load(m_field.GetHndl());

	m_camera.Load();

	m_shot.Load();

	m_goal.Load(m_field.GetGoalPos());

	m_grapple.Load();

	m_player.Load();

	m_sky.Load();

	m_enemy.Load();

	m_LineHndl = LoadGraph("Data/graphics/line.png");

}

//----------------------
// ゲームのメイン処理
//----------------------
void CPlayScene::Step()
{

	m_clearTime++;

	m_clearFrame++;

	if (m_clearFrame == 6) {

		m_clearMilliSecond++;

		m_clearFrame = 0;

	}
	if (m_clearMilliSecond == 10) {

		m_clearSecond++;

		m_clearMilliSecond = 0;

	}
	if (m_clearSecond == 60) {

		m_clearMinute++;

		m_clearSecond = 0;

	}
	m_grapple.Step(m_player.GetHndl(), m_block);

	if (m_camera.GetID() == m_camera.ID_PLAY) {

		VECTOR ancpos = m_grapple.GetAncPos();

		if (!m_grapple.GetHit2())

			CCollisionManager::CheckHitRopeToField(m_player, m_field, m_block, m_grapple, &ancpos);

		if (m_grapple.GetHit2() && CCollisionManager::CheckReleaseRopeToBlock(m_grapple, m_block, m_player)) {

			ancpos = m_grapple.GetTarget2();

		}
		else {

			m_grapple.SetHit2(false);

		}

		m_player.Step(m_camera.GetRot(), m_dt, ancpos, m_grapple.IsShot(), m_grapple);

	}

	m_sky.Step(m_player.GetPos());


	m_enemy.Step(m_player.GetCenter(), m_shot,  m_grapple.IsShot());

	m_shot.Step(m_player.GetCenter());

	m_camera.Step(m_player.GetPos());

	m_block.Step();

	auto& whiteBlocks = m_block.GetWhite();

	for (int i = 0; i < whiteBlocks.size(); i++) {

		CAnchorBlock& oneblock = whiteBlocks[i];
		if (oneblock.GetHit()) {

			if (CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_RB) || CMouse::IsKeep(MOUSE_INPUT_LEFT)) {

				m_grapple.RequestShot(oneblock.GetPos());

				m_block.SetAncHit(true, i);

				SoundManager::Play(SoundManager::SE_PLSHOT, DX_PLAYTYPE_BACK);

			}
		}
	}

	CCollisionManager::CheckHitPlayerToBlock(m_player, m_block, m_grapple);

	CCollisionManager::CheckHitPlayerToShot(m_player, m_shot, m_grapple, m_block);

	int block_index = 0;

	if (CCollisionManager::CheckHitReticuleToBlock(m_camera, m_block, m_player, m_field, &block_index)) {

		m_block.SetHit(true, block_index);

		m_camera.ReticuleHit(true);

	}

	CCollisionManager::CheckHitPlayerToField(m_player, m_field);

	CCollisionManager::CheckHitShotToField(m_field, m_block, m_shot);

	m_goal.Update();

	m_block.Update();

	m_player.Update();

	m_camera.Update();

	m_shot.Update();

	m_enemy.Update();

	m_field.Update();

	m_grapple.Update();

	m_sky.Update();




	if (CCollisionManager::CheckHitPlayerToGoal(m_player, m_goal)) {

		m_state = END;


	}
	if (m_player.GetPos().y <= KILL_Y) {

		ResetGame();

	}
}

//----------------------
//	終了処理
//----------------------
void CPlayScene::Exit()
{
	m_player.Exit();

	m_grapple.Exit();

	m_shot.Exit();

	m_enemy.Exit();

	m_block.Exit();

	m_goal.Exit();

	m_sky.Exit();

	m_field.Exit();

	DeleteGraph(m_LineHndl);

	SoundManager::AllStop();

}
void CPlayScene::ResetGame() {

	m_player.Reset();

	m_enemy.Reset();

	m_grapple.OutShot();

	m_camera.Reset();

}