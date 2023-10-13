#include "global.h"
#include <algorithm>
#include <cmath>
#define NOMINMAX

// 判断k是否属于区间[min, max]
bool InRange(float k, float min, float max)
{
	return k >= min && k <= max;
}

// 计算Vec3内积
float Dot(const Vec3& a, const Vec3& b)
{
	return a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z();
}

// 计算Vec3外积
Vec3 Cross(const Vec3& a, const Vec3& b)
{
	float x = a.Y() * b.Z() - a.Z() * b.Y();
	float y = a.Z() * b.X() - a.X() * b.Z();
	float z = a.X() * b.Y() - a.Y() * b.X();
	return Vec3(x, y, z);
}

// 计算Vec3长度
float Length(const Vec3& v)
{
	return sqrt(v.X() * v.X() + v.Y() * v.Y() + v.Z() * v.Z());
}

// 标准化Vec3
Vec3 Normalize(const Vec3& v)
{
	return v / Length(v);
}

// 角度转弧度
float Radians(float angle)
{
	return angle / 180.0f * PI;
}

// 判断两个浮点数相等
bool FloatEqual(float a, float b)
{
	return fabs(a - b) < 0.0001f;
}

// 平移函数
Mat4 Translate(const Vec3& translate)
{
	Mat4 res(1.0f);
	for (int i = 0; i < 3; ++i)res[i][3] = translate[i];
	return res;
}

// 旋转函数
Mat4 Rotate(const Vec3& n, float alpha)
{
	float cosAlpha = cos(alpha);
	float sinAlpha = sin(alpha);
	Mat3 I(1.0f);

	// 计算nnT
	Mat3 nnT(1.0f);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			nnT[i][j] = n[i] * n[j];
		}
	}

	// 计算N
	Mat3 N(0.0f);
	N[0][1] = -n.Z();
	N[0][2] = n.Y();
	N[1][0] = n.Z();
	N[1][2] = -n.X();
	N[2][0] = -n.Y();
	N[2][1] = n.X();

	// Rodrigues' Rotate Formula
	Mat3 res = cosAlpha * I + (1 - cosAlpha) * nnT + sinAlpha * N;
	return Mat4(res);
}

// 缩放函数
Mat4 Scale(const Vec3& scale)
{
	Mat4 res(1.0f);
	for (int i = 0; i < 3; ++i)res[i][i] = scale[i];
	return res;
}

// 正交投影
Mat4 Ortho(float l, float r, float t, float b, float n, float f)
{
	// n和f都是负值
	Vec3 scale(2.0f / (r - l), 2.0f / (t - b), 2.0f / (n - f));
	Vec3 translate(-(l + r) / 2.0f, -(t + b) / 2.0f, -(n + f) / 2.0f);
	Mat4 res = Scale(scale) * Translate(translate);
	return res;
}

// 透视投影
Mat4 Perspective(float fov, float ratio, float zNear, float zFar)
{
	// ratio是宽高比，zNear和zFar都是正值
	// 计算l, r, t, b, n, f
	float n = -zNear, f = -zFar;
	float t = tan(fov / 2.0f) * zNear;
	float b = -t;
	float r = ratio * (t - b) / 2.0f;
	float l = -r;

	// 计算Mp2o
	Mat4 Mp2o(0.0f);
	Mp2o[0][0] = n;
	Mp2o[1][1] = n;
	Mp2o[2][2] = n + f;
	Mp2o[2][3] = -n * f;
	Mp2o[3][2] = 1.0f;

	return Ortho(l, r, t, b, n, f) * Mp2o;
}

// Mat4×Vec4
Vec4 operator*(const Mat4& M, const Vec4& v)
{
	Vec4 res(1.0f);
	for (int i = 0; i < 4; ++i) {
		float sum = 0;
		for (int j = 0; j < 4; ++j) {
			sum += M[i][j] * v[j];
		}
		res[i] = sum;
	}
	return res;
}

// Blin-Phong
Color BlinPhong(const Mat4& normalMatrix, Image* diffuseMap, Triangle& triangle, const Vec3& bary, const Vec3& lightPos, const Vec3& viewPos)
{
	// 计算worldPos
	Vec4* worldPoints = triangle.GetWorldPoints();
	// 归一化其次分量
	//for (int i = 0; i < 3; ++i)worldPoints[i] = worldPoints[i] / worldPoints[i].W();
	Vec3 worldPos = bary.X() * worldPoints[0].XYZ() + bary.Y() * worldPoints[1].XYZ() + bary.Z() * worldPoints[2].XYZ();


	// 计算法向量
	Vec3* normals = triangle.GetNormals();
	Vec3 normal = normalMatrix * Vec4(bary.X() * normals[0] + bary.Y() * normals[1] + bary.Z() * normals[2], 0.0f);
	normal = Normalize(normal);
	//std::cout << "Blin-Phong Matrix: " <<std::endl << normalMatrix << std::endl;
	//std::cout << "Blin-Phong normal: " << normal << std::endl;
	

	// 计算纹理颜色
	Vec2* texCoords = triangle.GetTexCoords();
	Vec2 uv = bary.X() * texCoords[0] + bary.Y() * texCoords[1] + bary.Z() * texCoords[2];
	//std::cout << "Blin-Phong texCoords:" << std::endl;
	//for (int i = 0; i < 3; ++i) {
		//std::cout << texCoords[i] << std::endl;
	//}
	//std::cout << "Blin-Phong bary: " << bary << std::endl;
	//std::cout << "Blin-Phong uv: " << uv << std::endl;
	Color color = diffuseMap->GetPixel(uv);

	// 定义光源强度
	Color lightIntensity(1.0f);

	// 环境光
	float ambi = 0.3;
	Color ambient = ambi * lightIntensity * color;

	// 漫反射
	Vec3 lightDir = Normalize(lightPos - worldPos);
	float diff = std::max(Dot(lightDir, normal), 0.0f);
	Color diffuse = diff * lightIntensity * color;

	// 镜面反射
	Vec3 viewDir = Normalize(viewPos - worldPos);
	Vec3 halfVec = Normalize(lightDir + viewDir);
	// 定义闪光度
	float shininess = 16.0f;
	float spec = std::pow(std::max(Dot(halfVec, normal), 0.0f), shininess);
	Color specular = spec * lightIntensity * color;

	Color res(0.0f);
	for (int i = 0; i < 3; ++i) {
		res[i] = std::min(ambient[i] + diffuse[i] + specular[i], 1.0f);
	}
	//std::cout << color << std::endl;
	return res;
	//return (normal + Vec3(1.0f)) / 2.0f;
}

// max
float Max(float a, float b)
{
	return a > b ? a : b;
}