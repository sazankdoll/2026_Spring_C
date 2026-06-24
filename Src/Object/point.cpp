#include"point.h"


// シングルトンのインスタンス取得
Point* Point::_instance = nullptr;

Point* Point::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Point();
	}
	return _instance;
}

Point::Point(void)
{
	
	php_ = 0;
	pBhp_ = 0;
	
}

Point::~Point(void)
{

}

void Point::Init(void)
{
	
	php_= 0;

}



void Point::SetpHp(int php)
{
	php_ = php;
}

void Point::SetpBhp(int pBhp)
{
	pBhp_ = pBhp;
}



int Point::GetpHp(void)
{
	return php_;
}

int Point::GetpBhp(void)
{
	return pBhp_;
}

