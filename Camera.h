#pragma once
#include "Vec3.h"
#include "Mat4.h"
#include <easyx.h>
#define NOMINMAX

class Camera {
public:
	Camera();                                                                   // Ĭ�Ϲ��캯��
	Camera(const Vec3& position, const Vec3& worldUp, float yaw, float pitch);
	~Camera();
	Mat4 GetViewMatrix(bool print = false);
	void Listen(ExMessage* msg, float deltaTime, float xOffset, float yOffset); // �����ⲿ�¼�
	Vec3& GetPosition();                                                        // ��ȡ�����λ��
	const Vec3& GetPosition()const;                                             // ��ȡ�����λ��
private:
	Mat4 LookAt(const Vec3& position, const Vec3& center, const Vec3& worldUp); // ����view����
	void UpdateCameraVectors();                                                 // ����yaw��pitch������front��up��right
	void ProcessKeyboard(ExMessage* msg, float deltaTime);                      // ������̰���
	void ProcessMouseMovement(float xOffset, float yOffset);                    // ��������ƶ�

	Vec3 position;                                                              // �����λ��
	Vec3 front;                                                                 // �����ǰ��
	Vec3 up;                                                                    // ������Ϸ�
	Vec3 right;                                                                 // ������ҷ�
	Vec3 worldUp;                                                               // �����Ϸ�
	float yaw;                                                                  // ƫ����
	float pitch;                                                                // ������
};