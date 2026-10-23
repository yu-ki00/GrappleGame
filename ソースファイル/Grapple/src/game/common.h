#pragma once
#include<DxLib.h>
//#define DEBUG

enum {
	ANIMSTATE_NORMAL = 0,	// 終了後デタッチする(多分使わない)
	ANIMSTATE_LOOP,			// 繰返しループ
	ANIMSTATE_END,			// 最終フレームで停止

	ANIMSTATE_NUM
};
static const int WINDOW_SIZE_X = 1600;

static const int WINDOW_SIZE_Y = 900;

static const float G = 200.0f;		//通常時の重力

static const float GG = 600.0f;		//グラップリング中に働く重力

static const int BLOCK_SIZE = 20;

static const int RED = GetColor(255, 0, 0);
static const int GREEN = GetColor(0, 255, 0);
static const int BLUE = GetColor(0, 0, 255);
static const int WHITE = GetColor(255, 255, 255);

static const int STAGE_NUM = 3;

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };

