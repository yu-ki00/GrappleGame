#include "collision.h"
#include"math.h"
#include"float.h"
#include"iostream"
#include"algorithm"
#include"../MyMath/MyMath.h"
#include"cmath"
using namespace std;
#define BOX_LINE_NUM (12)
//---------------------------------
// 点と四角の当たり判定
//---------------------------------
bool Collision::ChekHitDotToSquare(VECTOR dotPos, VECTOR squarePos,
	int width, int height)
{
	// 四角形の上下左右それぞれの座標を計算する
	float up = squarePos.y - height * 0.5f;
	float down = squarePos.y + height * 0.5f;
	float left = squarePos.x - width * 0.5f;
	float right = squarePos.x + width * 0.5f;

	// 4つの端をそれぞれチェックして、すべての条件を満たしたらヒット
	if (dotPos.x >= left && dotPos.x <= right
		&& dotPos.y >= up && dotPos.y <= down)
	{
		return true;
	}
	else return false;
}


//---------------------------------
// 矩形同士の当たり判定
//---------------------------------
bool Collision::CheckHitBoxToBox(VECTOR BoxPos1, VECTOR BoxSize1,
	VECTOR BoxPos2, VECTOR BoxSize2)
{
	// 四角形の上下左右それぞれの座標を計算する
	float up1 = BoxPos1.y - BoxSize1.y * 0.5f;
	float down1 = BoxPos1.y + BoxSize1.y * 0.5f;
	float left1 = BoxPos1.x - BoxSize1.x * 0.5f;
	float right1 = BoxPos1.x + BoxSize1.x * 0.5f;
	float flont1 = BoxPos1.z - BoxSize1.z * 0.5f;
	float back1 = BoxPos1.z + BoxSize1.z * 0.5f;

	float up2 = BoxPos2.y - BoxSize2.y * 0.5f;
	float down2 = BoxPos2.y + BoxSize2.y * 0.5f;
	float left2 = BoxPos2.x - BoxSize2.x * 0.5f;
	float right2 = BoxPos2.x + BoxSize2.x * 0.5f;
	float flont2 = BoxPos2.z - BoxSize2.z * 0.5f;
	float back2 = BoxPos2.z + BoxSize2.z * 0.5f;

	// 4つの端をそれぞれチェックして、すべての条件を満たしたらヒット
	if (left1 <= right2 && right1 >= left2
		&& up1 <= down2 && down1 >= up2
		&& flont1 <= back2 && back1 >= flont2)
	{
		return true;
	}
	else return false;
}


//---------------------------------
// 球同士の当たり判定
//---------------------------------
bool Collision::CheckHitSphereToSphere(VECTOR circlePos1, int radius1,
	VECTOR circlePos2, int radius2)
{
	// 円1から円2までの距離を計算
	float lengthX = circlePos1.x - circlePos2.x;
	lengthX *= lengthX;
	float lengthY = circlePos1.y - circlePos2.y;
	lengthY *= lengthY;
	float lengthZ = circlePos1.z - circlePos2.z;
	lengthZ *= lengthZ;

	float length = lengthX + lengthY + lengthZ;	// これがaの2乗＋bの2乗

	// 2つの円の半径を加算し、2乗する
	float lengthRadius = (float)(radius1 + radius2);
	lengthRadius *= lengthRadius;


	// 以下の条件を満たせばヒットする
	if (lengthRadius >= length)
	{
		return true;
	}
	else return false;
}

