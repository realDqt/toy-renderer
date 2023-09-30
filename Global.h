#pragma once
#include "Vec3.h"
#include "Mat3.h"
#include "Mat4.h"

const int INF = 0X3f3f3f3f;
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
