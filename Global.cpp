#include "global.h"
#include <cmath>

// �ж�k�Ƿ���������[min, max]
bool InRange(float k, float min, float max)
{
	return k >= min && k <= max;
}

// ����Vec3�ڻ�
float Dot(const Vec3& a, const Vec3& b)
{
	return a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z();
}

// �ж��������������
bool FloatEqual(float a, float b)
{
	return fabs(a - b) < 0.0001f;
}