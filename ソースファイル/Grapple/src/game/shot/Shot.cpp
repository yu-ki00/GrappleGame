#include"Shot.h"
#include<math.h>
#include<DxLib.h>
#include"../common.h"



CShot::CShot() {

	m_hndl = -1;

	m_pos = m_speed = m_rot = ZERO;

	m_isActive = false;  //Å‰‚Í•\Ž¦‚µ‚È‚¢

	m_scale = { 1.0f, 1.0f, 1.0f };

	m_destroyTime = 0;

	m_rot = ZERO;

}

CShot::~CShot() {

	Exit();

}

void CShot::Init() {
	m_hndl = -1;

	m_pos = m_speed = ZERO;

	m_isActive = false;  //Å‰‚Í•\Ž¦‚µ‚È‚¢

	m_radius = 3.0f;

	m_scale = { 4.0f, 4.0f, 4.0f };

	m_destroyTime = 0;

	m_rot = ZERO;

}

void CShot::Load(int originHndl) {
	if (m_hndl == -1) {

		m_hndl = MV1DuplicateModel(originHndl);

	}
}

void CShot::Step( VECTOR plpos) {

	if (m_isActive == false)return;

	if (m_destroyTime > 180) {
		VECTOR a = VSub(m_pos, plpos);

		VECTOR b = VNorm(a);

		m_speed = VScale(b, SHOT_SPEED);
	}
	m_pos = VSub(m_pos, m_speed);

	m_destroyTime--;

	if (m_destroyTime <= 0) {

		m_isActive = false;

	}

}

void CShot::Draw() {
	if (m_isActive) {


		DrawSphere3D(m_pos, m_radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), true);

	}

}

bool CShot::RequestShot(const VECTOR& pos, const VECTOR& speed, const VECTOR& rot) {
	if (m_isActive == true)return false;
	m_pos = pos;
	m_speed = VScale(speed, SHOT_SPEED);
	m_isActive = true;
	m_rot = rot;
	m_destroyTime = 200;

	return true;
}

VECTOR CShot::GetCenter() {
	VECTOR res = m_pos;
	res.y += m_radius;
	return res;
}

void CShot::HitCalc() {
	m_isActive = false;
}
