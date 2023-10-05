#include "Screen.h"
#include "Camera.h"
#include "Mat4.h"
#include "Global.h"
#include "Model.h"
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

	// ����ģ��
	const char* filePath = "E:/toyRenderer/models/source/Aiz_v1.0_2.79.obj";
	Model myModel(filePath);

	// ����model����
	Vec3 translate(100.0f, 0.0f, 0.0f);
	Vec3 n(0.0f, 0.0f, 1.0f);
	Vec3 scale(200.0f, 200.0f, 200.0f);
	Mat4 model = Translate(translate) * Scale(scale);
	model = Mat4(1.0f);

	// ����projection����
	float fov = Radians(90.0f);
	float ratio = (float)SCR_WIDTH / SCR_HEIGHT;
	float zNear = 0.1f;
	float zFar = 100.0f;
	Mat4 projection = Perspective(fov, ratio, zNear, zFar);
	
	// �洢���̺�������Ϣ
	ExMessage *msg = new ExMessage;
	
	// ��ʼ��
	lastFrame = GetTickCount();
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
		// ע��y�ᷴת
		float yOffset = lastY - msg->y;
		lastX = msg->x;
		lastY = msg->y;

		// �������ͼ��̲���
		//camera.Listen(msg, deltaTime, xOffset, yOffset);

		// ����mvp����
		//Mat4 view = camera.GetViewMatrix(first);
		//Mat4 mvp = projection * view * model;

		// ����ģ��
		screen.RenderModel(myModel);
		FlushBatchDraw();

		// ����zBuffer
		screen.ClearZ();
	}
	EndBatchDraw();
	_getch();
	screen.Close();
}