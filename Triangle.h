#pragma once
#include "Vec2.h"
#include "Vec4.h"
class Triangle {
public:
	Triangle();                              // Ĭ�Ϲ��캯��
	Triangle(Triangle& rhs);                 // �������캯��
	Triangle(Vec4* points, Vec2* texCoords);
	~Triangle();
	Vec4 GetA();
	Vec4 GetB();
	Vec4 GetC();
	void SetA(Vec4& A);
	void SetB(Vec4& B);
	void SetC(Vec4& C);
	Vec3 Barycentric(Vec2 point);
	Vec4 operator[](int idx);
private:
	Vec4 points[3];    // ��������
	Vec2 texCoords[3]; // ��������
};
