#include "Screen.h"
#include "Camera.h"
#include "Mat4.h"
#include "Global.h"
#include <iostream>

const int SCR_WIDTH = 800;        // ��Ļ���
const int SCR_HEIGHT = 600;       // ��Ļ�߶�
const int SCR_DEPTH = 1000;       // ��Ļ���

float lastX = 0.0f, lastY = 0.0f; // �ϴ���������
float lastFrame = 0.0f;           // �ϴ�ʱ��
int main()
{
	// ������Ļ
	Screen screen(SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, Color(1.0f, 1.0f, 1.0f, 1.0f));
	screen.Create();

	// ���������
	Camera camera;

	// ����������
	// ��������
	Vec4* points = new Vec4[3];
	points[0] = Vec4(0.1, 0.2, -90);
	points[1] = Vec4(0.3, 0.4, -90);
	points[2] = Vec4(0.2, 0.1, -90);
	// ������ɫ
	Color* pointColors = new Color[3];
	pointColors[0] = Color(1.0f, 0.0f, 0.0f);
	pointColors[1] = Color(0.0f, 1.0f, 0.0f);
	pointColors[2] = Color(0.0f, 0.0f, 1.0f);
	Triangle triangle(points, NULL);

	// ����MP����
	Mat4 model(1.0f);
	Mat4 projection = Perspective(Radians(90.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 4.0f);

	
	// �洢������Ϣ
	ExMessage *msg = new ExMessage;
	// �洢�����Ϣ
	
	
	// ��ʼ��lastFrame
	lastFrame = GetTickCount();

	bool first = true;
	
	// ��Ⱦѭ��
	while (1) {
		cleardevice();
		BeginBatchDraw();
		peekmessage(msg, EX_MOUSE);
		// ����deltaTime
		float currentFrame = GetTickCount();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// ����xOffset��yOffset
		float xOffset = msg->x - lastX;
		float yOffset = msg->y - lastY;

		// �������ͼ��̲���
		camera.Listen(msg, deltaTime, xOffset, yOffset);

		// ����任
		Mat4 view = camera.GetViewMatrix();
		Mat4 mvp = projection * view * model;
		triangle.Transform(mvp, SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, first);
		if (first)first = false;

		// ��դ��
		screen.RasterizeTriangle(triangle, pointColors);
		EndBatchDraw();
	}
	

	screen.Close();
}