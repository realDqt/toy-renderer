#pragma once
#include "Vec2.h"
#include "Vec4.h"
#include "Mat4.h"
class Triangle {
public:
	Triangle();                                                       // 默认构造函数
	Triangle(Triangle& rhs);                                          // 拷贝构造函数
	Triangle(Vec4* points, Vec2* texCoords);
	~Triangle();
	Vec4 GetA();
	Vec4 GetB();
	Vec4 GetC();
	void SetA(Vec4& A);
	void SetB(Vec4& B);
	void SetC(Vec4& C);
	Vec3 Barycentric(Vec2 point);
	void Transform(const Mat4& mvp, int width, int height, int depth, bool print = false); // 完成MVP变换、透视除法和视口变换                                                  // 恢复至最初的顶点坐标
	Vec4& operator[](int idx);
	const Vec4& operator[](int idx)const;
private:
	Vec4 points[3];                                                    // 顶点坐标
	Vec4 oriPoints[3];                                                 // 最初的顶点坐标
	Vec2 texCoords[3];                                                 // 纹理坐标
};
