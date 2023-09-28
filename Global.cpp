#include "global.h"
#include <cmath>

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

// 判断两个浮点数相等
bool FloatEqual(float a, float b)
{
	return fabs(a - b) < 0.0001f;
}