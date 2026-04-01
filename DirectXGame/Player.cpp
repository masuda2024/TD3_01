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

// 行列の積
Matrix4x4 Multiply2(const Matrix4x4& m1, const Matrix4x4& m2) 
{
	Matrix4x4 result;

	result.m[0][0] = {(m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) + (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0])};
	result.m[0][1] = {(m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) + (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1])};
	result.m[0][2] = {(m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) + (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2])};
	result.m[0][3] = {(m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) + (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3])};

	result.m[1][0] = {(m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) + (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0])};
	result.m[1][1] = {(m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) + (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1])};
	result.m[1][2] = {(m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) + (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2])};
	result.m[1][3] = {(m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) + (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3])};

	result.m[2][0] = {(m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) + (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0])};
	result.m[2][1] = {(m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) + (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1])};
	result.m[2][2] = {(m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) + (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2])};
	result.m[2][3] = {(m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) + (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3])};

	result.m[3][0] = {(m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) + (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0])};
	result.m[3][1] = {(m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) + (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1])};
	result.m[3][2] = {(m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) + (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2])};
	result.m[3][3] = {(m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) + (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3])};

	return result;
}


Matrix4x4 Inverse2(const Matrix4x4& m)
{
	Matrix4x4 result{};
	float determinant =
	    (
			(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
			(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
			(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
			(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
			(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
			(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
			(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
			(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0])

	    );

	result =
	{
	    ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2]) - (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) -
	     (m.m[1][1] * m.m[2][3] * m.m[3][2])) /
	        determinant,

	    (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2]) + (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) +
	     (m.m[0][1] * m.m[2][3] * m.m[3][2])) /
	        determinant,

	    ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2]) - (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) -
	     (m.m[0][1] * m.m[1][3] * m.m[3][2])) /
	        determinant,

	    (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2]) + (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) +
	     (m.m[0][1] * m.m[1][3] * m.m[2][2])) /
	        determinant,

	    //======================================================================================================================================

	    (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2]) + (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) +
	     (m.m[1][0] * m.m[2][3] * m.m[3][2])) /
	        determinant,

	    ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2]) - (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) -
	     (m.m[0][0] * m.m[2][3] * m.m[3][2])) /
	        determinant,

	    (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2]) + (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) +
	     (m.m[0][0] * m.m[1][3] * m.m[3][2])) /
	        determinant,

	    ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2]) - (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) -
	     (m.m[0][0] * m.m[1][3] * m.m[2][2])) /
	        determinant,

	    //======================================================================================================================================

	    ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1]) - (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) -
	     (m.m[1][0] * m.m[2][3] * m.m[3][1])) /
	        determinant,

	    (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) +
	     (m.m[0][0] * m.m[2][3] * m.m[3][1])) /
	        determinant,

	    ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1]) - (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) -
	     (m.m[0][0] * m.m[1][3] * m.m[3][1])) /
	        determinant,

	    (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) +
	     (m.m[0][0] * m.m[1][3] * m.m[2][1])) /
	        determinant,

	    //======================================================================================================================================

	    (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1]) + (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) +
	     (m.m[1][0] * m.m[2][2] * m.m[3][1])) /
	        determinant,

	    ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) -
	     (m.m[0][0] * m.m[2][2] * m.m[3][1])) /
	        determinant,

	    (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1]) + (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) +
	     (m.m[0][0] * m.m[1][2] * m.m[3][1])) /
	        determinant,

	    ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) -
	     (m.m[0][0] * m.m[1][2] * m.m[2][1])) /
	        determinant,

	};

	return result;
}



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

	
	
	




	ImGui::Text("Mouse Control: %s", ON_Mouse ? "ON" : "OFF");
	if (Input::GetInstance()->TriggerKey(DIK_M))
	{
		ON_Mouse = !ON_Mouse;  // 押すたびに反転
		OFF_Mouse = !ON_Mouse; // 逆状態にする
	}


	if (OFF_Mouse)
	{

		// プレイヤーから3Dレティクルへの距離
		const float kDistanceP_To_3DR = 50.0f;
		// プレイヤーから3Dレティクルへのオフセット(X+1向き)
		Vector3 offset = {0, 0, 1.0f};
		// プレイヤーのワールド変換の回転を反映
		offset = TransformNormal(offset, worldTransform_.matWorld_);
		// ベクトルの長さを整える
		offset = Normalize(offset) * kDistanceP_To_3DR;
		// 位置
		worldTransform3DReticle_.translation_ = worldTransform_.translation_ + offset;
	
		worldTransform3DReticle_.translation_ += move;
	}

	if (ON_Mouse)
	{
		/*
		// マウスの移動量を取得する
		Input::MouseMove mouseMove = input_->GetMouseMove();
		

		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetActiveWindow(), &mousePos);

		float windowWidth = 1208.0f;
		float windowHeight = 720.0f;

		float ndcX = (2.0f * mousePos.x) / windowWidth - 1.0f;
		float ndcY = 1.0f - (2.0f * mousePos.y) / windowHeight; // Y軸反転

		Vector3 posNear = {ndcX, ndcY, 0.0f}; // 近面
		Vector3 posFar = {ndcX, ndcY, 1.0f};  // 遠面
		Matrix4x4 matVP = Multiply2(camera_->matView, camera_->matProjection);
		Matrix4x4 matVPInv = Inverse2(matVP);

		Vector3 worldPosNear = Transform(posNear, matVPInv);
		Vector3 worldPosFar = Transform(posFar, matVPInv);

		Vector3 rayDir = worldPosFar - worldPosNear;
		rayDir = Normalize(rayDir);

		const float kDistanceC_To_3DR = 50.0f;
		worldTransform3DReticle_.translation_ = worldPosNear + rayDir * kDistanceC_To_3DR;

		float deltaX = mouseMove.lX / windowWidth * 2.0f;   // NDC
		float deltaY = -mouseMove.lY / windowHeight * 2.0f; // NDC反転

		Vector3 offset = Transform(Vector3{deltaX, deltaY, 0.0f}, matVPInv) - Transform(Vector3{0, 0, 0}, matVPInv);
		worldTransform3DReticle_.translation_ += offset;
		*/




		/**/

		// マウス座標を取得する
		POINT mousePos;
		GetCursorPos(&mousePos);
		// クライアント座標に変換する
		ScreenToClient(GetActiveWindow(), &mousePos); // ウィンドウ座
		
		
		
		
		// マウス座標を3Dレティクルの位置に代入する
		mousePos.x = static_cast<LONG>(worldTransform3DReticle_.translation_.x);
		mousePos.y = static_cast<LONG>(worldTransform3DReticle_.translation_.y);
		//　ビュープロジェクションビューポート合成行列
		Matrix4x4 matVP = Multiply2(camera_->matView, camera_->matProjection);
		// 合成行列の逆行列を計算する
		Matrix4x4 matVPInv = Inverse2(matVP);
		//スクリーン座標
		Vector3 posNear = {(float)mousePos.x, (float)mousePos.y, 0.0f};
		Vector3 posFar = {(float)mousePos.x, (float)mousePos.y, 1.0f};
		//スクリーン座標系からワールド座標系に変換する
		Vector3 worldPosNear = Transform(posNear, matVPInv);
		Vector3 worldPosFar = Transform(posFar, matVPInv);
		//マウスレイの方向
		Vector3 rayDir = worldPosFar - worldPosNear;
		rayDir = Normalize(rayDir);
		// カメラから3Dレティクルへの距離
		const float kDistanceC_To_3DR = 15.0f;
		worldTransform3DReticle_.translation_ = posNear + rayDir * kDistanceC_To_3DR;

		
		//マウスの移動量を取得する
		Input::MouseMove mouseMove = input_->GetMouseMove();
		
		//マウスの移動量を3Dレティクルの位置に加算する
		worldTransform3DReticle_.translation_.x += mouseMove.lX * 1.0f; // 移動量を調整するために0.1倍する
		worldTransform3DReticle_.translation_.y -= mouseMove.lY * 1.0f; // 移動量を調整するために0.1倍する

		














	}







	

#pragma endregion



	//座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;

	
	
	// 行列更新
	worldTransform3DReticle_.matWorld_ = MakeAffineMatrix(worldTransform3DReticle_.scale_, worldTransform3DReticle_.rotation_, worldTransform3DReticle_.translation_);
	worldTransform3DReticle_.TransferMatrix();

	
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


	


	if (input_->TriggerKey(DIK_SPACE) || input_->IsTriggerMouse(0))
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