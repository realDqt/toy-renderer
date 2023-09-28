#pragma once
class Vec2 {
public:
	Vec2();                      // Ĭ�Ϲ��캯��
	Vec2(const Vec2& rhs);             // �������캯��
	Vec2(float x, float y);
	Vec2(float x);
	~Vec2();
	float X()const;
	float Y()const;
	void SetX(float x);
	void SetY(float y);
	Vec2& operator= (const Vec2& rhs); // ��ֵ���������
private:
	float x, y;
};

Vec2 operator+(const Vec2& a, const Vec2& b);  // �����ӷ�
Vec2 operator-(const Vec2& a, const Vec2& b);  // ��������
Vec2 operator*(float k, const Vec2& v); // ��������
Vec2 operator/(const Vec2& v, float k); // ��������

