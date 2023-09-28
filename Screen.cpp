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
	
	// Ϊ��Ȼ��������ڴ�
	zBuffer = new float[width * height];
	// ��ʼ����Ȼ���Ϊ���ֵ
	for (int i = 0; i < width * height; ++i)zBuffer[i] = static_cast<float>(depth);
}

Screen::~Screen()
{
	delete[] zBuffer;
}

void Screen::Create()
{
	initgraph(width, height);
	// ��[0, 1]ӳ����[0, 255]
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

// ��ȡָ��λ�õ���ɫ
Color Screen::GetPixel(int x, int y)
{
	COLORREF tem = getpixel(x, height - y);
	Color res(GetRValue(tem), GetGValue(tem), GetBValue(tem));
	return res;
}

// ��ָ��λ������Ϊָ����ɫ
void Screen::SetPixel(int x, int y, Color color)
{
	// ��[0, 1]ӳ����[0, 255]
	int r = static_cast<int>(color.R() * 255);
	int g = static_cast<int>(color.G() * 255);
	int b = static_cast<int>(color.B() * 255);
	putpixel(x, height - y, RGB(r, g, b));
}

// ��դ�������Σ������εĶ�����������Ļ����
void Screen::RasterizeTriangle(Triangle& triangle, Color* pointColors)
{
	// ���������ΰ�Χ��
	Vec2 bboxmin(static_cast<float>(width), static_cast<float>(height));
	Vec2 bboxmax(0.0f, 0.0f);
	for (int i = 0; i < 3; ++i) {
		bboxmin.SetX(std::min(bboxmin.X(), triangle[i].X()));
		bboxmin.SetY(std::min(bboxmin.Y(), triangle[i].Y()));

		bboxmax.SetX(std::max(bboxmax.X(), triangle[i].X()));
		bboxmax.SetY(std::max(bboxmax.Y(), triangle[i].Y()));
	}
	// ƫ��������
	float offsetX[4] = { -0.25f, 0.25f, 0.25f, -0.25f };
	float offsetY[4] = { 0.25f, 0.25f, -0.25f, -0.25f };
	// ������Χ���е�ÿһ������
	for (int x = bboxmin.X(); x <= bboxmax.X(); ++x) {
		for (int y = bboxmin.Y(); y <= bboxmax.Y(); ++y) {
			Color color(0.0f, 0.0f, 0.0f, 1.0f);
			// ���ز��������
			for (int i = 0; i < 4; ++i) {
				// ����ƫ�ƺ������
				float nx = static_cast<float>(x) + offsetX[i];
				float ny = static_cast<float>(y) + offsetY[i];
				// ������������
				Vec3 bary = triangle.Barycentric(Vec2(nx, ny));
				// �ж��Ƿ����������ڲ�
				if (!InRange(bary.X(), 0.0f, 1.0f) || !InRange(bary.Y(), 0.0f, 1.0f) || !InRange(bary.Z(), 0.0f, 1.0f))
					continue;
				// ��ֵ������ɫ
				Color sampleColor = bary.X() * pointColors[0] + bary.Y() * pointColors[1] + bary.Z() * pointColors[2];
				// �ۼ���color
				color = color + 0.25 * sampleColor;
			}
			// ������������
			Vec3 bary = triangle.Barycentric(Vec2(x, y));
			// ��Ȳ���
			float z = bary.X() * triangle[0].Z() + bary.Y() * triangle[1].Z() + bary.Z() * triangle[2].Z();
			// ��ά����ת����һά���꣬ע�ⷴתy��
			int idx = (height - y) * width + x;
		    if (z > zBuffer[idx])continue;
			if(color != Color(0.0f, 0.0f, 0.0f, 1.0f))SetPixel(x, y, color);
			// ����zBuffer
			zBuffer[idx] = z;
		}
	}
}