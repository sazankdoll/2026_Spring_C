#include "WeponMark.h"

WeponMark::WeponMark(const VECTOR& pos, const int color)
{
	transform_.pos = pos;
	color_ = color;
}

WeponMark::~WeponMark(void)
{
}

void WeponMark::Update(void)
{
}

void WeponMark::Draw(void)
{
	//É}Å[ÉNï`âÊ
	DrawSphere3D(transform_.pos, RADIUS, DIV_NUM, color_, color_, true);
}

void WeponMark::Release(void)
{
}

void WeponMark::InitLoad(void)
{
}

void WeponMark::InitTransform(void)
{
}

void WeponMark::InitCollider(void)
{
}

void WeponMark::InitAnimation(void)
{
}

void WeponMark::InitPost(void)
{
}
