#pragma once
#include "DxLib.h"

//インプットクラス
class CInput
{
private:

public:
	//入力制御初期化
	static void Init();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void Step();

	//今押された
	static bool IsTrg(int Key_code);

	//ずっと押されている
	static bool IsKeep(int Key_code);

	//キーを離した
	static bool IsRelease(int Key_code);

	//単純に押されているか
	static bool IsRep(int Key_code);
};


