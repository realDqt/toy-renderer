#pragma once
#define NOMINMAX
#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Color.h"
#include "Triangle.h"
#include "Image.h"


const float INF = 3.40282e+38;
const float PI = 3.1415926f;

// �ж�k�Ƿ���������[min, max]
bool InRange(float k, float min, float max);

// ����Vec3�ڻ�
float Dot(const Vec3& a, const Vec3& b);

// ����Vec3���
Vec3 Cross(const Vec3& a, const Vec3& b);

// ����Vec3����
float Length(const Vec3& v);

// ��׼��Vec3
Vec3 Normalize(const Vec3& v);

// �Ƕ�ת����
float Radians(float angle);

// �ж��������������
bool FloatEqual(float a, float b);

// ƽ�ƺ���
Mat4 Translate(const Vec3& translate);

// ��ת����
Mat4 Rotate(const Vec3& n, float alpha);

// ���ź���
Mat4 Scale(const Vec3& scale);

// ����ͶӰ
Mat4 Ortho(float l, float r, float t, float b, float n, float f);

// ͸��ͶӰ
Mat4 Perspective(float fov, float ratio, float zNear, float zFar);

// Mat4��Vec4
Vec4 operator* (const Mat4& M, const Vec4& v);

// Blin-Phong
Color BlinPhong(const Mat4& normalMatrix, Image* diffuseMap, Triangle& triangle, const Vec3& bary, const Vec3& lightPos, const Vec3& viewPos);

// max
float Max(float a, float b);
