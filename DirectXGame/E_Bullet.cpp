#include "E_Bullet.h"
using namespace KamataEngine;
#include "MyMath.h"


void E_Bullet::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity)
{
	assert(model);

	model_ = model;

	model_E_Bullet_ = model;

	EB_velocity_ = velocity;

	model_E_Bullet_ = KamataEngine::Model::CreateFromOBJ("E_bullet");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void E_Bullet::Update() 
{
	// 弾の速度(X軸方向)
	EB_velocity_.x = 1.0f;

	// 座標を移動させる (1フレーム分の移動量)
	worldTransform_.translation_.x -= EB_velocity_.x;

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}



void E_Bullet::Draw(const KamataEngine::Camera& camera)
{
	
	model_E_Bullet_->Draw(worldTransform_, camera);
}

#pragma region 衝突判定 [ プレイヤー  <<===>>  敵の弾 ]

KamataEngine::Vector3 E_Bullet::GetWorldPosition()
{
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


#pragma endregion

void E_Bullet::OnCollision()
{
	//is_EB_Dead_ = true; 
}