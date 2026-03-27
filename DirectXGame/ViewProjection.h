#pragma once
#include "KamataEngine.h"

class ViewProjection 
{
public:
	void Initialize();
	void UpdateMatrix();

	KamataEngine::Vector3 translation_ = {0, 0, -10};
	KamataEngine::Vector3 rotation_ = {0, 0, 0};

	KamataEngine::Matrix4x4 matView_;
	KamataEngine::Matrix4x4 matProjection_;
};