bool Collision::CheckHitLineToBox(VECTOR BoxPos,VECTOR BoxSize, VECTOR LineStart,VECTOR LineEnd, VECTOR* hitPos) {
	VECTOR half = VScale(BoxSize, 0.5f);
	VECTOR boxMin = VSub(BoxPos, half);
	VECTOR boxMax = VAdd(BoxPos, half);
	//線の方向ベクトル-------------------------------------
	VECTOR dir = VSub(LineEnd, LineStart);
	float tmin = 0.0f;
	float tmax = 1.0f;

	auto checkAxis = [&](float s, float d, float mn, float mx)-> bool {
		//平行
		if (fabs(d) < 1e-6f) {
			//線分全体がBOXのこの軸の範囲外
			return (s >= mn && s <= mx);
		}
		float t1 = (mn - s) / d;
		float t2 = (mx - s) / d;

		float tNear = min(t1, t2);
		float tFar = max(t1, t2);
		if (tFar<tmin || tNear>tmax)
			return false;
		tmin = max(tmin, tNear);
		tmax = min(tmax, tFar);
		return tmin <= tmax;
		};
	if (!checkAxis(LineStart.x, dir.x, boxMin.x, boxMax.x))return false;
	if (!checkAxis(LineStart.y, dir.y, boxMin.y, boxMax.y))return false;
	if (!checkAxis(LineStart.z, dir.z, boxMin.z, boxMax.z))return false;

	float t = tmin;
	if (t < 0.0f || t>1.0f)return false;
	if (hitPos)*hitPos = VAdd(LineStart, VScale(dir, t));

	return true;
}

