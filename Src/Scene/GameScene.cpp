#include <DxLib.h>
#include "../Manager/Camera.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SoundManager.h"
#include "../Object/Actor/ActorBase.h"
#include "../Object/Actor/Stage/Stage.h"
#include "../Object/Actor/Stage/SkyDome.h"
#include "../Object/Actor/Charactor/Player.h"
#include "../Object/Actor/Charactor/PlayerB.h"
#include "../Object/Common/Collider/ColliderBase.h"
#include "../Object/point.h"
#include "../Object/Actor/Wepon/Wepon.h"
#include "../Object/UI/Player1Ui.h"
#include "../Object/UI/Player2Ui.h"
#include "../Object/Actor/Item/ItemBase.h"
#include "../Object/Timer/Timer.h"
#include "GameScene.h"

GameScene::GameScene(Timer*timer)
	:
	ShakePosP1_(0),
	ShakeTimeP1_(0),
	ShakeFlagP1_(false),
	ShakePosP2_(0),
	ShakeTimeP2_(0),
	ShakeFlagP2_(false),
	timer_(timer),

	SceneBase()
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	//カメラインスタンス取得
	Camera* camera = SceneManager::GetInstance().GetCamera();

	//スカイドーム
	skydome_ = new SkyDome();
	skydome_->Init();

	//ステージ
	stage_ = new Stage();
	stage_->Init();

	//プレイヤー
	player_ = new Player(this);
	player_->Init();
	playerB_ = new PlayerB(this);
	playerB_->Init();

	//プレイヤーUI
	player1Ui_ = new Player1Ui(player_, this);
	player1Ui_->Init();
	player2Ui_ = new Player2Ui(playerB_, this);
	player2Ui_->Init();

	//アイテム
	itemBase_ = new ItemBase(this, player_, playerB_);
	itemBase_->Init();

	//プレイヤー同士の位置を設定
	player_->SetPlayer(playerB_);
	playerB_->SetPlayer(player_);

	//カメラモード変更
	camera->ChangeMode(Camera::MODE::FIXED_POINT);
	
	//振動関係初期化
	ShakeTimeP1_ = 0;
	ShakePosP1_ = SHAKE_WIDTH;
	ShakeFlagP1_ = false;
	ShakeTimeP2_ = 0;
	ShakePosP2_ = SHAKE_WIDTH;
	ShakeFlagP2_ = false;

	// BGM初期化
	bgm_ = resMng_.Load(ResourceManager::SRC::GAME_BGM).handleId_;
	volume_ = BGM_VOLUME;

	// 直接インスタンスを取得して呼び出すことで null 参照を防ぐ
	SoundManager::GetInstance().PlayBGM(bgm_, volume_);

	InitCollider();
}

void GameScene::Update(void)
{
	// スカイドーム更新
	skydome_->Update();

	// シーン遷移
	auto const& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	// ステージ更新
	stage_->Update();

	// 各プレイヤー更新
	player_->Update();
	playerB_->Update();

	// アイテム更新
	itemBase_->Update();
	
	// 各hpの振動
	HpShakeP1();
	HpShakeP2();

	UpdateCollider();

	// UI更新
	Point::GetInstance()->SetpHp(player_->GetHp());
	Point::GetInstance()->SetpBhp(playerB_->GetHp());
	if (player_->GetHp() <= 0|| playerB_->GetHp() <= 0|| timer_->GetMin() <= 0 && timer_->GetSec() <= 0)
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::RESULT);
	}
}

void GameScene::Draw(void)
{
	// スカイドーム描画
	skydome_->Draw();

	// ステージ描画
	stage_->Draw();

	//ステージ描画
	player_->Draw();
	playerB_->Draw();

	//UI描画
	player1Ui_->Draw();
	player2Ui_->Draw();

	//アイテム描画
	itemBase_->Draw();
}

