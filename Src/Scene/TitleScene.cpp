#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/Camera.h"
#include "../Object/Actor/Stage/SkyDome.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
	:
	img_(),
	count(0),
	countChange(0),
	isChange(false),
	SceneBase()
{
	count = CHANGE_COUNT_INIT;
	countChange = 0;
	isChange = false;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	// リソースロード
	img_=resMng_.Load(ResourceManager::SRC::TITLE_IMG).handleId_;
	bgm_ = resMng_.Load(ResourceManager::SRC::TITLE_BGM).handleId_;
	volume_ = BGM_VOLUME;

	// 直接インスタンスを取得して呼び出すことで null 参照を防ぐ
	SoundManager::GetInstance().PlayBGM(bgm_, volume_);
}

void TitleScene::Update(void)
{
	// タイトル文字の点滅
	countChange++;
	if (countChange > CHANGE_COUNT)
	{
		countChange = 0;
		if(count==CHANGE_COUNT_MAX)isChange = true;
		 else if(count==1) isChange = false;

		if(!isChange) count++;
		else count--;
	}

	// シーン遷移
	auto const& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN))
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	// タイトル背景描画
	DrawGraph(0, 0, img_, TRUE);

	// タイトル文字描画
	SetFontSize(TITLE_ROG_SIZE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, COLOR_MAX /count);
	DrawString(BASE_TITLE_ROG_POS_X, BASE_TITLE_ROG_POS_Y, "光体", 0xffff00);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(BASE_TITLE_ROG_POS_X + (ROG_POS_NO_SECOND * TITLE_ROG_SIZE), BASE_TITLE_ROG_POS_Y, "バトル", 0xffffff);

	// ゲームスタート文字描画
	SetFontSize(ACENE_CHANGE_SIZE);
	DrawString(ACENE_CHANGE_POS_X, ACENE_CHANGE_POS_Y, "スぺース(Aボタン)でゲームスタート", 0xffffff);
	SetFontSize(BASE_SIZE);
}

void TitleScene::Release(void)
{
}
