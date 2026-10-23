#pragma once
#include "../../game/player/Player.h"
#include"../../game/block/blockManager.h"
#include"../../game/camera/CameraManager.h"
#include"../../game/shot/ShotManager.h"
#include"../../game/stage/goal/goal.h"
#include"../../game/stage/field/field.h"
class CCollisionManager {
public:
	//プレイヤーとそれぞれのブロックの当たり判定
	static void CheckHitPlayerToBlock(CPlayer& m_player,CBlockManager& m_block,CGrapple &grapple);

	//照準とブロックの当たり判定
	static bool CheckHitReticuleToBlock(CameraManager& m_camera, CBlockManager& m_block,CPlayer& player,CField field, int* block_index = nullptr);

	//プレイヤーとゴールの当たり判定
	static bool CheckHitPlayerToGoal(CPlayer& player, CGoal goal);

	//プレイヤーと敵の弾の当たり判定
	static void CheckHitPlayerToShot(CPlayer player, CShotManager& shot, CGrapple& grapple,CBlockManager& block);

	//プレイヤーとステージの当たり判定
	static void CheckHitPlayerToField(CPlayer& player, CField field);

	//紐とステージの当たり判定
	static void CheckHitRopeToField(CPlayer& player, CField field, CBlockManager& block,CGrapple& grapple, VECTOR* hitPos = nullptr);

	//紐とブロックの当たり判定
	static void CheckHitRopeToBlock(CPlayer& player, CField field, CBlockManager& block, CGrapple& grapple);

	//紐がブロックから離れた時の判定
	static bool CheckReleaseRopeToBlock(CGrapple& grapple,CBlockManager& block,CPlayer player);

	//敵の弾とステージの当たり判定
	static void CheckHitShotToField(CField field, CBlockManager block, CShotManager& shot);

};