#include"enemy.h"
#include"../../lib/MyMath/MyMath.h"
#include<math.h>
#include"../common.h"



void CEnemy::Init() {

	m_scale = { 5.0f,5.0f,5.0f };

	m_shotWait = 0;

	m_rot = ZERO;

}

void CEnemy::Load(int hndl) {
	if (m_hndl == -1) {

		m_hndl = MV1DuplicateModel(hndl);

	}
}

void CEnemy::Step(VECTOR plpos, CShotManager& shot, bool isShot) {
	if (!m_isActive)return;
	VECTOR vec = CMyMath::CreateVec(plpos, m_pos);

	float len = CMyMath::GetVecLength(vec);

	//プレイヤーが感知射程に入ったら動く
	if (len <= DETECTION_RANGE) {

		//距離が一定以内だとプレイヤーの方向を向く
		vec = VNorm(vec);

		m_rot.y = atan2f(-vec.x, -vec.z);

		m_rot.x = atan2f(vec.y, sqrtf(vec.x * vec.x + vec.z * vec.z));

		m_shotWait++;
		//m_shotWaitが一定以上になったら弾発射
		if (m_shotWait == SHOT_WAIT) {
			//弾のリクエスト
			shot.RequestShot(m_pos, vec, m_rot);

			m_shotWait = 0;


		}
	}
}
void CEnemy::Reset() {
	m_rot = ZERO;
}