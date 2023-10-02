#include "Screen.h"
#include "Camera.h"
#include "Mat4.h"
#include "Global.h"
#include <iostream>

const int SCR_WIDTH = 800;             // 屏幕宽度
const int SCR_HEIGHT = 600;            // 屏幕高度
const int SCR_DEPTH = 1000;            // 屏幕深度

float lastX = 0.0f, lastY = 0.0f;      // 上次鼠标的坐标
float lastFrame = 0.0f;                // 上次时间

const Vec3 position(0.0f, 0.0f, 0.0f); // 摄像机位置
const Vec3 worldUp(0.0f, 1.0f, 0.0f);  // 世界上方
float yaw = -90.0f;                    // 偏航角
float pitch = 0.0f;                    // 俯仰角

int main()
{
	// 创建屏幕
	Screen screen(SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, Color(1.0f, 1.0f, 1.0f, 1.0f));
	screen.Create();

	// 创建摄像机
	Camera camera(position, worldUp, yaw, pitch);
	std::cout << std::endl;

	// 构造三角形
	// 顶点坐标
	Vec4* points = new Vec4[3];
	points[0] = Vec4(10, 20, -90);
	points[1] = Vec4(30, 40, -90);
	points[2] = Vec4(20, 10, -90);
	// 顶点颜色
	Color* pointColors = new Color[3];
	pointColors[0] = Color(1.0f, 0.0f, 0.0f);
	pointColors[1] = Color(0.0f, 1.0f, 0.0f);
	pointColors[2] = Color(0.0f, 0.0f, 1.0f);
	Triangle triangle(points, NULL);

	// 计算MP矩阵
	Mat4 model(1.0f);
	Mat4 view = camera.GetViewMatrix();
	Mat4 projection = Perspective(Radians(90.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
	std::cout << "model: " << std::endl << model << std::endl << std::endl;
	std::cout << "view: " << std::endl << view << std::endl << std::endl;
	std::cout << "projection: " << std::endl << projection << std::endl << std::endl;

	
	// 存储键盘和鼠标的信息
	ExMessage *msg = new ExMessage;
	
	// 初始化
	lastFrame = GetTickCount();
	std::cout << "msg->x: " << msg->x << " msg->y: " << msg->y << std::endl << std::endl;
	lastX = msg->x;
	lastY = msg->y;

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
		lastX = msg->x;
		lastY = msg->y;

		// 监听鼠标和键盘操作
		camera.Listen(msg, deltaTime, xOffset, yOffset);

		// 坐标变换
		//Mat4 view = camera.GetViewMatrix(first);
		Mat4 mvp = projection * view * model;
		//if (first)std::cout << "view:\n" << view << std::endl << std::endl;;
		triangle.Transform(mvp, SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, first);
		if (first)first = false;

		// 光栅化
		screen.RasterizeTriangle(triangle, pointColors);
		EndBatchDraw();
	}
	

	screen.Close();
}