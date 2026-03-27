#include "ViewProjection.h"
#include "math.h"

using namespace KamataEngine;
using namespace MathUtility;

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) 
{
	Matrix4x4 result{};

	for (int row = 0; row < 4; row++) 
	{
		for (int column = 0; column < 4; column++)
		{

			result.m[row][column] = m1.m[row][0] * m2.m[0][column] + m1.m[row][1] * m2.m[1][column] + m1.m[row][2] * m2.m[2][column] + m1.m[row][3] * m2.m[3][column];
		}
	}

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	// スケール行列
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	// 回転行列
	Matrix4x4 rotateX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(rotate.z);

	Matrix4x4 rotateMatrix = Multiply(Multiply(rotateX, rotateY), rotateZ);

	// 平行移動行列
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	// アフィン変換
	Matrix4x4 worldMatrix = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);

	return worldMatrix;
}

void ViewProjection::Initialize()
{

	// 透視投影行列
	matProjection_ = MakePerspectiveFovMatrix
	(
	    0.45f, // FOV
	    (float)1280 / 720, 
		0.1f, 1000.0f
	);
}

void ViewProjection::UpdateMatrix() 
{

	// カメラのワールド行列
	Matrix4x4 cameraMatrix = MakeAffineMatrix
	(
		{1, 1, 1},
		rotation_,
		translation_
	);

	// 逆行列 = View行列
	matView_ = Inverse(cameraMatrix);
}