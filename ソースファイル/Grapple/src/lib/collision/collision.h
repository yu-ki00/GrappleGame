#pragma once

#include <DxLib.h>
class Collision {
public:
	// 点と四角の当たり判定
	//	dotPos		:	点の座標
	//	squarePos	:	四角形の中心座標
	//	width		:	四角形の横幅
	//	height		:	四角形の縦幅
	//	@return		:	true=当たった　false=当たっていない
	static bool ChekHitDotToSquare(VECTOR dotPos, VECTOR squarePos,int width, int height);

	// 矩形同士の当たり判定
	//	squarePos	:	矩形の中心座標
	//	width		:	矩形の横幅
	//	height		:	矩形の縦幅
	//	@return		:	true=当たった　false=当たっていない
	static bool CheckHitBoxToBox(VECTOR BoxPos1, VECTOR BoxSize1,VECTOR BoxPos2, VECTOR BoxSize2);
	// 円同士の当たり判定
	//	circlePos	:	円の中心座標
	//	radius		:	円の半径
	//	@return		:	true=当たった　false=当たっていない
	static bool CheckHitSphereToSphere(VECTOR circlePos1, int radius1,VECTOR circlePos2, int radius2);

	//ボックスと線の当たり判定
	//	BoxPos		:	ボックスの中心座標
	//	BoxSize		:	ボックスのサイズ
	//	LineStart	:	線の始点
	//	LineEnd		:	線の終点
	//	hitPos		:	衝突座標
	static bool CheckHitLineToBox(VECTOR BoxPos, VECTOR BoxSize, VECTOR LineStart, VECTOR LineEnd, VECTOR* hitPos = nullptr);

	//線とボックスの辺の当たり判定
	//	BoxPos		:	ボックスの中心座標
	//	BoxSize		:	ボックスのサイズ
	//	LineStart	:	線の始点
	//	LineEnd		:	線の終点
	//	hitPos		:	衝突座標
	static bool CheckHitLineToBoxLine(VECTOR BoxPos, VECTOR BoxSize, VECTOR LineStart, VECTOR LineEnd, VECTOR* hitpos = nullptr);

	//線と線の当たり判定
	//LineStart1	:一本目のラインの始点
	//LineEnd1		:一本目のラインの終点
	//LineStart2	:2本目のラインの始点
	//LineEnd2		:２本目のラインの終点
	//hitpos		:衝突座標
	static bool CheckHitLineToLine(VECTOR LineStart1, VECTOR LineEnd1, VECTOR LineStart2, VECTOR LineEnd2, VECTOR* hitpos = nullptr);

	//ボックスと三角形の当たり判定
	//	p0			:	三角形の点１
	//	p1			:	三角形の点２
	//	p2			:	三角形の点３
	//	center		:	ボックスの中心点
	//	size		:	ボックスのサイズ
	static bool TriangleToBox(VECTOR p0, VECTOR& p1, VECTOR p2, VECTOR center, float size);

};