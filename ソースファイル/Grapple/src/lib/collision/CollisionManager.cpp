#include"CollisionManager.h"
#include"collision.h"
#include"../../game/system/SoundManager.h"
#include<math.h>
bool isGround = false;

//プレイヤーとそれぞれのブロックの当たり判定
void CCollisionManager::CheckHitPlayerToBlock(CPlayer& m_player, CBlockManager& m_block, CGrapple& grapple) {

	bool isHit = false;

	if (isGround == true) {

		isGround = false;

	}
	for (int b = 0; b < BLOCK_NUM; b++) {

		switch (b)
		{
		case BLUE_BLOCK:

			for (CBlock& oneblock : m_block.GetBlue()) {

				VECTOR block_pos = oneblock.GetPos();

				VECTOR player_pos = m_player.GetCenter();

				VECTOR vec = VSub(player_pos, block_pos);

				float len = VSize(vec);

				if (len > 30)continue;

				// 当たっていたら、各軸のめり込んでいる距離を出す
				isHit = Collision::CheckHitBoxToBox(player_pos, PLAYER_SIZE,

				block_pos, VGet(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

				if (isHit) {

					VECTOR v = VSub(player_pos, block_pos);

					v.x = (BLOCK_SIZE / 2 + PLAYER_SIZE.x / 2) - fabsf(v.x);

					v.y = (BLOCK_SIZE / 2 + PLAYER_SIZE.y / 2) - fabsf(v.y);

					v.z = (BLOCK_SIZE / 2 + PLAYER_SIZE.z / 2) - fabsf(v.z);

					// 押し戻し距離で一番めり込んだ距離が短い場所だけ押し戻す
					if (v.x < v.y && v.x < v.z) {

						v.y = v.z = 0.0f;

					}
					else if (v.y < v.x && v.y < v.z) {
						v.x = v.z = 0.0f;

						m_player.ResetVelocity_Y();

						if (player_pos.y > block_pos.y) {

							isGround = true;
						}

					}
					else if (v.z < v.x && v.z < v.y) {

						v.x = v.y = 0.0f;

					}
					// 各軸の押し戻し方向を確定
					if (player_pos.x < block_pos.x) v.x *= -1.0f;

					if (player_pos.y < block_pos.y) v.y *= -1.0f;

					if (player_pos.z < block_pos.z) v.z *= -1.0f;

					// 押し戻した距離を加算
					player_pos = VAdd(player_pos, v);

					player_pos.y -= 10;

					m_player.SetPos(player_pos);

					if (isGround == true) {

						m_player.IsGround(true);

					}
					else {

						m_player.IsGround(false);
					}

				}
			}
			break;
		case RED_BLOCK:

			for (CDamageBlock& oneblock : m_block.GetRed()){

				VECTOR block_pos = oneblock.GetPos();

				VECTOR player_pos = m_player.GetCenter();

				VECTOR vec = VSub(player_pos, block_pos);

				float len = VSize(vec);

				if (len > 30)continue;

				// 当たっていたら、各軸のめり込んでいる距離を出す
				isHit = Collision::CheckHitBoxToBox(player_pos, PLAYER_SIZE,

					block_pos, VGet(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

				if (isHit) {

					grapple.SetShot(false);

					m_player.SetPos(START_POS);

					VECTOR v = VSub(player_pos, block_pos);

					v.x = (BLOCK_SIZE / 2 + PLAYER_SIZE.x / 2) - fabsf(v.x);

					v.y = (BLOCK_SIZE / 2 + PLAYER_SIZE.y / 2) - fabsf(v.y);

					v.z = (BLOCK_SIZE / 2 + PLAYER_SIZE.z / 2) - fabsf(v.z);

					// 押し戻し距離で一番めり込んだ距離が短い場所だけ押し戻す
					if (v.x < v.y && v.x < v.z) {

						v.y = v.z = 0.0f;

						m_player.ResetVelocity_X();

					}
					else if (v.y < v.x && v.y < v.z) {

						v.x = v.z = 0.0f;

						m_player.ResetVelocity_Y();

						if (player_pos.y > block_pos.y) {

							isGround = true;
						}
					}
					else {
						v.x = v.y = 0.0f;

						m_player.ResetVelocity_Z();

					}

					// 各軸の押し戻し方向を確定
					if (player_pos.x < block_pos.x) v.x *= -1.0f;

					if (player_pos.y < block_pos.y) v.y *= -1.0f;

					if (player_pos.z < block_pos.z) v.z *= -1.0f;

					// 押し戻した距離を加算
					player_pos = VAdd(player_pos, v);

					player_pos.y -= 10;

					m_player.SetPos(player_pos);

					if (isGround == true) {

						m_player.IsGround(true);
					}
					else {

						m_player.IsGround(false);
					}

				}
			}
			break;
		case WHITE_BLOCK:

			for (CAnchorBlock& oneblock : m_block.GetWhite()) {

				VECTOR block_pos = oneblock.GetPos();

				VECTOR player_pos = m_player.GetCenter();

				VECTOR vec = VSub(player_pos, block_pos);

				float len = VSize(vec);

				if (len > 30)continue;

				// 当たっていたら、各軸のめり込んでいる距離を出す
				isHit = Collision::CheckHitBoxToBox(player_pos, PLAYER_SIZE,

					block_pos, VGet(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

				if (isHit) {

					VECTOR v = VSub(player_pos, block_pos);

					v.x = (BLOCK_SIZE / 2 + PLAYER_SIZE.x / 2) - fabsf(v.x);

					v.y = (BLOCK_SIZE / 2 + PLAYER_SIZE.y / 2) - fabsf(v.y);

					v.z = (BLOCK_SIZE / 2 + PLAYER_SIZE.z / 2) - fabsf(v.z);

					// 押し戻し距離で一番めり込んだ距離が短い場所だけ押し戻す
					if (v.x < v.y && v.x < v.z) {

						v.y = v.z = 0.0f;

					}
					else if (v.y < v.x && v.y < v.z) {

						v.x = v.z = 0.0f;

						m_player.ResetVelocity_Y();

						if (player_pos.y > block_pos.y) {

							isGround = true;
						}
					}
					else {

						v.x = v.y = 0.0f;

					}
					// 各軸の押し戻し方向を確定
					if (player_pos.x < block_pos.x) v.x *= -1.0f;

					if (player_pos.y < block_pos.y) v.y *= -1.0f;

					if (player_pos.z < block_pos.z) v.z *= -1.0f;

					// 押し戻した距離を加算
					player_pos = VAdd(player_pos, v);

					player_pos.y -= 10;

					m_player.SetPos(player_pos);

					if (isGround == true) {

						m_player.IsGround(true);
					}
					else {

						m_player.IsGround(false);
					}

				}
			}
			break;
		default:
			break;
		}

	}

}

//照準とブロックの当たり判定
bool CCollisionManager::CheckHitReticuleToBlock(CameraManager& m_camera, CBlockManager& m_block, CPlayer& player, CField field, int* block_index) {
	bool isHit = false;

	VECTOR camera_vec = m_camera.GetVec();

	VECTOR camera_pos = m_camera.GetPos();

	VECTOR player_pos = m_camera.GetTarget();

	for (int j = 0; j < LENGTH; j++)
	{
		for (CBlock& oneblock : m_block.GetBlue()) {

			VECTOR block_pos = oneblock.GetPos();

			VECTOR HitPos = VAdd(player_pos, VScale(camera_vec, (float)j));

			isHit = Collision::CheckHitSphereToSphere(HitPos, 1, block_pos, 20);

			if (isHit) {

				return false;
			}

		}
		for (CDamageBlock& oneblock : m_block.GetRed()) {

			VECTOR block_pos = oneblock.GetPos();

			VECTOR HitPos = VAdd(player_pos, VScale(camera_vec, (float)j));

			isHit = Collision::CheckHitSphereToSphere(HitPos, 1, block_pos, 20);

			if (isHit) {

				return false;
			}

		}
		auto& whiteBlocks = m_block.GetWhite();
		for (int i = 0; i < whiteBlocks.size(); i++) {
			CAnchorBlock& oneblock = whiteBlocks[i];

			VECTOR block_pos = oneblock.GetPos();

			VECTOR HitPos = VAdd(player_pos, VScale(camera_vec, (float)j));

			isHit = Collision::CheckHitSphereToSphere(HitPos, 1, block_pos, 20);

			if (isHit) {
				*block_index = i;

				return isHit;
			}
			else {
				m_block.SetHit(false, i);

				m_camera.ReticuleHit(false);

			}

		}

	}
	return false;
}

//プレイヤーとゴールの当たり判定
bool CCollisionManager::CheckHitPlayerToGoal(CPlayer& player, CGoal goal) {

	bool isHit = false;

	VECTOR plpos = player.GetCenter();

	int plrad = (int)PLAYER_SIZE.y / 2;

	VECTOR glpos = goal.GetCenter();

	isHit = Collision::CheckHitSphereToSphere(plpos, plrad, glpos, 30);

	return isHit;

}

//プレイヤーと敵の弾の当たり判定
void CCollisionManager::CheckHitPlayerToShot(CPlayer player, CShotManager& shot, CGrapple& grapple, CBlockManager& block) {

	bool isHit = false;

	for (int i = 0; i < SHOT_NUM; i++) {

		CShot& oneShot = shot.GetShot(i);

		VECTOR plpos = player.GetCenter();

		VECTOR shotpos = oneShot.GetCenter();

		int plrad = (int)PLAYER_SIZE.y / 2;

		int shotrad = (int)oneShot.GetRadius();

		isHit = Collision::CheckHitSphereToSphere(plpos, plrad, shotpos, shotrad);

		if (isHit) {

			oneShot.HitCalc();

			grapple.SetShot(false);
			SoundManager::Play(SoundManager::SE_DAMAGE, DX_PLAYTYPE_BACK);
		}
	}
}
//プレイヤーとステージの当たり判定
void CCollisionManager::CheckHitPlayerToField(CPlayer& player, CField field) {

	VECTOR result{ 0.0f };

	bool m_isHitFlag = false;

	VECTOR plpos = player.GetCenter();

	float plrad = player.GetRadius();

	float scale = 0.0f;

	//当たり判定情報が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	col = MV1CollCheck_Sphere(field.GetHndl(), -1, plpos, plrad);

	if (col.HitNum != 0) {

		m_isHitFlag = true;

		VECTOR nownorm = { 0 };

		float nowsize = 0.0f;

		for (int i = 0; i < col.HitNum; i++) {

			VECTOR Normal = col.Dim[i].Normal;

			VECTOR v = VSub(plpos, col.Dim[i].HitPosition);
			float len = VSize(v);

			len = plrad - len;

			v = VScale(Normal, len);

			nownorm = VAdd(nownorm, v);
			if (Normal.y >= 0.5) {

				player.ResetVelocity_Y();

				isGround = true;
			}
			else if (Normal.y <= -0.7) {

				player.ResetVelocity_Y();
			}

			nowsize = VSize(result);

			if (nowsize >= scale) {

				result = nownorm;

				//はじきによる微量のずれを消すためにintにして小数点以下を消して渡す
				result.y = (int)result.y;

				scale = nowsize;
			}

		}
		if (isGround == true) {

			player.IsGround(true);

		}
		else {

			player.IsGround(false);
		}

		player.SetPos(VAdd(result, player.GetPos()));

	}
	else {
		if (isGround == true) {

			player.IsGround(true);

		}
		else if (isGround == false) {

			player.IsGround(false);

		}
	}

	MV1CollResultPolyDimTerminate(col);

}

//紐とステージの当たり判定
void CCollisionManager::CheckHitRopeToField(CPlayer& player, CField field, CBlockManager& block, CGrapple& grapple, VECTOR* hitPos) {

	grapple.SetHit2(false);

	if (grapple.IsShot() == false)
	{
		grapple.SetHit2(false);

		grapple.SetTarget2(ZERO);

		return;
	}

	int hitindex = 0;

	VECTOR ancpos = grapple.GetAncPos();

	VECTOR plpos = player.GetCenter();

	bool isHit = false;

	auto& whiteBlocks = block.GetWhite();

	for (int i = 0; i < whiteBlocks.size(); i++) {

		CAnchorBlock& oneblock = whiteBlocks[i];

		if (oneblock.GetAncHit()) {

			hitindex = i;

			break;
		}
	}
	for (int block_num = 0; block_num < BLOCK_NUM; block_num++) {

		if (block_num == 1)continue;

		switch (block_num)
		{
		case BLUE_BLOCK:

			for (CBlock& oneblock : block.GetBlue()){

				if (oneblock.GetActive() == false)continue;

				VECTOR blockpos = oneblock.GetPos();

				VECTOR blocksize = VGet(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);

				isHit = Collision::CheckHitLineToBox(blockpos, blocksize, ancpos, plpos, hitPos);

				if (isHit) {

					grapple.SetTarget2(*hitPos);

					grapple.SetHit2(true);

					oneblock.SetHit(true);

				}

			}
			break;

		case RED_BLOCK:
			for (CDamageBlock& oneblock : block.GetRed()) {

				if (oneblock.GetActive() == false)continue;

				VECTOR blockpos = oneblock.GetPos();

				VECTOR blocksize = VGet(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);

				isHit = Collision::CheckHitLineToBox(blockpos, blocksize, ancpos, plpos, hitPos);

				if (isHit) {

					grapple.OutShot();

				}
			}
			break;
		default:
			break;
		}
	}
	if (grapple.GetHit2() == false) {

		grapple.SetTarget2(ZERO);
	}
}


//紐がブロックから離れた時の判定
bool CCollisionManager::CheckReleaseRopeToBlock(CGrapple& grapple, CBlockManager& block, CPlayer player) {

	bool isHit = false;
	//グラップル情報の取得
	VECTOR ancpos = grapple.GetAncPos();

	VECTOR plpos = player.GetPos();

	VECTOR target2 = grapple.GetTarget2();

	for (int block_num = 0; block_num < BLOCK_NUM; block_num++) {

		switch (block_num)
		{
		case BLUE_BLOCK:

			for (CBlock& oneblock : block.GetBlue()){

				if (oneblock.GetActive() == false)continue;

				VECTOR blockpos = oneblock.GetPos();

				VECTOR blocksize = VGet(BLOCK_SIZE - 2, BLOCK_SIZE - 2, BLOCK_SIZE - 2);

				//紐がブロックと当たっているかを三角形とブロックの当たり判定で判定
				isHit = Collision::TriangleToBox(ancpos, plpos, target2, blockpos, BLOCK_SIZE - 2);

				if (isHit) {

					return true;

				}
			}
			break;

		case RED_BLOCK:
			for (CDamageBlock& oneblock : block.GetRed()) {

				if (oneblock.GetActive() == false)continue;

				VECTOR blockpos = oneblock.GetPos();

				VECTOR blocksize = VGet(BLOCK_SIZE - 2, BLOCK_SIZE - 2, BLOCK_SIZE - 2);

				isHit = Collision::TriangleToBox(ancpos, plpos, target2, blockpos, BLOCK_SIZE - 2);

				if (isHit) {

					return true;

				}
			}
			break;
		default:
			break;
		}
	}
	return false;
}

//敵の弾とステージの当たり判定
void CCollisionManager::CheckHitShotToField(CField field, CBlockManager block, CShotManager& shot) {

	VECTOR result{ 0.0f };

	bool m_isHitFlag = false;

	for (int i = 0; i < SHOT_NUM; i++) {

		//弾一つ一つの取得
		CShot& oneshot = shot.GetShot(i);

		if (!oneshot.GetActive())continue;

		//必要な弾の情報の取得
		VECTOR shotpos = oneshot.GetPos();

		float shotrad = oneshot.GetRadius();

		//当たり判定情報が格納される構造体
		MV1_COLL_RESULT_POLY_DIM col;

		//フィールドと弾の当たり判定
		col = MV1CollCheck_Sphere(field.GetHndl(), -1, shotpos, shotrad);

		if (col.HitNum != 0) {

			oneshot.HitCalc();

			continue;
		}

		//それぞれのブロックとの当たり判定
		for (int block_num = 0; block_num < 3; block_num++) {
			bool hit = false;
			switch (block_num)
			{
				//青ブロックとの当たり判定
			case BLUE_BLOCK:

				for (CBlock& oneblock : block.GetBlue()) {

					VECTOR block_pos = oneblock.GetPos();

					VECTOR block_size = { BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };

					//弾とブロックがぶつかっていたら衝突判定をtrueに
					if (Collision::CheckHitBoxToBox(block_pos, block_size, shotpos, VGet(shotrad, shotrad, shotrad))) {

						hit = true;

					}
				}
				break;
			case WHITE_BLOCK:
				//白ブロックとの衝突判定
				for (CAnchorBlock& oneblock : block.GetWhite()){

					VECTOR block_pos = oneblock.GetPos();

					VECTOR block_size = { BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };

					//弾とブロックがぶつかっていたら衝突判定をtrueに
					if (Collision::CheckHitBoxToBox(block_pos, block_size, shotpos, VGet(shotrad, shotrad, shotrad))) {

						hit = true;

					}
				}
				break;
			case RED_BLOCK:
				//赤ブロックとの衝突判定
				for (CDamageBlock& oneblock : block.GetRed()) {

					VECTOR block_pos = oneblock.GetPos();

					VECTOR block_size = { BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };

					//弾とブロックがぶつかっていたら衝突判定をtrueに
					if (Collision::CheckHitBoxToBox(block_pos, block_size, shotpos, VGet(shotrad, shotrad, shotrad))) {

						hit = true;

					}
				}
				break;


			default:
				break;
			}
			if (hit == true) {

				oneshot.HitCalc();

				break;
			}
		}
	}
}