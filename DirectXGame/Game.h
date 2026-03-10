#pragma once
#include "KamataEngine.h"

#include "Fade.h"

class Game 
{
public:
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();
	// デストラクタ
	~Game();




	// 終了フラグ
	bool finishedGAME_ = false;
	// デス(オーバー)フラグのgetter
	bool IsFinishedGAME() const { return finishedGAME_; } // ゲームオーバー

	// 敵を倒した場合の(クリア)フラグ
	bool finishedGAME2_ = false;
	bool IsFinishedGAME2() const { return finishedGAME2_; } ////ゲームクリア




private:




	#pragma region フェーズ・フェード

	// ゲームのフェーズ(型)
	enum class Phase
	{
		kFadeIn,     // フェードイン
		kPlay,       // ゲームプレイ
		kDeath,      // プレイヤーのデス演出
		kEnemyDeath, // 敵のデス演出
		kFadeOut,    // フェードアウト(オーバー)
		kFadeOut2,   // フェードアウト(クリア)
	};

	// ゲームの現在フェーズから開始
	Phase phase_;

	// フェーズの切り替え
	void ChangePhase();

	// フェード
	Fade* fade_ = nullptr;
#pragma endregion



};
