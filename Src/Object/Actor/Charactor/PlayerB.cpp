#include "../../../Scene/GameScene.h"
#include "../../../Manager/ResourceManager.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Manager/Camera.h"
#include "../../../Manager/InputManager.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Utility/MatrixUtility.h"
#include "../../../Application.h"
#include "../../../Common/Quaternion.h"
#include "../../Common/Collider/ColliderLine.h"
#include "../../Common/Collider/ColliderCapsule.h"
#include "../../Common/Collider/ColliderSphere.h"
#include "../../Common/Collider/ColliderCapsule.h"
#include "../../Common/EffectController.h"
#include "../Wepon/Wepon.h"
#include "../Wepon/WeponMark.h"
#include "Player.h"
#include "PlayerB.h"

PlayerB::PlayerB(GameScene*game)
	:
	isWepon_(false),
	game_(game),
	player_(nullptr),

	CharactorBase()
{
}

PlayerB::~PlayerB(void)
{
}

void PlayerB::Draw(void)
{
	CharactorBase::Draw();

	for (WeponMark* mark : weponMark_)
	{
		mark->Draw();
	}
	if (wepon_ != nullptr) {
		wepon_->Draw();
	}
	SetFontSize(TEXT_SIZE_MAX);
	DrawFormatString(Application::SCREEN_SIZE_X - LE_AT_TEXT_POS.x, LE_AT_TEXT_POS.y, 0xffffff, "Lv%d",
		(int)lengthLevel_);
	DrawFormatString(Application::SCREEN_SIZE_X - SP_RA_TEXT_POS.x, SP_RA_TEXT_POS.y, 0xffffff, "Lv%d",
		(int)radiusLevel_);
	DrawFormatString(Application::SCREEN_SIZE_X - SP_RA_TEXT_POS.z, SP_RA_TEXT_POS.y, 0xffffff, "Lv%d",
		(int)speedLevel_);
	DrawFormatString(Application::SCREEN_SIZE_X - LE_AT_TEXT_POS.z, LE_AT_TEXT_POS.y, 0xffffff, "Lv%d",
		(int)attackLevel_);

	SetFontSize(TEXT_SIZE_MIN);

}

void PlayerB::Release(void)
{
	transform_.Release();

	for (WeponMark* mark : weponMark_)
	{
		mark->Release();
	}
	if (wepon_ != nullptr) {
		wepon_->Release();
	}
}

bool PlayerB::IsWepon(void)
{
	if (wepon_ != nullptr && !isWepon_)
	{
		isWepon_ = true;
		return true;
	}
	return false;
}

void PlayerB::InitLoad(void)
{
	// 基底クラスのリソースロード
	CharactorBase::InitLoad();

	//プレイヤー
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::PLAYERB));
}

void PlayerB::InitTransform(void)
{
	transform_.scl = PLAYER_SIZE;
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Identity();
	transform_.quaRotLocal =
		Quaternion::Mult(transform_.quaRotLocal,
			Quaternion::AngleAxis(AsoUtility::Deg2RadF(INIT_ROT), AsoUtility::AXIS_Y));
	transform_.pos = INIT_POS;
	transform_.Update();
}

void PlayerB::InitCollider(void)
{
	//主に地面との衝突で仕様する線分コライダ
	ColliderLine* colLine = new ColliderLine(
		ColliderBase::TAG::PLAYERB, &transform_,
		COL_LINE_START_LOCAL_POS, COL_LINE_END_LOCAL_POS);
	ownColliders_.emplace(static_cast<int>(ColliderBase::SHAPE::LINE), colLine);

	//主に攻撃との当たり判定で使用する球体コライダ
	ColliderSphere* colSphere = new ColliderSphere(
		ColliderBase::TAG::PLAYERB, &transform_,
		COL_CAPSULE_TOP_LOCAL_POS,
		COL_CAPSULE_RADIUS);
	ownColliders_.emplace(static_cast<int>(ColliderBase::SHAPE::SPHERE), colSphere);
}

void PlayerB::InitAnimation(void)
{
	
}

