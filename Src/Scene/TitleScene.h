#pragma once
#include "SceneBase.h"
#include "../Object/Common/Transform.h"
#include "../Object/Common/AnimationController.h"

class SkyDome;

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);
	// デストラクタ
	~TitleScene(void) override;

	void Init(void) override;	// 初期化
	void Update(void)override;	// 更新
	void Draw(void)override;	// 描画
	void Release(void)override;	// 解放

private:

	// タイトル文字初期座標
	static const int BASE_TITLE_ROG_POS_X = 600;
	static const int BASE_TITLE_ROG_POS_Y = 250;
	// タイトル文字サイズ
	static const int TITLE_ROG_SIZE = 150;
	// タイトル文字の間隔
	static const int ROG_POS_NO_SECOND = 2;

	// ゲームスタート文字初期座標
	static const int ACENE_CHANGE_POS_X = 250;
	static const int ACENE_CHANGE_POS_Y = 800;
	// ゲームスタート文字サイズ
	static const int ACENE_CHANGE_SIZE = 96;
	// ゲームスタート文字の間隔
	static const int BASE_SIZE = 16;

	//色の最大値
	static const int COLOR_MAX = 255;

	//点滅カウント初期値
	static const int CHANGE_COUNT_INIT = 1;
	//点滅の間隔
	static const int CHANGE_COUNT = 5;
	//点滅カウント最大値
	static const int CHANGE_COUNT_MAX = 12;

	//BGMの音量
	static const int BGM_VOLUME = 100;

	// 点滅用カウントフラグ
	bool isChange;

	// 背景画像ハンドル
	int img_;
	// 点滅用カウント
	int count;
	// 点滅用カウントの最大値
	int countChange;
	
};
