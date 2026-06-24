#pragma once
#include "SceneBase.h"
class Timer;

class ResultScene :public SceneBase
{
public:
	
	// コンストラクタ
	ResultScene(Timer*timer);
	// デストラクタ
	~ResultScene(void) override;

	void Init(void) override;	// 初期化
	void Update(void)override;	// 更新
	void Draw(void)override;	// 描画
	void Release(void)override;	// 解放

private:

	//リザルトテキストの標準
	//WIN座標
	static constexpr int RESULT_TEXT_WIN_POS_X = 700;
	static constexpr int RESULT_TEXT_POS_Y = 230;
	//DRAW座標
	static constexpr int RESULT_TEXT_DRAW_POS_X = 850;
	//遷移表示座標
	static constexpr int RESULT_TEXT_TRANSITION_POS_X = 250;
	static constexpr int RESULT_TEXT_TRANSITION_POS_Y = 800;
	//サイズ
	static constexpr int RESULT_TEXT_SIZE_MAX = 96;
	static constexpr int RESULT_TEXT_SIZE_MIN = 16;
	//BGMボリューム
	static constexpr int BGM_VOLUME = 50;

	// タイマー
	Timer* timer_;

	// 背景画像ハンドル
	int img_;
	//各プレイヤーのHP
	int p1Hp_;
	int p2Hp_;

};