void PlayerB::InitPost(void)
{
	// 移動方向
	moveDir_ = AsoUtility::VECTOR_ZERO;
	// 移動スピード
	moveSpeed_ = 0.0f;
	// 移動量
	movePow_ = AsoUtility::VECTOR_ZERO;
	
	//hp
	hp_ = HP_MAX;

	LengthLevelSet(LEVEL_LENGTH::LEVEL_1);

	RadiusLevelSet(LEVEL_RADIUS::LEVEL_1);

	SpeedLevelSet(LEVEL_SPEED::LEVEL_1);

	AttackLevelSet(LEVEL_ATTACK::LEVEL_1);

	effect_ = new EffectController();
	effect_->Add(0, (Application::PATH_EFFECT + "Wepon/Wepon2.efkefc"));

	hitSeHandle_ = resMng_.Load(ResourceManager::SRC::HIT_SE).handleId_;
	weponSeHandle_ = resMng_.Load(ResourceManager::SRC::WEPON_SE).handleId_;
}

void PlayerB::ProcessMove(void)
{
	

	//moveSpeed_ = 0.0f;
	//movePow_ = AsoUtility::VECTOR_ZERO;
	VECTOR dir = AsoUtility::VECTOR_ZERO;

	auto& ins = InputManager::GetInstance();
	if (GetJoypadNum() == 0) {

		if (ins.IsNew(KEY_INPUT_I)) { dir = AsoUtility::DIR_F; }
		if (ins.IsNew(KEY_INPUT_J)) { dir = AsoUtility::DIR_L; }
		if (ins.IsNew(KEY_INPUT_K)) { dir = AsoUtility::DIR_B; }
		if (ins.IsNew(KEY_INPUT_L)) { dir = AsoUtility::DIR_R; }
	}
	else {
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD2);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
	}

	if (!AsoUtility::EqualsVZero(dir))
	{
		//慣性のある移動処理
		moveSpeed_ = INIT_MOVE_SPEED;
		Quaternion cameraRot = scnMng_.GetCamera()->GetQuaRotZ();
		moveDir_ = Quaternion::PosAxis(cameraRot, dir);
		movePow_ = VAdd(movePow_, VScale(moveDir_, moveSpeed_));
		float currentSpeed = VSize(movePow_);

		if (currentSpeed > speed_) // SPEED_MOVE (例: 5.0f など) を超えていたら
		{
			// 現在の向きを保ったまま、長さを SPEED_MOVE に固定する
			// movePow_ が 0 でないことは currentSpeed > SPEED_MOVE で保証されるので安全
			movePow_ = VScale(VNorm(movePow_), speed_);
		}

	}
	else {

	}
	//移動量の減速処理
	movePow_ = AsoUtility::Lerp(movePow_, AsoUtility::VECTOR_ZERO, DECELERATION);

}

void PlayerB::ProcessJump(void)
{

}

void PlayerB::ProcessHit(void)
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
		if (hitCol->GetTag() != ColliderBase::TAG::WEPONY) continue;
		// 派生クラスへキャスト
		const ColliderCapsule* colliderCapsule =
			dynamic_cast<const ColliderCapsule*>(hitCol);
		if (colliderCapsule == nullptr) continue;

		if (colliderCapsule->IsHit(colSphere, false, false))
		{
				// ダメージ処理
				hp_ -= player_->GetAttack();
				sonMng_.PlaySE(SoundManager::SeId::HIT_P2, hitSeHandle_);

				if (hp_ < 0) hp_ = 0;
				// ダメージエフェクトの生成など
				game_->SetShakeP2(true, SHAKE_TIME);
		}
	
	}
}

void PlayerB::ProcessAttack(void)
{
	for (WeponMark* mark : weponMark_)
	{
		mark->Update();
	}
	if (wepon_ != nullptr) {
		wepon_->Update();
	}

	if (wepon_ != nullptr
		&& !wepon_->IsAlive())
	{

		sonMng_.StopSE(SoundManager::SeId::WEPON_P2);
		delete wepon_;
		wepon_ = nullptr;

		for (WeponMark* mark : weponMark_)
		{
			mark->Release();
			delete mark;
		}
		weponMark_.clear();
	}

	if (weponMark_.size() >= MARK_MAX)return;

	auto& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_H) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN)) {
		// WeponMarkを生成
		VECTOR markPos = transform_.pos;
		WeponMark* newMark = new WeponMark(markPos, 0x0000ff);
		weponMark_.push_back(newMark);

		// 2つ目のWeponMarkが置かれたらWeponを生成
		if (weponMark_.size() == MARK_MAX) {
			VECTOR startPos = weponMark_[0]->GetTransform().pos;
			VECTOR endPos = weponMark_[1]->GetTransform().pos;
			if (wepon_ != nullptr) {

				delete wepon_;
				wepon_ = nullptr;
			}
			wepon_ = new Wepon(ColliderBase::TAG::WEPONB, startPos, endPos, length_, attackSpeed_, radius_);

			wepon_->Init();

			//エフェクト生成
			VECTOR normDir = VNorm(VSub(endPos, startPos));
			float yaw = atan2f(normDir.x, normDir.z);
			float pitch = -asinf(normDir.y);
			float roll = 0.0f;
			VECTOR euler = { pitch, yaw, roll };

			float effRadius = (radius_ * EFFECT_RADIUS_SCALE) + EFFECT_RADIUS_OFFSET;
			float effLength = (length_ / EFFECT_LENGTH_DIVISOR) + EFFECT_LENGTH_OFFSET;
			effect_->Play(0, startPos, euler, VGet(effRadius, effRadius, effLength));
			sonMng_.PlaySE(SoundManager::SeId::WEPON_P2, weponSeHandle_);

			isWepon_ = false;
			// WeponMarkを全て削除
			for (WeponMark* mark : weponMark_) {
				delete mark;
			}
			weponMark_.clear();
		}
	}
}

