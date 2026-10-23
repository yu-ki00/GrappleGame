#include"Player.h"
#include"../../lib/input/PadInput.h"
#include"../../lib/input/input.h"
#include"../../lib/MyMath/MyMath.h"
#include"../../lib/collision/CollisionManager.h"
#include"string.h"

using namespace std;

CPlayer::CPlayer() {

	Init();

}
//初期化
void CPlayer::Init() {

	m_size = PLAYER_SIZE;

	m_velocity = ZERO;

	m_Accel = 0.0f;

	m_isGround = false;

	m_pos = START_POS;


}
//モデルのロード
void CPlayer::Load() {
	if (m_hndl == -1) {

		m_hndl = MV1LoadModel(PLAYER_PATH);

	}

	RequestAnimLoop(WAIT, ANIM_SPD);
}
//毎フレーム呼び出す処理
void CPlayer::Step(VECTOR camera_rot, float dt, VECTOR ancpos, bool isShot, CGrapple& grapple) {

	VECTOR vec = ZERO;

	vec = VSub(m_pos, ancpos);

	float len = VSize(vec);

	vec = VNorm(vec);

	grapple.GetPos();

	if (isShot == true) {
		//紐を縮める

		if (CInput::IsRep(KEY_INPUT_E) || CGamePad::IsPadKeep(DX_INPUT_PAD1, BUTTON_X)) {

			m_pos = VSub(m_pos, VScale(vec, 3));

		}
		//紐を伸ばす
		if ((CInput::IsRep(KEY_INPUT_Q) || CGamePad::IsPadKeep(DX_INPUT_PAD1, BUTTON_Y)) && len <= 300) {

			m_pos = VAdd(m_pos, VScale(vec, 3));

		}
	}

	float ropelength = VSize(VSub(m_pos, ancpos));

	m_speed = ZERO;

	//常にカメラが向いているほうを向く

	m_rot.y = camera_rot.y;

	if (isShot == true) {
		GrappleJump();
		MoveSwing(ancpos, dt, ropelength);
		if (m_state != GRAPPLE) {
			m_state = GRAPPLE;
			RequestAnimLoop(m_state, ANIM_SPD);
		}

		//ショットボタンを離すと慣性ジャンプ
		if (CGamePad::IsPadRelease(DX_INPUT_PAD1, BUTTON_RB) || CMouse::IsRelease(MOUSE_INPUT_LEFT)) {
			grapple.OutShot();
			//慣性ジャンプ===============================================

			VECTOR dir = VSub(m_pos, ancpos);

			float dist = VSize(dir);

			dir = VScale(dir, 1.0f / dist);

			//接線方向

			float velAlong = VDot(m_velocity, dir);

			VECTOR tangent = VSub(m_velocity, VScale(dir, velAlong));

			//接線を正規化してブースト

			tangent = VNorm(tangent);

			m_velocity = VAdd(m_velocity, VScale(tangent, INERTIAL_BOOST*1));
			if (m_velocity.y >= 300) {

				m_velocity.y = 300;
			}
			//===========================================================
		}
	}
	else {
		bool isMove = MoveExec(dt);
		if (isMove && m_state != WALK) {

			m_state = WALK;

			RequestAnimLoop(m_state, ANIM_SPD);
		}
		else if (!isMove && m_state != WAIT) {

			m_state = WAIT;

			RequestAnimLoop(m_state, ANIM_SPD);

		}
	}
	UpdateAnim();

}

//モデルの描画
void CPlayer::Draw() {

	MV1DrawModel(m_hndl);

}



