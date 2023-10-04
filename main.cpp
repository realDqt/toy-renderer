#include "Screen.h"
#include "Camera.h"
#include "Mat4.h"
#include "Global.h"
#include <iostream>
#include <conio.h>

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

	// ����������0
	// ��������
	Vec4* points0 = new Vec4[3];
	points0[0] = Vec4(10, 10, -20);
	points0[1] = Vec4(10, 30, -20);
	points0[2] = Vec4(30, 30, -20);
	Triangle triangle0(points0, NULL);
	// ����������1
	Vec4* points1 = new Vec4[3];
	points1[0] = Vec4(30, 30, -20);
	points1[1] = Vec4(30, 10, -20);
	points1[2] = Vec4(10, 10, -20);
	Triangle triangle1(points1, NULL);
	// ������ɫ
	Color* pointColors = new Color[3];
	pointColors[0] = Color(1.0f, 0.0f, 0.0f);
	pointColors[1] = Color(0.0f, 1.0f, 0.0f);
	pointColors[2] = Color(0.0f, 0.0f, 1.0f);
	// ����MP����
	Mat4 model(1.0f);
	const Vec3 translate(1.0f, 0.0f, 0.0f);
	const Vec3 n(0.0f, 0.0f, 1.0f);
	const Vec3 scale(2.0f, 2.0f, 2.0f);
	//Mat4 view = camera.GetViewMatrix();
	// �������
	float fov = Radians(90.0f);
	float ratio = (float)SCR_WIDTH / SCR_HEIGHT;
	float zNear = 0.1f;
	float zFar = 100.0f;
	Mat4 projection = Perspective(fov, ratio, zNear, zFar);
	
	std::cout << "model: " << std::endl << model << std::endl << std::endl;
	//std::cout << "view: " << std::endl << view << std::endl << std::endl;
	std::cout << "projection: " << std::endl << projection << std::endl << std::endl;

	
	// �洢���̺�������Ϣ
	ExMessage *msg = new ExMessage;
	
	// ��ʼ��
	lastFrame = GetTickCount();
	std::cout << "msg->x: " << msg->x << " msg->y: " << msg->y << std::endl << std::endl;
	lastX = msg->x;
	lastY = msg->y;

	bool first = true;
	BeginBatchDraw();
	
	// ��Ⱦѭ��
	while (1) {
		cleardevice();
		//peekmessage(msg, EX_MOUSE);
		// ����deltaTime
		float currentFrame = GetTickCount();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// ����xOffset��yOffset
		float xOffset = msg->x - lastX;
		float yOffset = msg->y - lastY;
		std::cout << "xOffset: " << xOffset << "yOffset: " << yOffset << std::endl;
		lastX = msg->x;
		lastY = msg->y;

		// �������ͼ��̲���
		camera.Listen(msg, deltaTime, xOffset, -yOffset);

		// ����任
		Sleep(50);
		model = Rotate(n, 0.5f) * model;
		Mat4 view = camera.GetViewMatrix(first);
		Mat4 mvp = projection * view * model;
		//if (first)std::cout << "view:\n" << view << std::endl << std::endl;;
		triangle0.Transform(mvp, SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, first);
		triangle1.Transform(mvp, SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, first);
		if (first)first = false;

		// ��դ��
		screen.RasterizeTriangle(triangle0, pointColors);
		screen.RasterizeTriangle(triangle1, pointColors);
		FlushBatchDraw();
		// ����zBuffer
		screen.ClearZ();
	}
	
	EndBatchDraw();
	_getch();
	screen.Close();
}