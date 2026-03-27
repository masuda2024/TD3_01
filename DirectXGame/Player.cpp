#include "Player.h"

#include <cassert>
#include<numbers>
#include<algorithm>
#include<list>
#define NOMINMAX
#include "math.h"
#include "MyMath.h"

using namespace KamataEngine;
using namespace MathUtility;







void Player::Initialize(Model* model, Camera* camera, KamataEngine::Vector3& position)
{
	// NULLポイントチェック
	assert(model);

	model_ = model;

	
	// textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	camera_ = camera;



	//カーソル
	modelCursor_ = Model::CreateFromOBJ("Cursor", true);
	
	//3Dレティクルのワールド変換を初期化
	worldTransform3DReticle_.Initialize();
	worldTransform3DReticle_.translation_ = position;
	worldTransform3DReticle_.rotation_.y = std::numbers::pi_v<float> / 2.0f;




	//シングルトンインスタンスを取得する
	input_ = KamataEngine::Input::GetInstance();
	
	
}

void Player::Update()
{ 

#pragma region プレイヤーの移動


	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A))
	{
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_D))
	{
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_W))
	{
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_S))
	{
		move.y -= kCharacterSpeed;
	}

	//移動限界座標
	const float kMoveLimitX = 60.0f;
	const float kMoveLimitY = 30.0f;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);





#pragma endregion


#pragma region プレイヤーの攻撃
	Attack();
	

	for (P_Bullet* p_bullet : p_bullets_)
	{
		p_bullet->Update();
	}

	
#pragma endregion


#pragma region 3Dレティクル

	

	//プレイヤーから3Dレティクルへの距離
	const float kDistanceP_To_3DR = 50.0f;
	//プレイヤーから3Dレティクルへのオフセット(X+1向き)
	Vector3 offset = {0, 0, 1.0f};
	//プレイヤーのワールド変換の回転を反映
	offset = TransformNormal(offset, worldTransform_.matWorld_);
	//ベクトルの長さを整える
	offset = Normalize(offset) * kDistanceP_To_3DR;
	// 位置
	worldTransform3DReticle_.translation_ = worldTransform_.translation_ + offset;

	// 行列更新
	worldTransform3DReticle_.matWorld_ = MakeAffineMatrix(worldTransform3DReticle_.scale_, worldTransform3DReticle_.rotation_, worldTransform3DReticle_.translation_);
	worldTransform3DReticle_.TransferMatrix();

#pragma endregion





	//座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;

	worldTransform3DReticle_.translation_ += move;
	
	
	
	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();


	


}

void Player::Draw() 
{
	if (isDead_)
	{
		return;
	}


	model_->Draw(worldTransform_, *camera_); 
	

	
	for (P_Bullet* p_bullet : p_bullets_)
	{
		p_bullet->Draw(*camera_);
	}
	
	modelCursor_->Draw(worldTransform3DReticle_,*camera_);
}

Player::~Player()
{ 
	//弾の解放
	for (P_Bullet* p_bullet : p_bullets_)
	{
		delete p_bullet;
	}
	
	delete modelCursor_;
}

#pragma region プレイヤーの動き

void Player::RotateX() 
{
	//回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.007f;
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_W))
	{
		worldTransform_.rotation_.x -= kRotSpeed;
	} else if (input_->PushKey(DIK_S))
	{
		worldTransform_.rotation_.x += kRotSpeed;
	}
}

void Player::RotateZ()
{
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed2 = 0.01f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_W))
	{
		worldTransform_.rotation_.z -= kRotSpeed2;
	} else if (input_->PushKey(DIK_S)) 
	{
		worldTransform_.rotation_.z += kRotSpeed2;
	}
}

void Player::Attack() 
{


	


	if (input_->TriggerKey(DIK_SPACE))
	{
		//弾の速度
		const float kBulletSpeed = 1.0f;
		KamataEngine::Vector3 velocity(0, 0, kBulletSpeed);



		//弾を生成し、初期化
		P_Bullet* new_p_Bullet = new P_Bullet();
		new_p_Bullet->Initialize(model_, worldTransform_.translation_, velocity);
		//弾を登録する
		p_bullets_.push_back(new_p_Bullet);

		velocity_ = worldTransform3DReticle_.translation_ - worldTransform_.translation_;
		velocity_ = Normalize(velocity_) * kBulletSpeed;

	}
}

#pragma endregion 

#pragma region 衝突判定 [ プレイヤー  <<===>>  敵の弾 ]

KamataEngine::Vector3 Player::GetWorldPosition() 
{
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}



void Player::OnCollisionP()
{
	hp_ -= 100;
	if (hp_ <= 0) 
	{
		hp_ = 0;
		isDead_ = true;
	}
}


#pragma endregion