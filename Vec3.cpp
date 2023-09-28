#include "Vec3.h"

// Ĭ�Ϲ��캯��
Vec3::Vec3()
{
	this->x = this->y = this->z = 0.0f;
}

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3(float x)
{
	this->x = this->y = this->z = x;
}

// �������캯��
Vec3::Vec3(const Vec3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}

Vec3::~Vec3()
{
}

float Vec3::X()const
{
	return x;
}
float Vec3::Y()const
{
	return y;
}
float Vec3::Z()const
{
	return z;
}

void Vec3::SetX(float x)
{
	this->x = x;
}
void Vec3::SetY(float y)
{
	this->y = y;
}
void Vec3::SetZ(float z)
{
	this->z = z;
}

Vec3& Vec3::operator=(const Vec3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

// �����ӷ�
Vec3 operator+(const Vec3& a, const Vec3& b)
{
	Vec3 res(a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z());
	return res;
}
// ��������
Vec3 operator-(const Vec3& a, const Vec3& b)
{
	Vec3 res(a.X() - b.X(), a.Y() - b.Y(), a.Z() - b.Z());
	return res;
}
// ��������
Vec3 operator*(float k, const Vec3& v)
{
	Vec3 res(k * v.X(), k * v.Y(), k * v.Z());
	return res;
}
// ��������
Vec3 operator/(const Vec3& v, float k)
{
	Vec3 res(v.X() / k, v.Y() / k, v.Z() / k);
	return res;
}