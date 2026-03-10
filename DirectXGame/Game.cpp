#include "Game.h"






using namespace KamataEngine;
using namespace MathUtility;




void Game::Initialize()
{


#pragma region フェーズ・フェード
	// フェーズインから開始
	phase_ = Phase::kFadeIn;
	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
#pragma endregion





}

void Game::Update()
{
	// フェード
	fade_->Update();
	ImGui::Text("C : Clear  ,  O : Over");


	switch (phase_)
	{ 
	case Phase::kPlay:

#pragma region 仮設コード
		//ゲームクリア(仮)
		if (Input::GetInstance()->TriggerKey(DIK_C))
		{
			phase_ = Phase::kEnemyDeath;
		}
		// ゲームオーバー(仮)
		if (Input::GetInstance()->TriggerKey(DIK_O)) 
		{
			phase_ = Phase::kDeath;
		}
#pragma endregion







		break;

	case Phase::kDeath:



		// フェードアウト開始
		phase_ = Phase::kFadeOut;
		fade_->Start(Fade::Status::FadeOut, 1.0f);



		break;

	case Phase::kEnemyDeath:



		// フェードアウト開始
		phase_ = Phase::kFadeOut2;
		fade_->Start(Fade::Status::FadeOut, 1.0f);


		break;

	case Phase::kFadeIn:
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			phase_ = Phase::kPlay;
		}
		break;
	case Phase::kFadeOut:
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			finishedGAME_ = true;
		}
		break;
	case Phase::kFadeOut2:
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			finishedGAME2_ = true;
		}
		break;



	}

	


}

void Game::Draw()
{ 
	//スプライト
	Sprite::PreDraw();



	Sprite::PostDraw();


	//モデル
	Model::PreDraw();



	Model::PostDraw();


}

Game::~Game()
{
	// フェードの解放
	delete fade_;
}