//プレイヤーの中心座標
VECTOR CPlayer::GetCenter() {

	VECTOR center = m_pos;

	center.y = m_pos.y + (m_size.y / 2);

	return center;

}
//プレイヤー移動処理
bool CPlayer::MoveExec(float dt) {

	m_speed = ZERO;
	//加速度
	float ACCEL = 0.0f; 

	//入力方向
	float move_vec = 0.0f;

	//移動中かどうか
	bool isMove = false;


	if (CGamePad::Stick(STICK_LX_POS) != 0
		|| CGamePad::Stick(STICK_LX_NEG) != 0
		|| CGamePad::Stick(STICK_LY_POS) != 0
		|| CGamePad::Stick(STICK_LY_NEG) != 0) {

		ACCEL = -MOVE_ACCEL;

		move_vec = CGamePad::StickRot(STICK_LEFT);

	}
	if (CInput::IsRep(KEY_INPUT_W) && CInput::IsRep(KEY_INPUT_D)) {

		ACCEL = -MOVE_ACCEL;

		float move_deg = 45.0f;

		move_vec = CMyMath::DegRad(move_deg);


	}
	else if (CInput::IsRep(KEY_INPUT_W) && CInput::IsRep(KEY_INPUT_A)) {

		ACCEL = MOVE_ACCEL;

		float move_deg = 135.0f;

		move_vec = CMyMath::DegRad(move_deg);
	}

	else if (CInput::IsRep(KEY_INPUT_S) && CInput::IsRep(KEY_INPUT_D)) {

		ACCEL = -MOVE_ACCEL;

		float move_deg = 135.0f;

		move_vec = CMyMath::DegRad(move_deg);

	}

	else if (CInput::IsRep(KEY_INPUT_S) && CInput::IsRep(KEY_INPUT_A)) {

		ACCEL = MOVE_ACCEL;

		float move_deg = 45.0f;

		move_vec = CMyMath::DegRad(move_deg);

	}

	else if (CInput::IsRep(KEY_INPUT_W))
	{

		ACCEL = -MOVE_ACCEL;
	}

	else if (CInput::IsRep(KEY_INPUT_S))
	{
		ACCEL = MOVE_ACCEL;
	}

	else if (CInput::IsRep(KEY_INPUT_D))
	{
		ACCEL = -MOVE_ACCEL;

		float move_deg = 90.0f;

		move_vec = CMyMath::DegRad(move_deg);

	}

	else if (CInput::IsRep(KEY_INPUT_A))
	{
		ACCEL = MOVE_ACCEL;

		float move_deg = 90.0f;

		move_vec = CMyMath::DegRad(move_deg);

	}
	if (ACCEL != 0) {
		isMove = true;
	}

	//入力方向に加速
	m_speed.x += (sinf(m_rot.y + move_vec) * ACCEL);

	m_speed.y = 0.0f;

	m_speed.z += (cosf(m_rot.y + move_vec) * ACCEL);

	//ジャンプ処理
	JumpExec();


	//空中での処理
	if (!m_isGround) {

		m_velocity.y -= G * dt;

		//空中制御
		//入力方向ベクトル
		VECTOR wishDir = VNorm(VGet(m_speed.x, 0.0f, m_speed.z));

		//希望移動ベクトル
		float wishSpeed = VSize(VGet(m_speed.x, 0.0f, m_speed.z));

		if (wishSpeed > 0.0f) {

			//現在の速度の入力方向成分
			float currentSpeed = VDot(m_velocity, wishDir);


			//追加可能な速度
			float addSpeed = wishSpeed - currentSpeed;

			if (addSpeed > 0.0f) {

				//空中加速度
				float airAccel = AIR_ACCEL;

				//加速度
				float accelSpeed = airAccel * dt * AIR_CONTROL;

				//加速制限
				if (accelSpeed > addSpeed)

					accelSpeed = addSpeed;

				//加速
				m_velocity = VAdd(m_velocity, VScale(wishDir, accelSpeed));
			}
		}


	}
	else {
		//地上では摩擦を受ける
		m_speed.y = 0.0f;

		m_velocity.x -= m_velocity.x * FRICTION * dt;

		m_velocity.z -= m_velocity.z * FRICTION * dt;

		m_velocity.x += m_speed.x * dt;

		m_velocity.z += m_speed.z * dt;

	}

	//水平方向への速度の取得
	VECTOR horiz = VGet(m_velocity.x, 0.0f, m_velocity.z);

	float speed = VSize(horiz);

	//速度を制限する
	if (speed > MAX_SPEED) {

		VECTOR limited = VScale(VNorm(horiz), MAX_SPEED);

		m_velocity.x = limited.x;

		m_velocity.z = limited.z;

	}

	//位置更新
	m_pos = VAdd(m_pos, VScale(m_velocity, dt));

	return isMove;

}

//ジャンプ処理
void CPlayer::JumpExec() {
	if ((CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_A) || CInput::IsTrg(KEY_INPUT_SPACE)) && m_isGround) {

		//Aボタンを押したらジャンプ
		m_velocity.y = JUMP_SPEED;

	}
}

