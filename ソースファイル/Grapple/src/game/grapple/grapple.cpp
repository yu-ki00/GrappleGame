#include"grapple.h"
#include"../common.h"
#include"../../lib/Frame/frame.h"
#include"../../lib/MyMath/MyMath.h"
#include"../../lib/input/PadInput.h"
#include"../../lib/input/input.h"
#include<math.h>

void CGrapple::Init() {
	m_isShot = false;

	m_targetpos = { 0 };

	m_frameIndex = 0;

	m_framepos = ZERO;

	m_hit2 = false;

	m_targetpos2 = ZERO;

	m_isActive = true;

}
void CGrapple::Load() {
	if (m_hndl == -1)

		m_hndl = MV1LoadModel(GRAPPLE_PATH);

	m_frameIndex = MV1SearchFrame(m_hndl, "ボーン.001");

}
void CGrapple::Step(int hndl, CBlockManager& block) {

	//プレイヤーの手の位置にグラップルを持ってくる処理
	MATRIX mat = MGetRotY(DX_PI_F);

	MATRIX mat1 = MGetRotX(DX_PI_F * 0.5);

	MATRIX mat2 = MV1GetFrameLocalWorldMatrix(hndl, 11);

	mat1 = MMult(mat1, mat);

	mat1 = MMult(mat1, mat2);

	VECTOR vecX = VGet(mat1.m[0][0], mat1.m[1][0], mat1.m[2][0]);

	VECTOR vecY = VGet(mat1.m[0][1], mat1.m[1][1], mat1.m[2][1]);

	VECTOR vecZ = VGet(mat1.m[0][2], mat1.m[1][2], mat1.m[2][2]);

	vecX = VNorm(vecX);

	vecY = VNorm(vecY);

	vecZ = VNorm(vecZ);

	mat1.m[0][0] = vecX.x; mat1.m[1][0] = vecX.y; mat1.m[2][0] = vecX.z;

	mat1.m[0][1] = vecY.x; mat1.m[1][1] = vecY.y; mat1.m[2][1] = vecY.z;

	mat1.m[0][2] = vecZ.x; mat1.m[1][2] = vecZ.y; mat1.m[2][2] = vecZ.z;

	MV1SetMatrix(m_hndl, mat1);


	auto& whiteBlocks = block.GetWhite();
	for (int i = 0; i < whiteBlocks.size(); i++) {
		CAnchorBlock& oneblock = whiteBlocks[i];
		//グラップルが発射されていない場合ブロック側の接触判定を消す
		if (m_isShot == false) {

			oneblock.SetAncHit(false);

		}

		if (oneblock.GetAncHit() == false)continue;

		if (m_isShot == true) {
			//目標のブロックの位置をターゲットにグラップルの先端を飛ばす
			m_targetpos = oneblock.GetPos();

			//グラップルの先端フレームをターゲットの位置に飛ばす処理

			CFrame::SetFrameWorldPosition(m_hndl, m_frameIndex, m_targetpos);

		}
	}
	m_framepos = MV1GetFramePosition(m_hndl, m_frameIndex);

	if (m_isShot == false) {
		//発射されていない場合はフレームを元の位置に戻す
		MV1ResetFrameUserLocalMatrix(m_hndl, m_frameIndex);

	}
}
//これを呼んでフレームを飛ばす
void CGrapple::RequestShot(VECTOR pos) {

	m_targetpos = pos;

	m_isShot = true;

}
float CGrapple::GetLength() {

	float length = 0;

	VECTOR vec = VSub(m_targetpos, m_framepos);

	length = VSize(vec);

	return length;

}
VECTOR CGrapple::GetDir() {

	VECTOR dir = VSub(m_targetpos, m_framepos);

	dir = CMyMath::VecNorm(dir, GetLength());

	return dir;

}

void CGrapple::OutShot() {

	m_isShot = false;

	m_hit2 = false;

	m_targetpos2 = ZERO;

}