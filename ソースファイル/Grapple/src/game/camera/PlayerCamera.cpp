#include"PlayerCamera.h"
#include<math.h>
#include"../../lib/input/PadInput.h"
#include"../../lib/MyMath/MyMath.h"
#include"../common.h"
#include"../../lib/collision/CollisionManager.h"



//----------------------
// コンストラクタ
//----------------------
PlayCamera::PlayCamera()
{
	m_camPos = ZERO;

	m_targetPos = ZERO;

	m_UpVec = ZERO;

	m_rot = ZERO;

	m_reticuleHit = false;

	m_hndl = -1;

	m_hndl2 = -1;

}

//----------------------
// 初期化
//----------------------
void PlayCamera::Init()
{
	m_camPos = { 0.0f,CAMERA_OFFSET_Y,0.0f };

	m_targetPos = ZERO;

	m_rot = { 0.0f,DX_PI_F,0.0f };

	m_UpVec = { 0.0f,1.0f,0.0f };

	m_reticuleHit = false;

	m_hndl = -1;

	m_hndl2 = -1;

	SetMousePoint(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2);

}
void PlayCamera::Load() {

	m_hndl = LoadGraph("Data/graphics/cross2.png");

	m_hndl2 = LoadGraph("Data/graphics/hitcross.png");
}
//----------------------
//	ニアーファー設定
//----------------------
void PlayCamera::SetNearFar(float n, float f)
{
	SetCameraNearFar(n, f);
}

//------------------------
// カメラの座標計算
//------------------------
void PlayCamera::Step(VECTOR forcus)
{

	VECTOR stick = ZERO;

	stick.x = CGamePad::StickRotY(STICK_RIGHT);

	stick.y = CGamePad::StickRotX(STICK_RIGHT);

	m_rot = VAdd(m_rot, VScale(stick, SENSITIVITY));

	if (m_rot.x >= CMyMath::DegRad(80)) {

		m_rot.x= CMyMath::DegRad(80);

	}
	if (m_rot.x <= CMyMath::DegRad(-80)) {

		m_rot.x = CMyMath::DegRad(-80);

	}

	int MouseX, MouseY;

	GetMousePoint(&MouseX, &MouseY);

	float x, y;

	x = (float)WINDOW_SIZE_X / 2 - (float)MouseX;

	y = (float)WINDOW_SIZE_Y / 2 - (float)MouseY;

	if (x <= 0) { x *= -1; }

	if (y <= 0) { y *= -1; }

	VECTOR MousePos = VGet(float(MouseX), (float)(MouseY), 0.0f);

	float speedy = y / (WINDOW_SIZE_Y / 2);//マウスが画面の半分の中の何割動いたか

	speedy *= 60;

	if (MousePos.y <= WINDOW_SIZE_Y / 2)
	{

		float Rad = (80 * DX_PI_F) / 180;

		if (m_rot.x < Rad)
		{

			m_rot.x += (speedy * DX_PI_F) / 180;

		}
		else
		{

			m_rot.x = Rad;

		}

		if (m_rot.x > 2.0f * DX_PI_F)m_rot.x -= 2.0f;

	}
	if (MousePos.y > WINDOW_SIZE_Y / 2)
	{

		float Rad = (-80 * DX_PI_F) / 180;

		if (m_rot.x > Rad)
		{

			m_rot.x -= (speedy * DX_PI_F) / 180;

		}
		else
		{

			m_rot.x = Rad;

		}

		if (m_rot.x < -2.0f)m_rot.x += 2.0f;

	}

	float speedx = x / (WINDOW_SIZE_X / 2);

	speedx *= 60;

	if (MousePos.x <= WINDOW_SIZE_X / 2)
	{

		m_rot.y -= (speedx * DX_PI_F) / 180;

	}
	if (MousePos.x > WINDOW_SIZE_X / 2)
	{

		m_rot.y += (speedx * DX_PI_F) / 180;

	}
	// 注視点を原点に平行移動する行列を作成

	MATRIX OriginMove;

	OriginMove = CMyMath::GetTranslateVecMatrix(-forcus.x, -forcus.y - TARGET_OFFSET_Y, -forcus.z);

	// カメラを注視点より手前に移動さえる平行移動行列を作成

	MATRIX TargetFront;

	TargetFront = CMyMath::GetTranslateVecMatrix(0.0f, TARGET_OFFSET_Y, CAMERA_LENGTH);

	// カメラのX軸回転行列を作成

	MATRIX XRot;

	XRot = CMyMath::GetPitchMatrix(m_rot.x);

	// カメラのY軸回転行列を作成

	MATRIX YRot;

	YRot = CMyMath::GetYawMatrix(m_rot.y);

	// 注視点をもとの位置に平行移動する行列を作成

	MATRIX BackOriginMove;

	BackOriginMove = CMyMath::GetTranslateVecMatrix(forcus.x, forcus.y + TARGET_OFFSET_Y, forcus.z);

	// 各行列を合成

	MATRIX Mix;

	Mix = CMyMath::MatMult(BackOriginMove, YRot);

	Mix = CMyMath::MatMult(Mix, XRot);

	Mix = CMyMath::MatMult(Mix, TargetFront);

	Mix = CMyMath::MatMult(Mix, OriginMove);

	// 注視点に行列をかけてカメラの座標を算出

	m_targetPos = VGet(forcus.x, forcus.y + TARGET_OFFSET_Y, forcus.z);

	m_camPos = CMyMath::MatTransform(Mix, forcus);

	SetMousePoint(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2);


}
void PlayCamera::Draw() {

	if (m_reticuleHit == true)

		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 1.0f, 0.0f, m_hndl2, true);

	else {

		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 1.0f, 0.0f, m_hndl, true);

	}

}

//------------------------
// カメラの更新
//------------------------
void PlayCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_camPos, m_targetPos, m_UpVec);
}


VECTOR PlayCamera::GetVec() {
	VECTOR ret;

	ret.x = cosf(m_rot.x) * sinf(m_rot.y);

	ret.y = sinf(m_rot.x);

	ret.z = cosf(m_rot.x) * cosf(m_rot.y);

	ret.x *= -1;

	ret.z *= -1;

	return ret;
}

void PlayCamera::Exit() {
	if (m_hndl != -1) {
		DeleteGraph(m_hndl);
		DeleteGraph(m_hndl2);
		m_hndl = -1;
		m_hndl2 = -1;
	}
}