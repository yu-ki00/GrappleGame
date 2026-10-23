#pragma once
#include<DxLib.h>
//ボーンを動かす処理
class CFrame {
public:
	//ボーンのワールド座標の取得
	static MATRIX GetWorldMatrix(int modelHndl, int frameIndex);

	//ボーンの位置のセット
	static void SetFrameWorldPosition(int modelHndl, int frameIndex,VECTOR targetWorld);
};