void PlayerB::CollisionReserve(void)
{

}

void PlayerB::LengthLevelSet(LEVEL_LENGTH length)
{

	lengthLevel_ = length;

	switch (lengthLevel_)
	{
	case CharactorBase::LEVEL_LENGTH::LEVEL_1:
		length_ = LEVEL_1_LENGTH;
		break;
	case CharactorBase::LEVEL_LENGTH::LEVEL_2:
		length_ = LEVEL_2_LENGTH;
		break;
	case CharactorBase::LEVEL_LENGTH::LEVEL_3:
		length_ = LEVEL_3_LENGTH;
		break;
	case CharactorBase::LEVEL_LENGTH::LEVEL_4:
		length_ = LEVEL_4_LENGTH;
		break;
	case CharactorBase::LEVEL_LENGTH::LEVEL_5:
		length_ = LEVEL_5_LENGTH;
		break;

	default:
		break;
	}
}

void PlayerB::RadiusLevelSet(LEVEL_RADIUS radius)
{
	radiusLevel_ = radius;

	switch (radiusLevel_)
	{
	case CharactorBase::LEVEL_RADIUS::LEVEL_1:
		radius_ = LEVEL_1_RADIUS;
		break;
	case CharactorBase::LEVEL_RADIUS::LEVEL_2:
		radius_ = LEVEL_2_RADIUS;
		break;
	case CharactorBase::LEVEL_RADIUS::LEVEL_3:
		radius_ = LEVEL_3_RADIUS;
		break;
	case CharactorBase::LEVEL_RADIUS::LEVEL_4:
		radius_ = LEVEL_4_RADIUS;
		break;
	case CharactorBase::LEVEL_RADIUS::LEVEL_5:
		radius_ = LEVEL_5_RADIUS;
		break;
	default:
		break;
	}
}

void PlayerB::SpeedLevelSet(LEVEL_SPEED speed)
{
	speedLevel_ = speed;
	switch (speedLevel_)
	{
	case CharactorBase::LEVEL_SPEED::LEVEL_1:
		speed_ = LEVEL_1_MOVE_SPEED;
		attackSpeed_ = LEVEL_1_ATTACK_SPEED;
		break;
	case CharactorBase::LEVEL_SPEED::LEVEL_2:
		speed_ = LEVEL_2_MOVE_SPEED;
		attackSpeed_ = LEVEL_2_ATTACK_SPEED;
		break;
	case CharactorBase::LEVEL_SPEED::LEVEL_3:
		speed_ = LEVEL_3_MOVE_SPEED;
		attackSpeed_ = LEVEL_3_ATTACK_SPEED;
		break;
	case CharactorBase::LEVEL_SPEED::LEVEL_4:
		speed_ = LEVEL_4_MOVE_SPEED;
		attackSpeed_ = LEVEL_4_ATTACK_SPEED;
		break;
	case CharactorBase::LEVEL_SPEED::LEVEL_5:
		speed_ = LEVEL_5_MOVE_SPEED;
		attackSpeed_ = LEVEL_5_ATTACK_SPEED;
		break;
	default:
		break;
	}
}

