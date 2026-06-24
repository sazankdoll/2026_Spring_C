#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/Camera.h"
#include "../Object/Actor/Stage/SkyDome.h"
#include "../Object/point.h"
#include "../Object/Timer/Timer.h"
#include "ResultScene.h"

ResultScene::ResultScene(Timer*timer)
	:
	img_(-1),
	p1Hp_(-1),
	p2Hp_(-1),
	timer_(timer),
	SceneBase()
{
}

ResultScene::~ResultScene(void)
{
}

void ResultScene::Init(void)
{
	// リソースロード
	img_ = resMng_.Load(ResourceManager::SRC::TITLE_IMG).handleId_;
	bgm_ = resMng_.Load(ResourceManager::SRC::RESULT_BGM).handleId_;

	// BGM再生初期化
	volume_ = BGM_VOLUME;
	sonMng_.PlayBGM(bgm_, volume_);

	// 各プレイヤーのHPを取得
	p1Hp_ = Point::GetInstance()->GetpHp();
	p2Hp_ = Point::GetInstance()->GetpBhp();

}

void ResultScene::Update(void)
{
	//シーン遷移
	auto const& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE)
		|| ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)
		|| ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN)
		|| timer_->GetMin() <= 0 && timer_->GetSec() <= 0)
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void ResultScene::Draw(void)
{
	// 背景画像描画
	DrawGraph(0, 0, img_, TRUE);

	// 結果表示
	SetFontSize(RESULT_TEXT_SIZE_MAX);
	if (p1Hp_ > p2Hp_ )
	{
		DrawFormatString(RESULT_TEXT_WIN_POS_X, RESULT_TEXT_POS_Y, 0xffff00, "Player1 Win");
	}
	else if (p1Hp_ <p2Hp_)
	{
		DrawFormatString(RESULT_TEXT_WIN_POS_X, RESULT_TEXT_POS_Y, 0xffff00, "Player2 Win");
	}
	else if (p1Hp_ == p2Hp_)
	{
		DrawFormatString(RESULT_TEXT_DRAW_POS_X, RESULT_TEXT_POS_Y, 0xffff00, "Draw");
	}
	
	// 遷移文字表示
	DrawString(RESULT_TEXT_TRANSITION_POS_X, RESULT_TEXT_TRANSITION_POS_Y, "スペース(Aボタン)でスタート画面へ", 0xffffff);
	SetFontSize(RESULT_TEXT_SIZE_MIN);
}

void ResultScene::Release(void)
{
}
