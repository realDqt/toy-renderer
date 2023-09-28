#include "Vec2.h"

// 默认构造函数
Vec2::Vec2()
{
	this->x = this->y = 0.0f;
}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2::Vec2(float x)
{
	this->x = this->y = x;
}

// 拷贝构造函数
Vec2::Vec2(const Vec2& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
}

Vec2::~Vec2()
{
}

float Vec2::X()const
{
	return x;
}
float Vec2::Y()const
{
	return y;
}

void Vec2::SetX(float x)
{
	this->x = x;
}
void Vec2::SetY(float y)
{
	this->y = y;
}

Vec2& Vec2::operator=(const Vec2& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

// 向量加法
Vec2 operator+(const Vec2& a, const Vec2& b)
{
	Vec2 res(a.X() + b.X(), a.Y() + b.Y());
	return res;
}
// 向量减法
Vec2 operator-(const Vec2& a, const Vec2& b)
{
	Vec2 res(a.X() - b.X(), a.Y() - b.Y());
	return res;
}
// 向量数乘
Vec2 operator*(float k, const Vec2& v)
{
	Vec2 res(k * v.X(), k * v.Y());
	return res;
}
// 向量数除
Vec2 operator/(const Vec2& v, float k)
{
	Vec2 res(v.X() / k, v.Y() / k);
	return res;
}