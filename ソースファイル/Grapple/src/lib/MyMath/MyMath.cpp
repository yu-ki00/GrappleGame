#include<DxLib.h>
#include<math.h>
#include"MyMath.h"


float CMyMath::GetDistance(float PosX, float PosY, float posx, float posy) {  //‚Q“_ŠÔ‚Ì‹——£
	float x, y;
	float num;
	x = posx - PosX;
	y = posy - PosY;
	num = (x * x) + (y * y);
	return sqrtf(num);
}
VECTOR CMyMath::AddVector(VECTOR A, VECTOR B) {
	VECTOR res;
	res.x = A.x + B.x;
	res.y = A.y + B.y;
	res.z = A.z + B.z;
	return res;
}
VECTOR CMyMath::SubVector(VECTOR A, VECTOR B) {
	A.x -= B.x;
	A.y -= B.y;
	A.z -= B.z;
	return A;
}
VECTOR CMyMath::CreateVec(VECTOR endPos, VECTOR startPos) {
	VECTOR res;
	res.x = endPos.x - startPos.x;
	res.y = endPos.y - startPos.y;
	res.z = endPos.z - startPos.z;
	return res;
}
float CMyMath::GetVecLength(VECTOR vec) {
	float len;
	len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return len;
}
VECTOR CMyMath::VecNorm(VECTOR vec, float length) {
	VECTOR res;
	res.x = vec.x / length;
	res.y = vec.y / length;
	res.z = vec.z / length;
	return res;
}
VECTOR CMyMath::VecScale(VECTOR vec, float scale) {
	VECTOR res;
	res.x = vec.x * scale;
	res.y = vec.y * scale;
	res.z = vec.z * scale;
	return res;
}
float CMyMath::VecDot(VECTOR vec1, VECTOR vec2) {
	float ret;
	ret = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return ret;
}
MATRIX CMyMath::GetIdentityMatrix() {
	MATRIX ret = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				ret.m[i][j] = 1;
			}
			else {
				ret.m[i][j] = 0;
			}
		}
	}
	return ret;
}
MATRIX CMyMath::GetTranslateMatrix(VECTOR trans) {
	MATRIX ret = GetIdentityMatrix();
	ret.m[0][3] = trans.x;
	ret.m[1][3] = trans.y;
	ret.m[2][3] = trans.z;
	return ret;
}
MATRIX CMyMath::GetTranslateVecMatrix(float x, float y, float z) {
	MATRIX ret = GetIdentityMatrix();
	ret.m[0][3] = x;
	ret.m[1][3] = y;
	ret.m[2][3] = z;
	return ret;
}

MATRIX CMyMath::GetScaleMatrix(VECTOR scale) {
	MATRIX ret = GetIdentityMatrix();
	ret.m[0][0] = scale.x;
	ret.m[1][1] = scale.y;
	ret.m[2][2] = scale.z;
	return ret;
}
//XŽ²‰ñ“]s—ñ‚ðŽæ“¾‚·‚é
MATRIX CMyMath::GetPitchMatrix(float radx) {
	MATRIX ret = GetIdentityMatrix();
	ret.m[1][1] = cosf(radx);
	ret.m[1][2] = -(sinf(radx));
	ret.m[2][1] = sinf(radx);
	ret.m[2][2] = cosf(radx);
	return ret;
}
//YŽ²‰ñ“]s—ñ‚ðŽæ“¾‚·‚é
MATRIX CMyMath::GetYawMatrix(float rady) {
	MATRIX ret = GetIdentityMatrix();
	ret.m[0][0] = cosf(rady);
	ret.m[0][2] = sinf(rady);
	ret.m[2][0] = -sinf(rady);
	ret.m[2][2] = cosf(rady);
	return ret;
}
//ZŽ²‰ñ“]s—ñ‚ðŽæ“¾‚·‚é
MATRIX CMyMath::GetRollMatrix(float radz) {
	MATRIX ret = GetIdentityMatrix();
	ret.m[0][0] = (float)cos(radz);
	ret.m[0][1] = -(sinf(radz));
	ret.m[1][0] = sinf(radz);
	ret.m[1][1] = cosf(radz);
	return ret;

}
//ˆø”‚Å“n‚³‚ê‚½‚Q‚Â‚Ìs—ñ‚ð‘«‚µŽZ‚·‚é
MATRIX CMyMath::MatAdd(MATRIX Mat1, MATRIX Mat2) {
	MATRIX ret = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = Mat1.m[i][j] + Mat2.m[i][j];
		}
	}
	return ret;
}
//ˆø”‚Å“n‚³‚ê‚½s—ñ‚ðƒXƒJƒ‰[”{‚·‚é
MATRIX CMyMath::MatScale(MATRIX Mat, float scal) {
	MATRIX ret = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = Mat.m[i][j] * scal;
		}
	}
	return ret;
}
//ˆø”‚Å“n‚³‚ê‚½‚Q‚Â‚Ìs—ñ‚ÌŠ|‚¯ŽZ‚ðs‚¤
MATRIX CMyMath::MatMult(MATRIX Mat1, MATRIX Mat2) {
	MATRIX ret = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int n = 0; n < 4; n++) {
				ret.m[i][j] += (Mat1.m[i][n] * Mat2.m[n][j]);
			}
		}
	}
	return ret;
}
//s—ñ~ƒxƒNƒgƒ‹‚ðs‚¤i•ÏŠ·ŒvŽZj
VECTOR CMyMath::MatTransform(MATRIX Mat, VECTOR vec) {
	VECTOR ret = { 0,0,0 };
	float work[4] = { 0 };
	float ret_buf[4] = { 0 };
	work[0] = vec.x;
	work[1] = vec.y;
	work[2] = vec.z;
	work[3] = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret_buf[i] += (Mat.m[i][j] * work[j]);
		}
	}
	ret.x = ret_buf[0];
	ret.y = ret_buf[1];
	ret.z = ret_buf[2];
	return ret;

	

}
//s—ñ“]’u‚ðs‚¤
MATRIX CMyMath::MatTranspose(MATRIX Mat) {
	MATRIX ret = GetIdentityMatrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = Mat.m[j][i];
		}
	}
	return ret;
}
float CMyMath::DegRad(float deg) { return deg * (DX_PI_F / 180); }

