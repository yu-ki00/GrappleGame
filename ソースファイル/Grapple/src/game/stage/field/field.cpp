#include"field.h"

static const char FIELD_PATH1[] = "Data/Model/field/stage.mv1";
static const char FIELD_PATH2[] = "Data/Model/field/stage2.mv1";
static const char FIELD_PATH3[] = "Data/Model/field/stage3.mv1";

void CField::Init() {
	int stagedata = Data::GetInstance()->GetStage();
	if (stagedata == 1) {
		m_state = STAGE_1;
	}
	else if (stagedata == 2) {
		m_state = STAGE_2;
	}
	else if (stagedata == 3) {
		m_state = STAGE_3;
	}

	m_isActive = true;
	m_hndl = -1;
}
void CField::Load() {
	if (m_hndl == -1) {
		if (m_state == STAGE_1) {
			m_hndl = MV1LoadModel(FIELD_PATH1);
		}
		else if (m_state == STAGE_2) {
			m_hndl = MV1LoadModel(FIELD_PATH2);

		}
		else if (m_state == STAGE_3) {
			m_hndl = MV1LoadModel(FIELD_PATH3);

		}
	}
	MV1SetupCollInfo(m_hndl);	// ƒRƒŠƒWƒ‡ƒ“î•ñ\’z

}