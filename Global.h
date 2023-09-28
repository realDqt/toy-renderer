#pragma once
#include "Vec3.h"
const int INF = 0X3f3f3f3f;

// 判断k是否属于区间[min, max]
bool InRange(float k, float min, float max);

// 计算Vec3内积
float Dot(const Vec3& a, const Vec3& b);

// 判断两个浮点数相等
bool FloatEqual(float a, float b);

