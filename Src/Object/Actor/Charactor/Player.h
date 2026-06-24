#pragma once
#include "CharactorBase.h"

class GameScene;
class Camara;
class PlayerB;

class Player :
    public CharactorBase
{
public:

	//初期値
	//座標
	static constexpr VECTOR INIT_POS = { -1000.0f, 0.0f, 0.0f };
	
	//エフェクト調整
	static constexpr float EFFECT_RADIUS_SCALE = 2.0f;
	static constexpr float EFFECT_RADIUS_OFFSET = 10.0f;
	static constexpr float EFFECT_LENGTH_DIVISOR = 10.0f;
	static constexpr float EFFECT_LENGTH_OFFSET = 20.0f;

	// コンストラクタ
	Player(GameScene*game);

	// デストラクタ
	~Player(void);

	void Draw(void)override;

	// 解放
	void Release(void)override;

	//hp
	int GetHp(void) const override { return hp_; }

	//attack
	int GetAttack(void) const override { return attack_; }

	Wepon* GetWepon(void);

	bool IsWepon(void);

	//プレイヤーの強化
	void PowerUp(void);
	void SetPlayer(PlayerB* playerB) { playerB_ = playerB; }

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

	void Respawn(void) override;

	
private:

	GameScene* game_;
	PlayerB* playerB_;
	bool isWepon_;
	
	

	
	
	// 衝突判定用カプセル上部球体
	static constexpr VECTOR COL_CAPSULE_TOP_LOCAL_POS = { 0.0f, 1.0f, 0.0f };
	// 衝突判定用カプセル下部球体
	static constexpr VECTOR COL_CAPSULE_DOWN_LOCAL_POS = { 0.0f, -1.0f, 0.0f };
	
	// ジャンプ力
	static constexpr float POW_JUMP_INIT = 3500.0f;
	// 持続ジャンプ力
	static constexpr float POW_JUMP_KEEP = 400.0f;
	// ジャンプ受付時間
	static constexpr float TIME_JUMP_INPUT = 0.5f;
	


	// 操作
	void ProcessMove(void);
	void ProcessJump(void);
	void ProcessHit(void);

	

	//攻撃処理
	virtual void ProcessAttack(void);


	// 衝突判定
	void CollisionReserve(void) override;	

	//レベル設定
	
	///長さレベル
	void LengthLevelSet(LEVEL_LENGTH length) override;
	///半径レベル
	void RadiusLevelSet(LEVEL_RADIUS radius) override;
	///スピードレベル
	void SpeedLevelSet(LEVEL_SPEED speed) override;
	///攻撃力レベル
	void AttackLevelSet(LEVEL_ATTACK attack) override;

	

};

