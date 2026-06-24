#include "../../../Manager/ResourceManager.h"
#include "../../../Manager/SceneManager.h"
#include "../../Common/Collider/ColliderCapsule.h"
#include "Wepon.h"

Wepon::Wepon(const ColliderBase::TAG& tag, const VECTOR& statePos, const VECTOR& endPos,
	const float& length, const float& speed, const float& radius)
{
	tag_ = tag;
	transform_.pos = statePos;
	downPos_ = statePos;
	endPos_ = endPos;
	length_ = length;
	moveSpeed_ = speed;
	radius_ = radius;
}

Wepon::~Wepon(void)
{
}

void Wepon::Update(void)
{
	if (!IsAlive())return;

	prevPos_ = transform_.pos;

	Move();
}

void Wepon::Draw(void)
{
	if (!IsAlive())return;
}

void Wepon::Release(void)
{
}

void Wepon::InitLoad(void)
{
}

void Wepon::InitTransform(void)
{
}

void Wepon::InitCollider(void)
{
	// カプセルの両端を指定
	ColliderCapsule* colCapsule = new ColliderCapsule(
		tag_, &transform_,
		AsoUtility::VECTOR_ZERO,
		VSub(downPos_, transform_.pos),
		radius_);
	ownColliders_.emplace(static_cast<int>(ColliderBase::SHAPE::CAPSULE), colCapsule);
}

void Wepon::InitAnimation(void)
{
}

void Wepon::InitPost(void)
{
	movePow_ = AsoUtility::VECTOR_ZERO;

	//光体のと終点座標でベクトルを作る
	VECTOR dir = VNorm(VSub(endPos_, transform_.pos));
	moveDir_ = dir;
}

bool Wepon::IsAlive(void)
{
	//光体の後ろ座標と消失する座標の距離が一定以下になると消える
	float diff = VSize(VSub(endPos_, downPos_));
	if (diff <= DISAPPEAR_LENGTH)
	{
		return false;
	}
	return true;
}

void Wepon::Move(void)
{
	//光体上側移動処理
	movePow_ = VScale(moveDir_, moveSpeed_);
	VECTOR nextPos = VAdd(transform_.pos, movePow_);

	float distHeadToEnd = VSize(VSub(endPos_, transform_.pos));
	bool is = false;
	if (distHeadToEnd <= moveSpeed_)
	{
		transform_.pos = endPos_;
		is = true;
	}
	else
	{
		transform_.pos = nextPos;
	}

	float diff = VSize(VSub(transform_.pos, downPos_));
	if (diff >= length_ || is)
	{
		float tailToEnd = VSize(VSub(endPos_, downPos_));
		if (tailToEnd <= moveSpeed_)
		{
			downPos_ = endPos_;
		}
		else
		{
			downPos_ = VAdd(downPos_, VScale(moveDir_, moveSpeed_));
		}
	}

	// 光体の衝突判定の座標を更新
	auto it = ownColliders_.find(static_cast<int>(ColliderBase::SHAPE::CAPSULE));
	if (it != ownColliders_.end()) {
		ColliderCapsule* colCapsule = dynamic_cast<ColliderCapsule*>(it->second);
		if (colCapsule) {
			colCapsule->SetLocalPosDown(VSub(downPos_, transform_.pos));
		}
	}
}