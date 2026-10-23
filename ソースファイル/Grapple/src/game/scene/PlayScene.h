#pragma once
#include<DxLib.h>
#include"../player/Player.h"
#include"../camera/CameraManager.h"
#include"../block/blockManager.h"
#include"../grapple/grapple.h"
#include"../stage/sky/sky.h"
#include"../stage/goal/goal.h"
#include"../enemy/enemyManager.h"
#include"../shot/ShotManager.h"
#include"../stage/field/field.h"

static const float KILL_Y = -400.0f;	//この高さに来るとスタートに戻る

class CPlayScene {
private:
	enum tagPlayScene {
		INIT,
		LOAD,
		MAIN,
		END,
		RETURN
	};
	tagPlayScene m_state;

	CPlayer m_player;

	CameraManager m_camera;

	CBlockManager m_block;

	CGrapple m_grapple;

	CSky m_sky;

	CGoal m_goal;

	CEnemyManager m_enemy;

	CShotManager m_shot;

	CField m_field;

	int m_prevTime;			//ひとつ前の時間

	int m_nowTime;			//今

	float m_dt;				//デルタタイム

	int m_clearTime;		//クリア時間

	int m_clearFrame;		//クリア時間（フレーム）

	int m_clearSecond;		//クリア時間（秒）

	int m_clearMilliSecond;	//クリア時間（ミリ秒）

	int m_clearMinute;		//クリア時間（分）

	int m_LineHndl;			//集中線ハンドル


public:
	CPlayScene();

	~CPlayScene();

	int Loop();

	void Draw();

	int GetClearTime() { return m_clearTime; }

private:
	void Init();

	void Load();

	void Step();

	void Exit();

	void ResetGame();
};
