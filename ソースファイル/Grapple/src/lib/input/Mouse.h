#pragma once
#include<DxLib.h>
#include<math.h>
//インプットクラス
class CMouse
{
private:

public:
	//入力制御初期化
	static void Init();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void Step();

	//今押された
	static bool IsPush(int Mouse_code);

	//ずっと押されている
	static bool IsKeep(int Mouse_code);

	//キーを離した
	static bool IsRelease(int Mouse_code);

	//単純に押されているか
	static bool IsDown(int Mouse_code);
};
