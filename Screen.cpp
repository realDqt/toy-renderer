#include "Screen.h"
#include "Global.h"
#include <cstring>
#include <algorithm>
Screen::Screen(int width, int height, int depth, Color bgColor)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->bgColor = bgColor;
	
	// 为深度缓冲申请内存
	zBuffer = new float[width * height];
	// 初始化深度缓冲为最大值
	for (int i = 0; i < width * height; ++i)zBuffer[i] = static_cast<float>(depth);
}

Screen::~Screen()
{
	delete[] zBuffer;
}

void Screen::Create()
{
	initgraph(width, height);
	// 从[0, 1]映射至[0, 255]
	int r = static_cast<int>(bgColor.R() * 255);
	int g = static_cast<int>(bgColor.G() * 255);
	int b = static_cast<int>(bgColor.B() * 255);
	setbkcolor(RGB(r, g, b));
	cleardevice();
}

void Screen::Close()
{
	closegraph();
}

int Screen::GetWidth()
{
	return width;
}

int Screen::GetHeight()
{
	return height;
}

// 获取指定位置的颜色
Color Screen::GetPixel(int x, int y)
{
	COLORREF tem = getpixel(x, height - y);
	Color res(GetRValue(tem), GetGValue(tem), GetBValue(tem));
	return res;
}

// 将指定位置设置为指定颜色
void Screen::SetPixel(int x, int y, Color color)
{
	// 从[0, 1]映射至[0, 255]
	int r = static_cast<int>(color.R() * 255);
	int g = static_cast<int>(color.G() * 255);
	int b = static_cast<int>(color.B() * 255);
	putpixel(x, height - y, RGB(r, g, b));
}

// 光栅化三角形，三角形的顶点坐标是屏幕坐标
void Screen::RasterizeTriangle(Triangle& triangle, Color* pointColors)
{
	// 计算三角形包围盒
	Vec2 bboxmin(static_cast<float>(width), static_cast<float>(height));
	Vec2 bboxmax(0.0f, 0.0f);
	for (int i = 0; i < 3; ++i) {
		bboxmin.SetX(std::min(bboxmin.X(), triangle[i].X()));
		bboxmin.SetY(std::min(bboxmin.Y(), triangle[i].Y()));

		bboxmax.SetX(std::max(bboxmax.X(), triangle[i].X()));
		bboxmax.SetY(std::max(bboxmax.Y(), triangle[i].Y()));
	}
	// 偏移量数组
	float offsetX[4] = { -0.25f, 0.25f, 0.25f, -0.25f };
	float offsetY[4] = { 0.25f, 0.25f, -0.25f, -0.25f };
	// 遍历包围盒中的每一个像素
	for (int x = bboxmin.X(); x <= bboxmax.X(); ++x) {
		for (int y = bboxmin.Y(); y <= bboxmax.Y(); ++y) {
			Color color(0.0f, 0.0f, 0.0f, 1.0f);
			// 多重采样抗锯齿
			for (int i = 0; i < 4; ++i) {
				// 计算偏移后的坐标
				float nx = static_cast<float>(x) + offsetX[i];
				float ny = static_cast<float>(y) + offsetY[i];
				// 计算重心坐标
				Vec3 bary = triangle.Barycentric(Vec2(nx, ny));
				// 判断是否在三角形内部
				if (!InRange(bary.X(), 0.0f, 1.0f) || !InRange(bary.Y(), 0.0f, 1.0f) || !InRange(bary.Z(), 0.0f, 1.0f))
					continue;
				// 插值计算颜色
				Color sampleColor = bary.X() * pointColors[0] + bary.Y() * pointColors[1] + bary.Z() * pointColors[2];
				// 累加至color
				color = color + 0.25 * sampleColor;
			}
			// 计算重心坐标
			Vec3 bary = triangle.Barycentric(Vec2(x, y));
			// 深度测试
			float z = bary.X() * triangle[0].Z() + bary.Y() * triangle[1].Z() + bary.Z() * triangle[2].Z();
			// 二维坐标转换至一维坐标，注意反转y轴
			int idx = (height - y) * width + x;
		    if (z > zBuffer[idx])continue;
			if(color != Color(0.0f, 0.0f, 0.0f, 1.0f))SetPixel(x, y, color);
			// 更新zBuffer
			zBuffer[idx] = z;
		}
	}
}