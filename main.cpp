#include "Screen.h"
#include "Camera.h"
#include "Mat4.h"
#include "Global.h"
#include <iostream>

const int SCR_WIDTH = 800;        // 屏幕宽度
const int SCR_HEIGHT = 600;       // 屏幕高度
const int SCR_DEPTH = 1000;       // 屏幕深度

float lastX = 0.0f, lastY = 0.0f; // 上次鼠标的坐标
float lastFrame = 0.0f;           // 上次时间
int main()
{
	// 创建屏幕
	Screen screen(SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, Color(1.0f, 1.0f, 1.0f, 1.0f));
	screen.Create();

	// 创建摄像机
	Camera camera;

	// 构造三角形
	// 顶点坐标
	Vec4* points = new Vec4[3];
	points[0] = Vec4(0.1, 0.2, -90);
	points[1] = Vec4(0.3, 0.4, -90);
	points[2] = Vec4(0.2, 0.1, -90);
	// 顶点颜色
	Color* pointColors = new Color[3];
	pointColors[0] = Color(1.0f, 0.0f, 0.0f);
	pointColors[1] = Color(0.0f, 1.0f, 0.0f);
	pointColors[2] = Color(0.0f, 0.0f, 1.0f);
	Triangle triangle(points, NULL);

	// 计算MP矩阵
	Mat4 model(1.0f);
	Mat4 projection = Perspective(Radians(90.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 4.0f);

	
	// 存储键盘信息
	ExMessage *msg = new ExMessage;
	// 存储鼠标信息
	
	
	// 初始化lastFrame
	lastFrame = GetTickCount();

	bool first = true;
	
	// 渲染循环
	while (1) {
		cleardevice();
		BeginBatchDraw();
		peekmessage(msg, EX_MOUSE);
		// 计算deltaTime
		float currentFrame = GetTickCount();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 计算xOffset和yOffset
		float xOffset = msg->x - lastX;
		float yOffset = msg->y - lastY;

		// 监听鼠标和键盘操作
		camera.Listen(msg, deltaTime, xOffset, yOffset);

		// 坐标变换
		Mat4 view = camera.GetViewMatrix();
		Mat4 mvp = projection * view * model;
		triangle.Transform(mvp, SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, first);
		if (first)first = false;

		// 光栅化
		screen.RasterizeTriangle(triangle, pointColors);
		EndBatchDraw();
	}
	

	screen.Close();
}