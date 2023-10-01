#pragma once
#include "Vec3.h"
class Color {
public:
	Color();                                          // Ĭ�Ϲ��캯��
	Color(const Color& rhs);                          // �������캯��
	Color(float r, float g, float b, float a = 1.0f); // r, g, b, a ȡֵ��Χ����[0, 1]
	Color(float r, float a = 1.0f);
	~Color();
	float R()const;
	float G()const;
	float B()const;
	float A()const;
	Vec3 RGB()const;
	void SetR(float r);
	void SetG(float g);
	void SetB(float b);
	void SetA(float a);
	Color& operator=(const Color& rhs);
private:
	float r, g, b, a;                                 // �����̷�����͸����
};

Color operator+(const Color& a, const Color& b);
Color operator-(const Color& a, const Color& b);
Color operator*(float k, const Color& c);
Color operator/(const Color& c, float k);

bool operator==(const Color& a, const Color& b);
bool operator!=(const Color& a, const Color& b);