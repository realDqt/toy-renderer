#include "Screen.h"
#include "Camera.h"
#include "Mat4.h"
#include "Global.h"
#include <iostream>

const int SCR_WIDTH = 800;             // ��Ļ���
const int SCR_HEIGHT = 600;            // ��Ļ�߶�
const int SCR_DEPTH = 1000;            // ��Ļ���

float lastX = 0.0f, lastY = 0.0f;      // �ϴ���������
float lastFrame = 0.0f;                // �ϴ�ʱ��

const Vec3 position(0.0f, 0.0f, 0.0f); // �����λ��
const Vec3 worldUp(0.0f, 1.0f, 0.0f);  // �����Ϸ�
float yaw = -90.0f;                    // ƫ����
float pitch = 0.0f;                    // ������

int main()
{
	// ������Ļ
	Screen screen(SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, Color(1.0f, 1.0f, 1.0f, 1.0f));
	screen.Create();

	// ���������
	Camera camera(position, worldUp, yaw, pitch);
	std::cout << std::endl;

	// ����������
	// ��������
	Vec4* points = new Vec4[3];
	points[0] = Vec4(10, 20, -90);
	points[1] = Vec4(30, 40, -90);
	points[2] = Vec4(20, 10, -90);
	// ������ɫ
	Color* pointColors = new Color[3];
	pointColors[0] = Color(1.0f, 0.0f, 0.0f);
	pointColors[1] = Color(0.0f, 1.0f, 0.0f);
	pointColors[2] = Color(0.0f, 0.0f, 1.0f);
	Triangle triangle(points, NULL);

	// ����MP����
	Mat4 model(1.0f);
	Mat4 view = camera.GetViewMatrix();
	Mat4 projection = Perspective(Radians(90.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
	std::cout << "model: " << std::endl << model << std::endl << std::endl;
	std::cout << "view: " << std::endl << view << std::endl << std::endl;
	std::cout << "projection: " << std::endl << projection << std::endl << std::endl;

	
	// �洢���̺�������Ϣ
	ExMessage *msg = new ExMessage;
	
	// ��ʼ��
	lastFrame = GetTickCount();
	std::cout << "msg->x: " << msg->x << " msg->y: " << msg->y << std::endl << std::endl;
	lastX = msg->x;
	lastY = msg->y;

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
		lastX = msg->x;
		lastY = msg->y;

		// �������ͼ��̲���
		camera.Listen(msg, deltaTime, xOffset, yOffset);

		// ����任
		//Mat4 view = camera.GetViewMatrix(first);
		Mat4 mvp = projection * view * model;
		//if (first)std::cout << "view:\n" << view << std::endl << std::endl;;
		triangle.Transform(mvp, SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, first);
		if (first)first = false;

		// ��դ��
		screen.RasterizeTriangle(triangle, pointColors);
		EndBatchDraw();
	}
	

	screen.Close();
}