#pragma once
class Vec3 {
public:
	Vec3();                          // Ĭ�Ϲ��캯��
	Vec3(const Vec3& rhs);                 // �������캯��
	Vec3(float x, float y, float z);
	Vec3(float x);
	~Vec3();
	float X()const;
	float Y()const;
	float Z()const;
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	Vec3& operator= (const Vec3& rhs); // ��ֵ���������
	float& operator[](int idx);
	const float& operator[](int idx)const;
private:
	float x, y, z;
};

Vec3 operator+(const Vec3& a, const Vec3& b);  // �����ӷ�
Vec3 operator-(const Vec3& a, const Vec3& b);  // ��������
Vec3 operator*(float k, const Vec3& v); // ��������
Vec3 operator/(const Vec3& v, float k); // ��������

