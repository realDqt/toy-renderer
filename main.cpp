#include "Screen.h"
int main()
{
	// 创建屏幕
	Screen screen(800, 600, 1000, Color(1.0f, 1.0f, 1.0f, 1.0f));
	screen.Create();

	// 构造三角形
	// 顶点坐标
	Vec4* points = new Vec4[3];
	points[0] = Vec4(100, 100, 1);
	points[1] = Vec4(700, 200, 1);
	points[2] = Vec4(400, 500, 1);
	// 颜色
	Color* pointColors = new Color[3];
	pointColors[0] = Color(1.0f, 0.0f, 0.0f);
	pointColors[1] = Color(0.0f, 1.0f, 0.0f);
	pointColors[2] = Color(0.0f, 0.0f, 1.0f);
	Triangle triangle(points, NULL);

	// 渲染循环
	while (1) {
		cleardevice();
		BeginBatchDraw();
		screen.RasterizeTriangle(triangle, pointColors);
		EndBatchDraw();
	}

	screen.Close();
}