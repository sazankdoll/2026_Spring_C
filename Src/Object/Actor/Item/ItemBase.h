#pragma once
#include "../Charactor/CharactorBase.h"

class GameScene;
class Player;
class PlayerB;

class ItemBase :
	public CharactorBase
{
public:

	// 衝突判定用線分開始
	static constexpr VECTOR COL_LINE_START_LOCAL_POS = { 0.0f, 80.0f, 0.0f };
	// 衝突判定用線分終了
	static constexpr VECTOR COL_LINE_END_LOCAL_POS = { 0.0f, -120.0f, 0.0f };;

	// コンストラクタ
	ItemBase(GameScene* game, Player* player, PlayerB* playerB);

	// デストラクタ
	~ItemBase(void);

	void Draw(void)override;

	// 解放
	void Release(void)override;

	//生存フラグ
	bool IsItem(void);

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

	void LengthLevelSet(LEVEL_LENGTH length)override;
	void RadiusLevelSet(LEVEL_RADIUS radius)override;
	void SpeedLevelSet(LEVEL_SPEED speed)override;
	void AttackLevelSet(LEVEL_ATTACK attack)override {}

	void Respawn(void)override ;
	
private:



	static constexpr VECTOR ITEM_POS = { 0.0f, 20.0f, 0.0f };//アイテムの座標
	static constexpr int ITEM_COUNT = 300;//アイテムのリスポーン時間

	//リスポーン座標
	static constexpr VECTOR RESPAWN_POS_A = { -1000.0f, 20.0f, -1000.0f };
	static constexpr VECTOR RESPAWN_POS_B = { 1000.0f, 20.0f, -1000.0f };
	static constexpr VECTOR RESPAWN_POS_C = { -1000.0f, 20.0f, -1000.0f };
	static constexpr VECTOR RESPAWN_POS_D = { 1000.0f, 20.0f, 1000.0f };
	static constexpr VECTOR RESPAWN_POS_E = { -1000.0f, 20.0f, 1000.0f };
	static constexpr VECTOR RESPAWN_POS_F = { -2000.0f, 20.0f, -1000.0f };
	static constexpr VECTOR RESPAWN_POS_G = { -2000.0f, 20.0f, 1000.0f };
	static constexpr VECTOR RESPAWN_POS_H = { 2000.0f, 20.0f, -1000.0f };
	static constexpr VECTOR RESPAWN_POS_I = { 2000.0f, 20.0f, 1000.0f };

	//SE
	int getItemP1SeHandle_;
	int getItemP2SeHandle_;
	int crashSeHandle_;



	GameScene* game_;
	Player* player_;
	PlayerB* playerB_;

	//アイテムのタグ
	ColliderBase::TAG tag_;

	//アイテム座標
	VECTOR pos_;

	bool isAlive_;
	int resetCount_;

	// 衝突判定用カプセル上部球体
	static constexpr VECTOR COL_CAPSULE_TOP_LOCAL_POS = { 0.0f, 1.0f, 0.0f };
	// 衝突判定用カプセル下部球体
	static constexpr VECTOR COL_CAPSULE_DOWN_LOCAL_POS = { 0.0f, -1.0f, 0.0f };

	static constexpr float COL_RADIUS = 110.0f;

	// 衝突判定用球体半径
	float radius_;

	bool isItem_;

	// 衝突判定
	void CollisionReserveP1(void);
	void CollisionReserveP2(void);


	////レベル設定
	////長さレベル
	//void LengthLevelSet(LEVEL_LENGTH length) override;
	////半径レベル
	//void RadiusLevelSet(LEVEL_RADIUS radius) override;
	////スピードレベル
	//void SpeedLevelSet(LEVEL_SPEED speed) override;

};




