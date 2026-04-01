#include "Skydome.h"
using namespace KamataEngine;
using namespace MathUtility;
void Skydome::Initialize(KamataEngine::Camera* camera, KamataEngine::Model* model, uint32_t textureHandle)
{
	
	assert(model);
	camera = camera_;
	model = model_;
	textureHandle = textureHandle_;

	worldTransform_.Initialize();
	
	
}

void Skydome::Update() 
{
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	
}

void Skydome::Draw() 
{ 
	model_->Draw(worldTransform_, *camera_);
	

}

