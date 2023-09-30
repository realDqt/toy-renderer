#include "Camera.h"
#include "Global.h"

// 默认构造函数
Camera::Camera()
{
	position = Vec3(0.0f);
	worldUp = Vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	UpdateCameraVectors();
}

Camera::Camera(const Vec3& position, const Vec3& worldUp, float yaw, float pitch)
{
	this->position = position;
	this->worldUp = worldUp;
	this->yaw = yaw;
	this->pitch = pitch;
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

Mat4 Camera::GetViewMatrix()
{
	return LookAt(position, position + front, worldUp);
}

Mat4 Camera::LookAt(const Vec3& position, const Vec3& center, const Vec3& worldUp)
{
	// 建立相机坐标系
	Vec3 zAxis = Normalize(position - center);
	Vec3 xAxis = Normalize(Cross(worldUp, zAxis));
	Vec3 yAxis = Cross(zAxis, xAxis);

	// 计算旋转矩阵
	Mat4 rotate(1.0f);
	for (int i = 0; i < 3; ++i)rotate[0][i] = xAxis[i];
	for (int i = 0; i < 3; ++i)rotate[1][i] = yAxis[i];
	for (int i = 0; i < 3; ++i)rotate[2][i] = zAxis[i];

	// 计算平移矩阵
	Mat4 translate(1.0f);
	for (int i = 0; i < 3; ++i)translate[i][3] = -position[i];

	// 先平移后旋转
	return rotate * translate;
}

// 根据yaw和pitch，更新front、up和right
void Camera::UpdateCameraVectors()
{
	float p = Radians(pitch);
	float y = Radians(yaw);
	front[0] = cos(p) * cos(y);
	front[1] = sin(p);
	front[2] = cos(p) * sin(y);
	right = Normalize(Cross(front, worldUp));
	up = Cross(right, front);
}

// 处理键盘按下
void Camera::ProcessKeyboard(ExMessage* msg, float deltaTime)
{
	if (peekmessage(msg, EX_KEY)) {
		float distance = 2.5f * deltaTime;
		switch(msg->vkcode) {
		case 0x57:
			// 按下W
			position = position +  distance * front;
			break;
		case 0x53:
			// 按下S
			position = position - distance * front;
			break;
		case 0x41:
			// 按下A
			position = position - distance * right;
			break;
		case 0x44:
			// 按下D
			position = position + distance * right;
			break;
		default:
			break;
		}
	}
}

// 处理鼠标移动
void Camera::ProcessMouseMovement(float xOffset, float yOffset)
{
	xOffset *= 0.1f;
	yOffset *= 0.1f;

	pitch += yOffset;
	yaw += xOffset;

	UpdateCameraVectors();
}

// 监听外部事件
void Camera::Listen(ExMessage* msg, float deltaTime, float xOffset, float yOffset)
{
	ProcessKeyboard(msg, deltaTime);
	ProcessMouseMovement(xOffset, yOffset);
}