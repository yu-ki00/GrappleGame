#include"sky.h"
#include"../../common.h"
static const char SKY_MODEL_PATH[] = { "Data/Model/sky/yozora.mv1" };
static const VECTOR SKY_SCALE = { 25,25,25 };
void CSky::Init() {
	m_pos = ZERO;
	m_rot = { 0,0,0 };
	m_scale = SKY_SCALE;
	m_hndl = -1;
}
void CSky::Load() {
	if (m_hndl == -1)
	{
		m_hndl = MV1LoadModel(SKY_MODEL_PATH);
	}
}
void CSky::Step(VECTOR pos) {
	m_pos = pos;
}
void CSky::Update() {
	MV1SetRotationXYZ(m_hndl, m_rot);
	MV1SetScale(m_hndl, m_scale);
	MV1SetPosition(m_hndl, m_pos);

}
void CSky::Draw() {
	MV1DrawModel(m_hndl);
}
void CSky::Exit() {
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}

