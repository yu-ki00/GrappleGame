#pragma once
#include "PlayScene.h"
#include"TitleScene.h"
#include"ResultScene.h"
#include"SelectScene.h"
//シーンの管理
class SceneManager {
private:
	// ゲームの処理の流れ
	enum tagScene {
		TITLE,   // タイトルシーン
		SELECT,	//ステージセレクト
		GAME,   // ゲーム本編
		RESULT     // リザルトシーン
	};

	CPlayScene m_play;

	tagScene m_state;

	CTitleScene m_title;

	CSelectScene m_select;

	CResultScene m_result;

public:
	// コンストラクタ・デストラクタ
	SceneManager();

	~SceneManager();

	// 実行処理
	int Loop();
	// 描画処理
	void Draw();


};