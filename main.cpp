#include "Screen.h"
#include "Camera.h"
#include "Mat4.h"
#include "Global.h"
#include "Model.h"
#include "Image.h"
#include <iostream>
#include <conio.h>

const int SCR_WIDTH = 800;              // ��Ļ���
const int SCR_HEIGHT = 600;             // ��Ļ�߶�
const int SCR_DEPTH = 1000;             // ��Ļ���

float lastX = 0.0f, lastY = 0.0f;       // �ϴ���������
float lastFrame = 0.0f;                 // �ϴ�ʱ��

const Vec3 position(0.0f, 0.0f, 0.0f);  // �������ʼλ��
const Vec3 worldUp(0.0f, 1.0f, 0.0f);   // �����Ϸ�
float yaw = -90.0f;                     // ƫ����
float pitch = 0.0f;                     // ������

Vec3 lightPos(2.0f, 2.0f, 2.0f);        // ��Դλ��
Vec3 viewPos(0.0f, 0.0f, 0.0f);         // �۲�λ��


int main()
{
	// ������Ļ
	Screen screen(SCR_WIDTH, SCR_HEIGHT, SCR_DEPTH, Color(1.0f, 1.0f, 1.0f, 1.0f));
	screen.Create();

	// ���������
	Camera camera(position, worldUp, yaw, pitch);
	std::cout << std::endl;

	// ����ģ��
	const char* filePath = "../models/source/Aiz_v1.0_2.79.obj";
	Model myModel(filePath);

	// ����model����
	Vec3 translate(0.0f, -0.8f, -1.5f);
	Vec3 nx(1.0f, 0.0f, 0.0f), ny(0.0f, 1.0f, 0.0f), nz(0.0f, 0.0f, 1.0f);
	Vec3 scale(1.0f, 1.0f, 1.0f);
	Mat4 model = Translate(translate) * Rotate(ny, 0.5f);

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

		lightPos = Rotate(ny, 0.3f) * Vec4(lightPos, 0.0f);

		// ����DepthMap
		Mat4 view = Camera::LookAt(lightPos, translate, Vec3(0.0f, 1.0f, 0.0f));
		//Mat4 view(1.0f);
		Mat4 mvp = projection * view * model;
		screen.ConstructDepthMap(model, mvp, myModel);

		// ��ʽ��Ⱦ
		view = camera.GetViewMatrix();
		//model = Translate(translate) * Rotate(ny, 0.3f) * Translate(-1.0f * translate) * model;
		mvp = projection * view * model;
		viewPos = camera.GetPosition();
		screen.RenderModel(model, projection, mvp, myModel, lightPos, viewPos, true);

		FlushBatchDraw();

		// ����zBuffer
		screen.ClearZ();
		// ����depthMap
		screen.ClearDepth();
	}
	


	// debug
	/*
	Mat4 test(1.0f);
	for (int i = 0; i < 4; ++i)test[i][i] = static_cast<float>(i + 1);
	Mat4 invT = test.Inverse().Transpose();
	std::cout << "test.inverse: " << std::endl << test.Inverse() << std::endl;
	std::cout << "test.transpose: " << std::endl << test.Transpose() << std::endl;
	std::cout << "test.inverse.transpose: " << std::endl << invT << std::endl;
	*/
	EndBatchDraw();
	_getch();
	screen.Close();
}