#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "../../Object/Actor/Charactor/PlayerB.h"
#include "../../Scene/GameScene.h"
#include "Player2Ui.h"

Player2Ui::Player2Ui(PlayerB* playerB,GameScene*game)
	:
	playerB_(playerB),
	game_(game),
	CharactorBase()
{
}

Player2Ui::~Player2Ui(void)
{
}

void Player2Ui::InitPost(void)
{
}

void Player2Ui::UpdateProcess(void)
{
}

void Player2Ui::UpdateProcessPost(void)
{
}

void Player2Ui::Draw(void)
{
	//UI描画
	DrawRotaGraphF(Application::SCREEN_SIZE_X - SP_RA_ROG_POS.z, SP_RA_ROG_POS.y, ICON_SIZE, 0, speedImg_, TRUE);
	DrawRotaGraphF(Application::SCREEN_SIZE_X - LE_AT_ROG_POS.z, LE_AT_ROG_POS.y, ICON_SIZE, 0, attackImg_, TRUE);
	DrawRotaGraphF(Application::SCREEN_SIZE_X - SP_RA_ROG_POS.x, SP_RA_ROG_POS.y, ICON_SIZE, 0, radiusImg_, TRUE);
	DrawRotaGraphF(Application::SCREEN_SIZE_X - LE_AT_ROG_POS.x, LE_AT_ROG_POS.y, ICON_SIZE, 0, langthImg_, TRUE);
	float HpMaxS = HP_BAR_SIZE_MAX;
	float HpS = (float)playerB_->GetHp() / (float)HP_MAX;
	float DrawHps = (HpMaxS * HpS);

	int shakePos= game_->GetShakePosP2();

	DrawBox(Application::SCREEN_SIZE_X, 0+shakePos, Application::SCREEN_SIZE_X - (int)DrawHps, HP_BAR_SIZE_Y + shakePos, 0x00ffff, TRUE);
}

void Player2Ui::Release(void)
{
}

void Player2Ui::InitLoad(void)
{
	//リソースロード
	attackImg_ = resMng_.Load(ResourceManager::SRC::ATTACK_IMG).handleId_;
	speedImg_ = resMng_.Load(ResourceManager::SRC::SPEED_IMG).handleId_;
	radiusImg_ = resMng_.Load(ResourceManager::SRC::RADIUS_IMG).handleId_;
	langthImg_ = resMng_.Load(ResourceManager::SRC::RANGE_IMG).handleId_;
}

void Player2Ui::InitTransform(void)
{
}

void Player2Ui::InitCollider(void)
{
}

void Player2Ui::InitAnimation(void)
{
}
