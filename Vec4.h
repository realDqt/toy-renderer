#pragma once
#include "Vec3.h"
class Vec4 {
public:
	Vec4();                                          // 默认构造函数
	Vec4(const Vec4& rhs);                                 // 拷贝构造函数
	Vec4(float x, float y, float z, float w = 1.0f); 
	Vec4(Vec3 v, float w = 1.0f);
	~Vec4();
	float X()const;
	float Y()const;
	float Z()const;
	float W()const;
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetW(float w);
	Vec4& operator= (const Vec4& rhs); // 赋值运算符重载
private:
	float x, y, z, w;
};

Vec4 operator+(const Vec4& a, const Vec4& b);  // 向量加法
Vec4 operator-(const Vec4& a, const Vec4& b);  // 向量减法
Vec4 operator*(float k, const Vec4& v); // 向量数乘
Vec4 operator/(const Vec4& v, float k); // 向量数除

