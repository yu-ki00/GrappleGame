#include <crtdbg.h>
#include <memory>
#include "DxLib.h"
#include <math.h>
#include"common.h"
#include"scene/sceneManager.h"
#include"../lib/debug/fps.h"



// プログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	Sleep(1);
	// メモリリーク発見用
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// スクリーン設定
	ChangeWindowMode(TRUE);			// フルスクリーンorウィンドウモード
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);	// ウィンドウのサイズ

#ifndef _DEBUG
	// リリース版はログを出さない
	SetOutApplicationLogValidFlag(false);
#endif
	SetMainWindowText("Grapple");


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	//一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetMouseDispFlag(false);

	CFps::Init();
	// インスタント作成と初期化
	SceneManager scene;

	// 背景の初期化
	//SetMouseDispFlag(false);
	Data* p = Data::GetInstance();



	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		//エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (!CFps::CheckNext())continue;
		ClearDrawScreen();	// 画面クリア
		//フレームレート計算
		CFps::Calc();

		scene.Loop();
		scene.Draw();



		ScreenFlip();		// 描画切り替え

	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}