#include"goal.h"
#include"../../common.h"
static const char GOAL_MODEL_PATH[] = { "Data/model/field/goal.x" };
void CGoal::Init() {

	m_isActive = true;

	m_pos = ZERO;

	m_hndl = -1;
}
void CGoal::Load(VECTOR pos) {
	if (m_hndl == -1)
		m_hndl = MV1LoadModel(GOAL_MODEL_PATH);
	m_pos = pos;
}
void CGoal::Step() {

}
VECTOR CGoal::GetCenter() {
	VECTOR pos = VGet(m_pos.x, m_pos.y + 20, m_pos.z);
	return pos;
}