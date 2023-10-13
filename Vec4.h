#pragma once
#include "Vec3.h"
#include <iostream>
class Vec3;
class Vec4 {
public:
	Vec4();                                                // Ĭ�Ϲ��캯��
	Vec4(const Vec4& rhs);                                 // �������캯��
	Vec4(float x, float y, float z, float w = 1.0f); 
	Vec4(Vec3 v, float w = 1.0f);
	~Vec4();
	float X()const;
	float Y()const;
	float Z()const;
	float W()const;
	Vec3 XYZ()const;                                       // ��ȡxyz�������ɵ�Vec3
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetW(float w);
	Vec4& operator= (const Vec4& rhs);                     // ��ֵ���������
	float& operator[](int idx);
	const float& operator[](int idx)const;
private:
	float x, y, z, w;
};

Vec4 operator+(const Vec4& a, const Vec4& b);               // �����ӷ�
Vec4 operator-(const Vec4& a, const Vec4& b);               // ��������
Vec4 operator*(float k, const Vec4& v);                     // ��������
Vec4 operator/(const Vec4& v, float k);                     // ��������
Vec4 operator*(const Vec4& a, const Vec4& b);               // ������Ӧ�������
std::ostream& operator<<(std::ostream& out, const Vec4& v); // ������������

