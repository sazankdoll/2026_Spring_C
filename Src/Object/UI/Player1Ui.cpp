#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "../../Object/Actor/Charactor/Player.h"
#include "../../Scene/GameScene.h"
#include "Player1Ui.h"

Player1Ui::Player1Ui(Player*player,GameScene*game)
	:
	player_(player),
	game_(game),
	 CharactorBase()
{
}

Player1Ui::~Player1Ui(void)
{
}

void Player1Ui::InitPost(void)
{
}

void Player1Ui::UpdateProcess(void)
{
}

void Player1Ui::UpdateProcessPost(void)
{
}

void Player1Ui::Draw(void)
{
	//UI•`‰æ
	DrawRotaGraphF(SP_RA_ROG_POS.x- SP_RA_ROG_POS.y, SP_RA_ROG_POS.y, ICON_SIZE, 0, speedImg_, TRUE);
	DrawRotaGraphF(LE_AT_ROG_POS.x- LE_AT_ROG_POS.y, LE_AT_ROG_POS.y, ICON_SIZE, 0, attackImg_, TRUE);
	DrawRotaGraphF(SP_RA_ROG_POS.z-SP_RA_ROG_POS.y, SP_RA_ROG_POS.y, ICON_SIZE, 0, radiusImg_, TRUE);
	DrawRotaGraphF(LE_AT_ROG_POS.z- LE_AT_ROG_POS.y, LE_AT_ROG_POS.y, ICON_SIZE, 0, langthImg_, TRUE);
	float HpMaxS = HP_BAR_SIZE_MAX;
	float HpS=(float)player_->GetHp() / (float)HP_MAX;
	float DrawHps= HpMaxS * HpS;

	int shakePos = game_->GetShakePosP1();

	DrawBox(0, 0 + shakePos, (int)DrawHps, HP_BAR_SIZE_Y + shakePos, 0xffff00, TRUE);
}

void Player1Ui::Release(void)
{
}

void Player1Ui::InitLoad(void)
{
	attackImg_= resMng_.Load(ResourceManager::SRC::ATTACK_IMG).handleId_;
	speedImg_ = resMng_.Load(ResourceManager::SRC::SPEED_IMG).handleId_;
	radiusImg_ = resMng_.Load(ResourceManager::SRC::RADIUS_IMG).handleId_;
	langthImg_ = resMng_.Load(ResourceManager::SRC::RANGE_IMG).handleId_;
}

void Player1Ui::InitTransform(void)
{
}

void Player1Ui::InitCollider(void)
{
}

void Player1Ui::InitAnimation(void)
{
}
