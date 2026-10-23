#include"block.h"

CBlock::CBlock() {
	Init();
}
void CBlock::Init() {

	m_pos = { 0.0f,10.0f,20.0f };

	m_scale = { 1.0f,1.0f,1.0f };

	m_hit = false;

	m_isActive = false;

}
void CBlock::Load(int originhndl) {
	if (m_hndl == -1) {
		m_hndl = MV1DuplicateModel(originhndl);
	}
}
void CBlock::Step() {

}