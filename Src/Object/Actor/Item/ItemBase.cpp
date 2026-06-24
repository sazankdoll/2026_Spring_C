#include "../../../Manager/ResourceManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Scene/GameScene.h"
#include "../../../Manager/SceneManager.h"
#include "../../Common/Collider/ColliderLine.h"
#include "../../Common/Collider/ColliderCapsule.h"
#include "../../Common/Collider/ColliderSphere.h"
#include "../../Actor/Charactor/Player.h"
#include "../../Actor/Charactor/PlayerB.h"
#include "ItemBase.h"


ItemBase::ItemBase(GameScene* game,Player*player,PlayerB*playerB)
	:
	game_(game),
	player_(player),
	playerB_(playerB),
	isItem_(false),
	isAlive_(false),
	resetCount_(0),
	getItemP1SeHandle_(-1),
	getItemP2SeHandle_(-1),
	crashSeHandle_(-1),
	
	CharactorBase()
{

}

ItemBase::~ItemBase(void)
{
}

void ItemBase::Draw(void)
{
	if (isAlive_)
	{
		CharactorBase::Draw();
	}

}

void ItemBase::Release(void)
{
	transform_.Release();
}

bool ItemBase::IsItem(void)
{
	return true;
}

void ItemBase::InitLoad(void)
{
	// 基底クラスのリソースロード
	CharactorBase::InitLoad();

	//仮
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::PLAYERY));
}

void ItemBase::InitTransform(void)
{
	transform_.scl = ITEM_SIZE;
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Identity();
	transform_.quaRotLocal =
		Quaternion::Mult(transform_.quaRotLocal,
			Quaternion::AngleAxis(AsoUtility::Deg2RadF(AsoUtility::DEG180), AsoUtility::AXIS_Y));
	transform_.pos = ITEM_POS;
	transform_.Update();
}

void ItemBase::InitCollider(void)
{
	
//主に地面との衝突で仕様する線分コライダ
ColliderLine* colLine = new ColliderLine(
	ColliderBase::TAG::ITEM, &transform_,
	COL_LINE_START_LOCAL_POS, COL_LINE_END_LOCAL_POS);
ownColliders_.emplace(static_cast<int>(ColliderBase::SHAPE::LINE), colLine);

	//主に攻撃との当たり判定で使用する球体コライダ
	ColliderSphere* colSphere = new ColliderSphere(
		ColliderBase::TAG::ITEM, &transform_,
		COL_CAPSULE_TOP_LOCAL_POS,
		COL_RADIUS);
	ownColliders_.emplace(static_cast<int>(ColliderBase::SHAPE::SPHERE), colSphere);
}

void ItemBase::InitAnimation(void)
{
}

void ItemBase::InitPost(void)
{
	getItemP1SeHandle_ = resMng_.Load(ResourceManager::SRC::GET_ITEM_SE).handleId_;
	getItemP2SeHandle_ = resMng_.Load(ResourceManager::SRC::GET_ITEM_SE).handleId_;
	crashSeHandle_ = resMng_.Load(ResourceManager::SRC::CRASH_SE).handleId_;
}

void ItemBase::UpdateProcess(void)
{

	if (isAlive_)
	{
		resetCount_ = 0;
		CollisionReserveP1();
		CollisionReserveP2();
	}
	else if (!isAlive_)
	{
		resetCount_++;
		if (resetCount_ > ITEM_COUNT)
		{
			Respawn();
			isAlive_ = true;
			resetCount_ = 0;
		}
	}
}

void ItemBase::UpdateProcessPost(void)
{
}

void ItemBase::LengthLevelSet(LEVEL_LENGTH length)
{
}

void ItemBase::RadiusLevelSet(LEVEL_RADIUS radius)
{
}

void ItemBase::SpeedLevelSet(LEVEL_SPEED speed)
{
}

void ItemBase::Respawn(void)
{
	//ランダムに選ぶ
	int type = GetRand(9);

	switch (type)
	{
	case 0:
		transform_.pos = RESPAWN_POS_A;
		break;
	case 1:
		transform_.pos = RESPAWN_POS_B;
		break;
	case 2:
		transform_.pos = RESPAWN_POS_C;
		break;
	case 3:
		transform_.pos = RESPAWN_POS_D;
		break;
	case 4:
		transform_.pos = RESPAWN_POS_E;
		break;
	case 5:
		transform_.pos = RESPAWN_POS_F;
		break;
	case 6:
		transform_.pos = RESPAWN_POS_G;
		break;
	case 7:
		transform_.pos = RESPAWN_POS_H;
		break;
	case 8:
		transform_.pos = RESPAWN_POS_I;
		break;
	}
	transform_.Update();
}

void ItemBase::CollisionReserveP1(void)
{
	// カプセルコライダ  
	int SphereType = static_cast<int>(ColliderBase::SHAPE::SPHERE);
	// カプセルコライダが無ければ処理を抜ける  
	if (ownColliders_.count(SphereType) == 0) return;

	ColliderSphere* colSphere = static_cast<ColliderSphere*>(ownColliders_[static_cast<int>(ColliderBase::SHAPE::SPHERE)]);
	if (colSphere == nullptr) return;
	for (const auto& hitCol : hitColliders_)
	{
	
		// プレイヤーカプセル以外は処理を飛ばす
		if (hitCol->GetTag() != ColliderBase::TAG::PLAYERY) continue;

		// 派生クラスへキャスト
		const ColliderSphere* colliderSphere =
			dynamic_cast<const ColliderSphere*>(hitCol);
		if (colliderSphere == nullptr) continue;

		if (colliderSphere->IsHit(colSphere,false,false))
		{
			isAlive_ = false;
			isItem_ = true; // または取得フラグ


			//this->SetDestroy();
			sonMng_.PlaySE(SoundManager::SeId::GET_ITEM_P1 , getItemP1SeHandle_);
			player_->PowerUp();

			// 1つでも当たれば判定終了
			break;
		}
	}
}

void ItemBase::CollisionReserveP2(void)
{
	// カプセルコライダ  
	int SphereType = static_cast<int>(ColliderBase::SHAPE::SPHERE);
	// カプセルコライダが無ければ処理を抜ける  
	if (ownColliders_.count(SphereType) == 0) return;

	ColliderSphere* colSphere = static_cast<ColliderSphere*>(ownColliders_[static_cast<int>(ColliderBase::SHAPE::SPHERE)]);
	if (colSphere == nullptr) return;
	for (const auto& hitCol : hitColliders_)
	{
		// プレイヤーカプセル以外は処理を飛ばす
		if (hitCol->GetTag() != ColliderBase::TAG::PLAYERB) continue;


		// 派生クラスへキャスト
		const ColliderSphere* colliderSphere =
			dynamic_cast<const ColliderSphere*>(hitCol);
		if (colliderSphere == nullptr) continue;

		if (colliderSphere->IsHit(colSphere, false, false))
		{
			isAlive_ = false;
			isItem_ = true; // または取得フラグ


			//this->SetDestroy();
			sonMng_.PlaySE(SoundManager::SeId::GET_ITEM_P1, getItemP1SeHandle_);
			playerB_->PowerUp();

			// 1つでも当たれば判定終了
			break;
		}
	}
}

