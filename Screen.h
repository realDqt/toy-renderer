#pragma once
#define NOMINMAX
#include "Color.h"
#include "Triangle.h"
#include "Model.h"
#include <easyx.h>
class Screen {
public:
	Screen(int width, int height, int depth, Color bgColor);
	~Screen();
	void Create();                                                      // ��������
	void Close();                                                       // �رմ���
	int GetWidth();
	int GetHeight();
	Color GetPixel(int x, int y);                                       // ��ȡָ��λ�õ���ɫ
	void SetPixel(int x, int y, Color color);                           // ��ָ��λ������Ϊָ����ɫ
	void RasterizeTriangle(Triangle& triangle, Color* pointColors);     // ��դ�������Σ������εĶ�����������Ļ����
	void RasterizeTriangleMSAA(Triangle& triangle, Color* pointColors); // MSAA
	void RenderModel(const Mat4& mvp, Model& model);                    // ����ģ��
	void RenderModel(Model& model);                                     // ����ԭʼģ��
	void ClearZ();                                                      // ����zBuffer
private:
	bool InScreen(Triangle& triangle);                                  // �ж��������Ƿ�����Ļ��
	int width;                                                          // ���ڿ��
	int height;                                                         // ���ڸ߶�
	int depth;                                                          // �������
	Color bgColor;                                                      // ������ɫ
	float* zBuffer;                                                     // z����
};