void GameScene::Release(void)
{
	// スカイドーム解放
	skydome_->Release();
	delete skydome_;

	// ステージ解放
	stage_->Release();
	delete stage_;

	// 各プレイヤー解放
	player_->Release();
	delete player_;
	playerB_->Release();
	delete playerB_;

	// 各プレイヤーUI解放
	player1Ui_->Release();
	delete player1Ui_;
	player2Ui_->Release();
	delete player2Ui_;
	
	// アイテム解放
	itemBase_->Release();
	delete itemBase_;

	// タイマー解放
	delete timer_;
}

void GameScene::HpShakeP1(void)
{
	// 振動フラグtrueの時、振動処理を行う
	if (ShakeFlagP1_)
	{
		if (ShakePosP1_ == SHAKE_WIDTH)
		{
			ShakePosP1_ = -SHAKE_WIDTH;
		}
		else if (ShakePosP1_ == -SHAKE_WIDTH)
		{
			ShakePosP1_ = SHAKE_WIDTH;
		}
		ShakeTimeP1_--;
	}

	// 振動時間が0以下の時、振動フラグをfalseにし、座標を初期化
	if (ShakeTimeP1_ <= 0)
	{
		ShakeFlagP1_ = false;
		ShakePosP1_ = SHAKE_WIDTH;
	}
}
void GameScene::HpShakeP2(void)
{
	// 振動フラグtrueの時、振動処理を行う
	if (ShakeFlagP2_)
	{
		if (ShakePosP2_ == SHAKE_WIDTH)
		{
			ShakePosP2_ = -SHAKE_WIDTH;
		}
		else if (ShakePosP2_ == -SHAKE_WIDTH)
		{
			ShakePosP2_ = SHAKE_WIDTH;
		}
		ShakeTimeP2_--;
	}

	// 振動時間が0以下の時、振動フラグをfalseにし、座標を初期化
	if (ShakeTimeP2_ <= 0)
	{
		ShakeFlagP2_ = false;
		ShakePosP2_ = SHAKE_WIDTH;
	}
}

void GameScene::InitCollider(void)
{
	// 各コライダーの追加
	playerB_->AddHitCollider(stage_->GetOwnCollider(static_cast<int>(ColliderBase::SHAPE::MODEL)));
	player_->AddHitCollider(stage_->GetOwnCollider(static_cast<int>(ColliderBase::SHAPE::MODEL)));
	itemBase_->AddHitCollider(stage_->GetOwnCollider(static_cast<int>(ColliderBase::SHAPE::MODEL)));
	itemBase_->AddHitCollider(player_->GetOwnCollider(static_cast<int>(ColliderBase::SHAPE::SPHERE)));
	itemBase_->AddHitCollider(playerB_->GetOwnCollider(static_cast<int>(ColliderBase::SHAPE::SPHERE)));
}

void GameScene::UpdateCollider(void)
{
	// 各コライダーの更新
	const auto& playerWepon = player_->GetWepon();
	if (playerWepon != nullptr)
	{
		const ColliderBase* playerWeponCollider =
			playerWepon->GetOwnCollider(static_cast<int>(ColliderBase::SHAPE::CAPSULE));
		playerB_->AddHitCollider(playerWeponCollider);
	}
	else
	{
		// Playerの武器（WEPONY）のカプセルだけ解除
		playerB_->RemoveHitColliderByShapeAndTag(ColliderBase::SHAPE::CAPSULE, ColliderBase::TAG::WEPONY);
	}

	const auto& playerBWepon = playerB_->GetWepon();
	if (playerBWepon != nullptr)
	{
		const ColliderBase* playerBWeponCollider =
			playerBWepon->GetOwnCollider(static_cast<int>(ColliderBase::SHAPE::CAPSULE));
		player_->AddHitCollider(playerBWeponCollider);
	}
	else
	{
		// PlayerBの武器（WEPONB）のカプセルだけ解除
		player_->RemoveHitColliderByShapeAndTag(ColliderBase::SHAPE::CAPSULE, ColliderBase::TAG::WEPONB);
	}
}
