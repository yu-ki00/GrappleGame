#include"damage_block.h"

CDamageBlock::CDamageBlock() {
	Init();
}
void CDamageBlock::Init() {

	m_pos = { 20.0f,10.0f,20.0f };

	m_scale = { 1.0f,1.0f,1.0f };

	m_hit = false;
	m_isActive = false;
	m_state = STAY;
}
void CDamageBlock::Load(int originhndl) {
	if (m_hndl == -1) {
		m_hndl = MV1DuplicateModel(originhndl);
	}
}
void CDamageBlock::Step() {
	switch (m_state)
	{
	case Move_X:
		MoveX(100);
		break;
	case Move_Y:
		break;

	default:
		break;
	}
}
void CDamageBlock::MoveX(int move) {
	VECTOR vec = VSub(m_startpos, m_pos);
	float endX = m_startpos.x + move;
	float len = VSize(vec);
	if (m_pos.x <= endX && m_movecomp == false) {
		m_pos.x += 3;
		if (m_pos.x >= endX) {
			m_movecomp = true;
		}
	}
	else if (m_pos.x >= m_startpos.x && m_movecomp == true) {
		m_pos.x -= 3;
		if (m_pos.x <= m_startpos.x) {
			m_movecomp = false;
		}
	}

}
void CDamageBlock::MoveY(int move) {
	VECTOR vec = VSub(m_startpos, m_pos);
	int endX = (int)m_startpos.y + move;
	float len = VSize(vec);
	if (m_pos.y <= endX && m_movecomp == false) {
		m_pos.y += 3;
		if (m_pos.y >= endX) {
			m_movecomp = true;
		}
	}
	else if (m_pos.y >= m_startpos.y && m_movecomp == true) {
		m_pos.y -= 3;
		if (m_pos.y <= m_startpos.y) {
			m_movecomp = false;
		}
	}

}