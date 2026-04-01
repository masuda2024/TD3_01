#pragma once
#include "KamataEngine.h"
class Skydome 
{
public:
	void Initialize(KamataEngine::Camera* camera, KamataEngine::Model* model, uint32_t textureHandle);
	void Update();
	void Draw();
	
	
private:
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0u;
};