bool Collision::CheckHitLineToBoxLine(VECTOR BoxPos, VECTOR BoxSize, VECTOR LineStart, VECTOR LineEnd, VECTOR* hitpos) {
	VECTOR half = VScale(BoxSize, 0.5f);
	bool isHit = false;
	VECTOR BoxDot1 = { BoxPos.x - half.x,BoxPos.y - half.y,BoxPos.z + half.z };
	VECTOR BoxDot2 = { BoxPos.x - half.x,BoxPos.y + half.y ,BoxPos.z + half.z };
	VECTOR BoxDot3 = { BoxPos.x + half.x,BoxPos.y - half.y ,BoxPos.z + half.z };
	VECTOR BoxDot4 = { BoxPos.x + half.x,BoxPos.y + half.y,BoxPos.z + half.z };
	VECTOR BoxDot5 = { BoxPos.x - half.x,BoxPos.y - half.y,BoxPos.z - half.z };
	VECTOR BoxDot6 = { BoxPos.x - half.x,BoxPos.y + half.y ,BoxPos.z - half.z };
	VECTOR BoxDot7 = { BoxPos.x + half.x,BoxPos.y - half.y ,BoxPos.z - half.z };
	VECTOR BoxDot8 = { BoxPos.x + half.x,BoxPos.y + half.y,BoxPos.z - half.z };
	VECTOR boxEdgesStart[12] = {
	 BoxDot2,  BoxDot4,  BoxDot3, BoxDot1, // top
	 BoxDot6,  BoxDot8,  BoxDot7, BoxDot5, // bottom
	 BoxDot5,  BoxDot6,  BoxDot7, BoxDot8  // sides
	};
	VECTOR boxEdgesEnd[12] = {
		BoxDot2,BoxDot4,BoxDot3,BoxDot1,
		BoxDot6,BoxDot8,BoxDot7,BoxDot5,
		BoxDot5,BoxDot6,BoxDot7,BoxDot8
	};

	for (int i = 0; i < 12; i++) {
		if (CheckHitLineToLine(boxEdgesStart[i], boxEdgesEnd[i], LineStart, LineEnd)) {
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitLineToLine(VECTOR LineStart1, VECTOR LineEnd1, VECTOR LineStart2, VECTOR LineEnd2, VECTOR* hitpos) {
	VECTOR dir1 = VSub(LineEnd1, LineStart1);
	VECTOR dir2 = VSub(LineEnd2, LineStart2);
	VECTOR dirdiff = VSub(LineStart1, LineStart2);

	float a = VDot(dir1, dir1);
	float b = VDot(dir1, dir2);
	float c = VDot(dir2, dir2);
	float d = VDot(dir1, dirdiff);
	float e = VDot(dir2, dirdiff);

	float denom = a * c - b * b;
	float s, t;
	const float EPS = 1e-6f;

	if (fabs(denom) < EPS) {
		// parallel
		s = 0.0f;
		t = (fabs(b) > fabs(c) ? d / b : e / c);
	}
	else {
		s = (b * e - c * d) / denom;
		t = (a * e - b * d) / denom;
	}


	if (s < 0.0f) s = 0.0f;
	if (s > 1.0f) s = 1.0f;
	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;

	VECTOR cp1 = VAdd(LineStart1, VScale(dir1, s));
	VECTOR cp2 = VAdd(LineStart2, VScale(dir2, t));
	float dist = VSize(VSub(cp1, cp2));

	return dist < 0.001f;
}



bool Collision::TriangleToBox(VECTOR p0, VECTOR& p1, VECTOR p2, VECTOR center, float size)
{
	//Boxのmin, maxを算出
	VECTOR bmin = {
		center.x - size * 0.5f,
		center.y - size * 0.5f,
		center.z - size * 0.5f
	};
	VECTOR bmax = {
		center.x + size * 0.5f,
		center.y + size * 0.5f,
		center.z + size * 0.5f
	};
	//三角形の頂点がBox内
	auto PointInAABB = [&](const VECTOR& p) {
		return (p.x >= bmin.x && p.x <= bmax.x &&
			p.y >= bmin.y && p.y <= bmax.y &&
			p.z >= bmin.z && p.z <= bmax.z);
		};
	if (PointInAABB(p0) || PointInAABB(p1) || PointInAABB(p2))
		return true;
	//三角形の辺とBoxの交差判定
	auto SegmentAABB = [&](VECTOR s, VECTOR e)
		{
			VECTOR d = { e.x - s.x, e.y - s.y, e.z - s.z };
			float tmin = 0.0f;
			float tmax = 1.0f;
			for (int i = 0; i < 3; i++)
			{
				float s_i = (&s.x)[i];
				float d_i = (&d.x)[i];
				float min_i = (&bmin.x)[i];
				float max_i = (&bmax.x)[i];
				if (fabsf(d_i) < 1e-6f) {
					if (s_i < min_i || s_i > max_i) return false;
				}
				else {
					float ood = 1.0f / d_i;
					float t1 = (min_i - s_i) * ood;
					float t2 = (max_i - s_i) * ood;
					if (t1 > t2) std::swap(t1, t2);
					tmin = max(tmin, t1);
					tmax = min(tmax, t2);
					if (tmin > tmax) return false;
				}
			}
			return true;
		};
	if (SegmentAABB(p0, p1)) return true;
	if (SegmentAABB(p1, p2)) return true;
	if (SegmentAABB(p2, p0)) return true;
	//三角形のエッジ
	VECTOR e0 = VSub(p1, p0);
	VECTOR e1 = VSub(p2, p1);
	VECTOR e2 = VSub(p0, p2);
	//AABB中心基準に座標変換
	VECTOR v0 = VSub(p0, center);
	VECTOR v1 = VSub(p1, center);
	VECTOR v2 = VSub(p2, center);
	//半サイズ
	VECTOR h = { size * 0.5f, size * 0.5f, size * 0.5f };
	//軸テスト関数
	auto TestAxis = [&](VECTOR axis) {
		float p0p = VDot(v0, axis);
		float p1p = VDot(v1, axis);
		float p2p = VDot(v2, axis);
		float minP = min(min(p0p, p1p), p2p);
		float maxP = max(max(p0p, p1p), p2p);
		float r = fabsf(axis.x) * h.x + fabsf(axis.y) * h.y + fabsf(axis.z) * h.z;
		return !(minP > r || maxP < -r);
		};
	//AABB の軸
	if (!TestAxis({ 1,0,0 })) return false;
	if (!TestAxis({ 0,1,0 })) return false;
	if (!TestAxis({ 0,0,1 })) return false;
	//三角形の面の法線
	VECTOR triN = VCross(e0, e1);
	if (!TestAxis(triN)) return false;
	//三角形の 3 エッジ × Box の 3 軸 = 9 軸
	VECTOR edges[3] = { e0, e1, e2 };
	VECTOR axes[3] = { {1,0,0}, {0,1,0}, {0,0,1} };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			VECTOR axis = VCross(edges[i], axes[j]);
			if (VSize(axis) > 1e-6f) {
				if (!TestAxis(axis)) return false;
			}
		}
	}
	// ここまで分離軸なし → 交差
	return true;
}