void PlayerB::AttackLevelSet(LEVEL_ATTACK attack)
{
	attackLevel_ = attack;
	switch (attackLevel_)
	{
	case CharactorBase::LEVEL_ATTACK::LEVEL_1:
		attack_ = LEVEL_1_ATTACK;
		break;
	case CharactorBase::LEVEL_ATTACK::LEVEL_2:
		attack_ = LEVEL_1_ATTACK;
		break;
	case CharactorBase::LEVEL_ATTACK::LEVEL_3:
		attack_ = LEVEL_2_ATTACK;
		break;
	case CharactorBase::LEVEL_ATTACK::LEVEL_4:
		attack_ = LEVEL_2_ATTACK;
		break;
	case CharactorBase::LEVEL_ATTACK::LEVEL_5:
		attack_ = LEVEL_3_ATTACK;
		break;
	default:
		break;
	}
}


void PlayerB::PowerUp(void)
{

	//ランダムに選ぶ
	int randVal = GetRand(static_cast<int>(CharactorBase::POWER_UP::MAX) - 1);
	CharactorBase::POWER_UP type = static_cast<CharactorBase::POWER_UP>(randVal);


	switch (type)
	{
	case CharactorBase::POWER_UP::LENGTH: // 射程強化
		if (lengthLevel_ == LEVEL_LENGTH::LEVEL_1) LengthLevelSet(LEVEL_LENGTH::LEVEL_2);
		else if (lengthLevel_ == LEVEL_LENGTH::LEVEL_2) LengthLevelSet(LEVEL_LENGTH::LEVEL_3);
		else if (lengthLevel_ == LEVEL_LENGTH::LEVEL_3)LengthLevelSet(LEVEL_LENGTH::LEVEL_4);
		else if (lengthLevel_ == LEVEL_LENGTH::LEVEL_4)LengthLevelSet(LEVEL_LENGTH::LEVEL_5);

		break;

	case CharactorBase::POWER_UP::RADIUS: // 太さ強化
		if (radiusLevel_ == LEVEL_RADIUS::LEVEL_1) RadiusLevelSet(LEVEL_RADIUS::LEVEL_2);
		else if (radiusLevel_ == LEVEL_RADIUS::LEVEL_2) RadiusLevelSet(LEVEL_RADIUS::LEVEL_3);
		else if (radiusLevel_ == LEVEL_RADIUS::LEVEL_3)RadiusLevelSet(LEVEL_RADIUS::LEVEL_4);
		else if (radiusLevel_ == LEVEL_RADIUS::LEVEL_4)RadiusLevelSet(LEVEL_RADIUS::LEVEL_5);
		break;

	case CharactorBase::POWER_UP::SPEED: // 速度強化
		if (speedLevel_ == LEVEL_SPEED::LEVEL_1) SpeedLevelSet(LEVEL_SPEED::LEVEL_2);
		else if (speedLevel_ == LEVEL_SPEED::LEVEL_2) SpeedLevelSet(LEVEL_SPEED::LEVEL_3);
		else if (speedLevel_ == LEVEL_SPEED::LEVEL_3)SpeedLevelSet(LEVEL_SPEED::LEVEL_4);
		else if (speedLevel_ == LEVEL_SPEED::LEVEL_4)SpeedLevelSet(LEVEL_SPEED::LEVEL_5);
		break;

	case CharactorBase::POWER_UP::ATTACK: // 攻撃力強化
		if (attackLevel_ == LEVEL_ATTACK::LEVEL_1) AttackLevelSet(LEVEL_ATTACK::LEVEL_2);
		else if (attackLevel_ == LEVEL_ATTACK::LEVEL_2) AttackLevelSet(LEVEL_ATTACK::LEVEL_3);
		else if (attackLevel_ == LEVEL_ATTACK::LEVEL_3)AttackLevelSet(LEVEL_ATTACK::LEVEL_4);
		else if (attackLevel_ == LEVEL_ATTACK::LEVEL_4)AttackLevelSet(LEVEL_ATTACK::LEVEL_5);
	}
}

void PlayerB::UpdateProcess(void)
{
	// 移動操作
	ProcessMove();

	// ジャンプ処理
	//ProcessJump();
	//リスポーン
	if (transform_.pos.y < RESPAWN_POS_Y)
	{
		Respawn();
	}

	//	攻撃処理
	ProcessAttack();

	// ダメージ処理
	ProcessHit();

	//エフェクト更新処理
	if (wepon_ != nullptr) {
		effect_->LoopUpdate(0, wepon_->GetTransform().pos);
	}

}

void PlayerB::UpdateProcessPost(void)
{
}

void PlayerB::Respawn(void)
{
	transform_.pos = { 1000.0f, 0.0f, 0.0f };
	transform_.Update();
}