void CPlayer::GrappleJump() {
	if ((CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_A) || CInput::IsTrg(KEY_INPUT_SPACE)) && m_isGround) {

		//Aボタンを押したらジャンプ
		m_velocity.y = 200;

	}
}
//グラップル移動
void CPlayer::MoveSwing(VECTOR ancpos, float dt, float ropelength) {
	const float accel = 200.0f;

	// スイング中の重力
	m_velocity.y -= GG * dt;

	// 位置更新
	m_pos = VAdd(m_pos, VScale(m_velocity, dt));

	VECTOR diff = VSub(m_pos, ancpos);

	float dist = VSize(diff);

	if (dist < 0.0001f)
		return;

	VECTOR dir = VScale(diff, 1.0f / dist);

	// ロープ長制約（位置）
	if (dist > ropelength)
	{
		m_pos = VAdd(ancpos, VScale(dir, ropelength));
	}

	// 張力（ロープ方向速度の除去）
	float vAlong = VDot(m_velocity, dir);
	if (vAlong > 0.0f)
	{
		m_velocity = VSub(m_velocity, VScale(dir, vAlong));
	}

	// スティック入力
	float stick = CGamePad::StickRotX(STICK_LEFT);
	if (CInput::IsRep(KEY_INPUT_A)) {
		stick = -1;
	}
	else if (CInput::IsRep(KEY_INPUT_D)) {
		stick = 1;
	}

	// 入力立ち上がり検出（初動ブースト）
	static float prevStick = 0.0f;
	bool justPressed =
		fabsf(stick) > 0.2f &&
		fabsf(prevStick) <= 0.2f;
	prevStick = stick;

	if (justPressed)
	{
		// 左右方向接線ベクトル（ワールド上方向基準）
		VECTOR tangent = VNorm(VCross(dir, VECTOR{ 0.0f,1.0f,0.0f }));

		m_velocity = VAdd(m_velocity, VScale(tangent, stick * 3.0f));
	}

	// 入力中の継続横揺れ
	if (fabsf(stick) > 0.1f)
	{
		VECTOR tangent = VNorm(VCross(dir, VECTOR{ 0.0f,1.0f,0.0f }));
		m_velocity = VAdd(m_velocity, VScale(tangent, stick * accel * dt * 0.4f));
	}

	// 通常の横操作（姿勢調整）
	float speed = VSize(m_velocity);

	if (speed > 0.0001f && fabsf(stick) > 0.01f)
	{
		VECTOR planeN = VCross(dir, m_velocity);
		float nlen = VSize(planeN);
		if (nlen > 0.0001f)
		{
			planeN = VScale(planeN, 1.0f / nlen);

			float rot = stick * 1.5f * dt;
			if (rot < -0.08f) rot = -0.08f;
			if (rot > 0.08f) rot = 0.08f;
			VECTOR vel =
				VAdd(
					VScale(m_velocity, cosf(rot)),
					VScale(VCross(planeN, m_velocity), sinf(rot))
				);
			m_velocity = VScale(VNorm(vel), speed);
		}
	}

}
//プレイヤーを最初の状態に戻す
void CPlayer::Reset() {

	m_pos = START_POS;

	m_rot = ZERO;

	m_velocity = ZERO;

}

void CPlayer::RequestAnim(int animID, float animSpd) {
	DetachAnim();

	m_animData.m_hndl = MV1AttachAnim(m_hndl, animID);
	m_animData.m_id = animID;

	m_animData.m_endFrame = MV1GetAnimTotalTime(m_hndl, animID);

	m_animData.m_frame = 0.0f;

	m_animData.m_speed = animSpd;

	m_animData.m_state = ANIMSTATE_NORMAL;
}

void CPlayer::RequestAnimLoop(int animID, float animSpd) {

	DetachAnim();

	m_animData.m_hndl = MV1AttachAnim(m_hndl, animID);

	m_animData.m_id = animID;

	m_animData.m_endFrame = MV1GetAnimTotalTime(m_hndl, animID);

	m_animData.m_frame = 0.0f;

	m_animData.m_speed = animSpd;

	m_animData.m_state = ANIMSTATE_LOOP;
}

void CPlayer::DetachAnim() {
	if (m_animData.m_hndl != -1) {

		MV1DetachAnim(m_hndl, m_animData.m_hndl);

		m_animData.m_hndl = -1;
	}
}

void CPlayer::UpdateAnim() {

	if (m_animData.m_hndl != -1) {

		m_animData.m_frame += m_animData.m_speed;

		if (m_animData.m_frame >= m_animData.m_endFrame) {
			//最終フレームまで来たら、状態に合わせて動作を変える
			switch (m_animData.m_state)
			{
			case ANIMSTATE_NORMAL:

				DetachAnim();

				m_animData.m_endFrame = 0.f;

				m_animData.m_frame = 0.0f;

				m_animData.m_speed = 0.0f;

				break;
			case ANIMSTATE_LOOP:

				m_animData.m_frame = 0.0f;

				break;
			case ANIMSTATE_END:

				m_animData.m_frame = m_animData.m_endFrame;

				break;
			default:
				break;
			}
		}

		MV1SetAttachAnimTime(m_hndl, m_animData.m_hndl, m_animData.m_frame);
	}
}