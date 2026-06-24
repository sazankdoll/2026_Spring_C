#pragma once
#include "../ActorBase.h"
class WeponMark :
	public ActorBase
{
public:

	// コンストラクタ
	WeponMark(const VECTOR& pos, const int color);

	// デストラクタ
	~WeponMark(void);

	void Update(void)override;	// 更新
	void Draw(void)override;	// 描画
	void Release(void)override;	// 解放

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

	//マークの半径
	static constexpr float RADIUS = 15.0f;
	//マークの分割数
	static constexpr int DIV_NUM = 10;

	//マークの色
	int color_;

};

