#include"frame.h"
#include"../MyMath/MyMath.h"
#include"../../game/common.h"
//フレームの座標をローカル座標からワールド座標にする
MATRIX CFrame::GetWorldMatrix(int modelHndl, int frameIndex) {

	MATRIX local = MV1GetFrameLocalMatrix(modelHndl, frameIndex);

	int parent = MV1GetFrameParent(modelHndl, frameIndex);

	if (parent == -1)return local;

	MATRIX parentWorld = GetWorldMatrix(modelHndl, parent);

	return CMyMath::MatMult(parentWorld, local);
}


void CFrame::SetFrameWorldPosition(int modelHndl, int frameIndex, VECTOR targetWorld) {

	MATRIX modelWorld = MV1GetMatrix(modelHndl);

	MATRIX invModelWorld = MInverse(modelWorld);

	//ワールド → モデル座標
	VECTOR targetModel = VTransform(targetWorld, invModelWorld);

	//親のワールド行列（モデル座標系）
	int parent = MV1GetFrameParent(modelHndl, frameIndex);

	MATRIX parentWorld_Model = MGetIdent();

	if (parent != -1) {

		parentWorld_Model = GetWorldMatrix(modelHndl, parent);

	}
	MATRIX invParent_Model = MInverse(parentWorld_Model);

	//モデル座標 → 親ローカル座標
	VECTOR targetLocal = VTransform(targetModel, invParent_Model);

	//フレームの行列を更新（位置だけ差し替え）
	MATRIX localMat = MV1GetFrameLocalMatrix(modelHndl, frameIndex);

	localMat.m[3][0] = targetLocal.x;

	localMat.m[3][1] = targetLocal.y;

	localMat.m[3][2] = targetLocal.z;

	MV1SetFrameUserLocalMatrix(modelHndl, frameIndex, localMat);
}