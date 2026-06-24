#pragma once
#include "../Actor/Charactor/CharactorBase.h"
#include "../../Application.h"

class Player;
class GameScene;

class Player1Ui :public CharactorBase
{

public:
	//アイコンサイズ
	static constexpr float ICON_SIZE = 0.4f;

	//ＨＰバーサイズ調整
	static constexpr float HP_BAR_SIZE_MAX = (float)Application::SCREEN_SIZE_X / 2 - 70;
	//ＨＰバーの高さ
	static constexpr int HP_BAR_SIZE_Y = 40;

	// コンストラクタ
	Player1Ui(Player* player,GameScene*game);

	// デストラクタ
	~Player1Ui(void) override;

	

	void Draw(void)override;

	// 解放
	void Release(void)override;

private:

	//プレイヤー
	Player* player_;

	//ゲームシーン
	GameScene* game_;

protected:
	// リソースロード
	void InitLoad(void)override;

	// 大きさ、回転、座標の初期化
	void InitTransform(void)override;

	// 衝突判定の初期化
	void InitCollider(void)override;

	// アニメーションの初期化
	void InitAnimation(void)override;

	// 初期化後の個別処理
	void InitPost(void)override;

	// 更新系
	void UpdateProcess(void)override;
	void UpdateProcessPost(void)override;

	///長さレベル
	void LengthLevelSet(LEVEL_LENGTH length) override {}
	///半径レベル
	void RadiusLevelSet(LEVEL_RADIUS radius) override {}
	///スピードレベル
	void SpeedLevelSet(LEVEL_SPEED speed) override {}
	///攻撃レベル
	void AttackLevelSet(LEVEL_ATTACK attack) override {}

	void Respawn(void) override {}

};