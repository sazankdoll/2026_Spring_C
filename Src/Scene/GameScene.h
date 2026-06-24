#pragma once
#include "SceneBase.h"
#include "../Application.h"

class SkyDome;
class Stage;
class Player;
class PlayerB;
class Player1Ui;
class Player2Ui;
class ItemBase;
class Timer;

class GameScene : public SceneBase
{
public:
	
	// コンストラクタ
	GameScene(Timer*timer);
	// デストラクタ
	~GameScene(void) override;

	void Init(void) override;	// 初期化
	void Update(void)override;	// 更新
	void Draw(void)override;	// 描画
	void Release(void)override;	// 解放

	//各hpの振動
	void HpShakeP1(void);
	void HpShakeP2(void);

	//各攻撃振動フラグ・時間を設定
	void SetShakeP1(bool flag, int time) { ShakeFlagP1_ = flag; ShakeTimeP1_ = time; }
	void SetShakeP2(bool flag, int time) { ShakeFlagP2_ = flag; ShakeTimeP2_ = time; }

	//各攻撃振動の座標を取得
	int GetShakePosP1(void) { return ShakePosP1_; }
	int GetShakePosP2(void) { return ShakePosP2_; }

private:

	//テキスト座標
	static constexpr int TEXT_POS = 10;
	//振動幅
	static constexpr int SHAKE_WIDTH = 5;
	//bgmの音量
	static constexpr int BGM_VOLUME = 40;

	//スカイドーム
	SkyDome* skydome_;

	//ステージ
	Stage* stage_;

	//プレイヤー
	Player* player_;
	PlayerB* playerB_;

	//プレイヤーUI
	Player1Ui* player1Ui_;
	Player2Ui* player2Ui_;

	//アイテム
	ItemBase* itemBase_;

	//タイマー
	Timer* timer_;

	//シャドウマップハンドル
	int ShadowMapHandle;

	//振動関係P1
	//座標
	int ShakePosP1_;
	//振動時間
	int ShakeTimeP1_;
	//振動フラグ
	bool ShakeFlagP1_;
	
	//振動関係P2
	//座標
	int ShakePosP2_;
	//振動時間
	int ShakeTimeP2_;
	//振動フラグ
	bool ShakeFlagP2_;

	//当たり判定初期化
	void InitCollider(void);
	
	//当たり判定更新
	void UpdateCollider(void);
};
