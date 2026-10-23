#pragma once
#include<DxLib.h>
class CMyMath {
public:
	//floatのposどうしの距離
	static float GetDistance(float PosX, float PosY, float posx, float posy);

	//VECTORの足し算
	static VECTOR AddVector(VECTOR A, VECTOR B);

	//VECTORの引き算
	static VECTOR SubVector(VECTOR A, VECTOR B);

	//ベクトルの生成
	static VECTOR CreateVec(VECTOR endPos, VECTOR startPos);

	//ベクトルの長さを取得
	static float GetVecLength(VECTOR vec);

	//ベクトルを正規化
	static VECTOR VecNorm(VECTOR vec, float length);

	//ベクトルのスカラー倍
	static VECTOR VecScale(VECTOR vec, float scale);

	//内積
	static float VecDot(VECTOR vec1, VECTOR vec2);

	//単位行列を取得する
	static MATRIX GetIdentityMatrix();

	//平行移動行列を取得する
	static MATRIX GetTranslateMatrix(VECTOR trans);


	static MATRIX GetTranslateVecMatrix(float x, float y, float z);

	//拡縮行列を取得する
	static MATRIX GetScaleMatrix(VECTOR scale);

	//X軸回転行列を取得する
	static MATRIX GetPitchMatrix(float radx);

	//Y軸回転行列を取得する
	static MATRIX GetYawMatrix(float rady);

	//Z軸回転行列を取得する
	static MATRIX GetRollMatrix(float radz);

	//引数で渡された２つの行列を足し算する
	static MATRIX MatAdd(MATRIX Mat1, MATRIX Mat2);

	//引数で渡された行列をスカラー倍する
	static MATRIX MatScale(MATRIX Mat, float scal);

	//引数で渡された２つの行列の掛け算を行う
	static MATRIX MatMult(MATRIX Mat1, MATRIX Mat2);

	//行列×ベクトルを行う（変換計算）
	static VECTOR MatTransform(MATRIX Mat, VECTOR vec);

	//行列転置を行う
	static MATRIX MatTranspose(MATRIX Mat);

	//ディグリーからラジアンへの変換
	static float DegRad(float deg);
};
