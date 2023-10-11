#pragma once
#include "Color.h"
#include "Vec2.h"
#include <easyx.h>
#define NOMINMAX
class Image {
public:
	Image(const char* filePath);
	~Image();
	Color GetPixel(float u, float v); // ��ȡָ��λ�õ���ɫ
	Color GetPixel(Vec2 uv);          // ��ȡָ��λ�õ���ɫ
private:
	IMAGE* img;
};
