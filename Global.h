#pragma once
#include "Vec3.h"
const int INF = 0X3f3f3f3f;

// �ж�k�Ƿ���������[min, max]
bool InRange(float k, float min, float max);

// ����Vec3�ڻ�
float Dot(const Vec3& a, const Vec3& b);

// �ж��������������
bool FloatEqual(float a, float b);

