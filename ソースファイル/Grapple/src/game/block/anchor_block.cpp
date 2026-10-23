#include"anchor_block.h"
CAnchorBlock::CAnchorBlock() {

}
void CAnchorBlock::Init() {

	m_pos = { 20.0f,70.0f,260.0f };

	m_scale = { 1.0f,1.0f,1.0f };

	m_hit = false;

	m_movecomp = false;

	m_anchit = false;

	m_isMoveX = false;

	m_isMoveY = false;

	m_isActive = false;

	m_movelen = 0;
}
void CAnchorBlock::Load(int originhndl) {

	if (m_hndl == -1) {

		m_hndl = MV1DuplicateModel(originhndl);

	}

	m_startpos = m_pos;

}
void CAnchorBlock::Step() {
	if (m_isMoveX == true)
		MoveX(m_movelen);
	if (m_isMoveY == true)
		MoveY(m_movelen);
}
void CAnchorBlock::MoveX(int move) {

	VECTOR vec = VSub(m_startpos, m_pos);

	int endX = (int)m_startpos.x + move;

	float len = VSize(vec);

	if (m_pos.x <= endX && m_movecomp == false) {

		m_pos.x += 2;

		if (m_pos.x >= endX) {

			m_movecomp = true;

		}
	}
	else if (m_pos.x >= m_startpos.x &&m_movecomp == true) {

		m_pos.x -= 2;

		if (m_pos.x <= m_startpos.x) {

			m_movecomp = false;

		}
	}

}
void CAnchorBlock::MoveY(int move) {

	VECTOR vec = VSub(m_startpos, m_pos);

	int endY = (int)m_startpos.y + move;

	float len = VSize(vec);

	if (m_pos.x <= endY && m_movecomp == false) {

		m_pos.y += 2;

		if (m_pos.y >= endY) {

			m_movecomp = true;

		}
	}
	else if (m_pos.y >= m_startpos.y && m_movecomp == true) {

		m_pos.y -= 2;

		if (m_pos.y <= m_startpos.y) {

			m_movecomp = false;

		}
	}

}
void CAnchorBlock::SetMoveX(bool ismove, int movelen) {
	m_isMoveX = ismove;
	m_movelen = movelen;
}
void CAnchorBlock::SetMoveY(bool ismove, int movelen) {
	m_isMoveY = ismove;
	m_movelen = movelen;
}