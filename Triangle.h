#pragma once
#include "Vec2.h"
#include "Vec4.h"
class Triangle {
public:
	Triangle();                              // 默认构造函数
	Triangle(Triangle& rhs);                 // 拷贝构造函数
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
	Vec4 points[3];    // 顶点坐标
	Vec2 texCoords[3]; // 纹理坐标
};
