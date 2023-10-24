#pragma once
#include "Vec2.h"
#include "Vec4.h"
#include "Mat4.h"
class Triangle {
public:
	
	Triangle();                                                       // Ĭ�Ϲ��캯��
	Triangle(Triangle& rhs);                                          // �������캯��
	Triangle(Vec4* points, Vec2* texCoords, Vec3* normals = NULL);
	~Triangle();
	Vec4 GetA();
	Vec4 GetB();
	Vec4 GetC();
	void SetA(Vec4& A);
	void SetB(Vec4& B);
	void SetC(Vec4& C);
	Vec3 Barycentric(Vec2 point);
	void Transform(const Mat4& mvp, int width, int height, bool print = false); // ���MVP�任��͸�ӳ������ӿڱ任 
	void CalcWorldPoints(const Mat4& model);                           // �����������������
	Vec4* GetWorldPoints();                                            // ��ȡ��������������
	Vec3* GetNormals();                                                // ��ȡ�����㷨����
	Vec2* GetTexCoords();                                              // ��ȡ��������������
	Vec4& operator[](int idx);
	const Vec4& operator[](int idx)const;
private:
	Vec4 points[3];                                                    // ��������
	Vec4 worldPoints[3];                                               // ��������
	Vec4 oriPoints[3];                                                 // ����Ķ�������
	Vec2 texCoords[3];                                                 // ��������
	Vec3 normals[3];                                                   // ���㷨����
};
