#include "Triangle.h"
#include "Global.h"
#include <assert.h>
#include <iostream>

// Ĭ�Ϲ��캯��
Triangle::Triangle()
{
}

// �������캯��
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

Vec4& Triangle::operator[](int idx)
{
	return points[idx];
}

const Vec4& Triangle::operator[](int idx)const
{
	return points[idx];
}

Vec3 Triangle::Barycentric(Vec2 point)
{
	// ��һ����η���
	for (int i = 0; i < 3; ++i)points[i] = points[i] / points[i].W();

	// ��ȡ��������
	float x = point.X(), y = point.Y();
	float xa = points[0].X(), xb = points[1].X(), xc = points[2].X();
	float ya = points[0].Y(), yb = points[1].Y(), yc = points[2].Y();

	// ������������
	float alpha = -(x - xb) * (yc - yb) + (y - yb) * (xc - xb);
	alpha /= -(xa - xb) * (yc - yb) + (ya - yb) * (xc - xb);

	float beta = -(x - xc) * (ya - yc) + (y - yc) * (xa - xc);
	beta /= -(xb - xc) * (ya - yc) + (yb - yc) * (xa - xc);

	float gamma = 1 - alpha - beta;

	return Vec3(alpha, beta, gamma);
}

// ���MVP�任��͸�ӳ������ӿڱ任
void Triangle::Transform(const Mat4& mvp, int width, int height, int depth, bool print)
{
	// mvp�任
	for (int i = 0; i < 3; ++i) {
		points[i] = mvp * points[i];
	}

	// ͸�ӳ���
	for (int i = 0; i < 3; ++i) {
		assert(!FloatEqual(points[i].W(), 0.0f));
		points[i] = points[i] / points[i].W();
		if(print)std::cout << points[i] << std::endl;
	}

	// �ӿڱ任
	Vec3 scale(width / 2.0f, height / 2.0f, depth / 2.0f);
	Vec3 translate(width / 2.0f, height / 2.0f, -depth / 2.0f);
	Mat4 viewport = Translate(translate) * Scale(scale);
	for (int i = 0; i < 3; ++i) {
		points[i] = viewport * points[i];
		if (print)std::cout << points[i] << std::endl;
	}
}