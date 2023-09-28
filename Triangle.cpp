#include "Triangle.h"

// 默认构造函数
Triangle::Triangle()
{
}

// 拷贝构造函数
Triangle::Triangle(Triangle& rhs)
{
	for (int i = 0; i < 3; ++i) {
		this->points[i] = rhs.points[i];
		this->texCoords[i] = rhs.texCoords[i];
	}
}

Triangle::Triangle(Vec4* points, Vec2* texCoors)
{
	for (int i = 0; i < 3; ++i) {
		if(points)this->points[i] = points[i];
		if(texCoords)this->texCoords[i] = texCoords[i];
	}
}

Triangle::~Triangle()
{
}

Vec4 Triangle::GetA()
{
	return points[0];
}
Vec4 Triangle::GetB()
{
	return points[1];
}
Vec4 Triangle::GetC()
{
	return points[2];
}

void Triangle::SetA(Vec4& A)
{
	points[0] = A;
}
void Triangle::SetB(Vec4& B)
{
	points[1] = B;
}
void Triangle::SetC(Vec4& C)
{
	points[2] = C;
}

Vec4 Triangle::operator[](int idx)
{
	return points[idx];
}

Vec3 Triangle::Barycentric(Vec2 point)
{
	// 归一化齐次分量
	for (int i = 0; i < 3; ++i)points[i] = points[i] / points[i].W();

	// 获取顶点坐标
	float x = point.X(), y = point.Y();
	float xa = points[0].X(), xb = points[1].X(), xc = points[2].X();
	float ya = points[0].Y(), yb = points[1].Y(), yc = points[2].Y();

	// 计算重心坐标
	float alpha = -(x - xb) * (yc - yb) + (y - yb) * (xc - xb);
	alpha /= -(xa - xb) * (yc - yb) + (ya - yb) * (xc - xb);

	float beta = -(x - xc) * (ya - yc) + (y - yc) * (xa - xc);
	beta /= -(xb - xc) * (ya - yc) + (yb - yc) * (xa - xc);

	float gamma = 1 - alpha - beta;

	return Vec3(alpha, beta, gamma);
}