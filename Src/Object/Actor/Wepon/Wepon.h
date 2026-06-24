#pragma once
#include "../ActorBase.h"
class Wepon :
    public ActorBase
{
public:

	// コンストラクタ
	Wepon(const ColliderBase::TAG& tag, const VECTOR& statePos, const VECTOR& endPos,
		const float& length = 500.0f, const float& speed = 50.0f, const float& radius = 30.0f);
	// デストラクタ
	~Wepon(void);

	void Update(void)override;	// 更新
	void Draw(void)override;	// 描画
	void Release(void)override;	// 解放

	//生存フラグ
	bool IsAlive(void);

	//光体の後ろ座標の取得
	VECTOR GetEndPos(void) { return downPos_; }

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

private:

	//光体が消失するまでの長さ
	static constexpr float DISAPPEAR_LENGTH = 1.0f;

	//光体のタグ
	ColliderBase::TAG tag_;

	//消失する座標
	VECTOR endPos_;
	//光体の後ろ座標
	VECTOR downPos_;
	// 移動方向
	VECTOR moveDir_;
	// 移動量
	VECTOR movePow_;
	// 移動前の座標
	VECTOR prevPos_;

	//長さ
	float length_;
	// 移動スピード
	float moveSpeed_;
	// 衝突判定用球体半径
	float radius_;

	//移動処理
	void Move(void);
};

