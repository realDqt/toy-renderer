#include "Screen.h"
int main()
{
	// ������Ļ
	Screen screen(800, 600, 1000, Color(1.0f, 1.0f, 1.0f, 1.0f));
	screen.Create();

	// ����������
	// ��������
	Vec4* points = new Vec4[3];
	points[0] = Vec4(100, 100, 1);
	points[1] = Vec4(700, 200, 1);
	points[2] = Vec4(400, 500, 1);
	// ��ɫ
	Color* pointColors = new Color[3];
	pointColors[0] = Color(1.0f, 0.0f, 0.0f);
	pointColors[1] = Color(0.0f, 1.0f, 0.0f);
	pointColors[2] = Color(0.0f, 0.0f, 1.0f);
	Triangle triangle(points, NULL);

	// ��Ⱦѭ��
	while (1) {
		cleardevice();
		BeginBatchDraw();
		screen.RasterizeTriangle(triangle, pointColors);
		EndBatchDraw();
	}

	screen.Close();
}