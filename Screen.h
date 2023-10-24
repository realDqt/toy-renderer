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
	int GetWidth()const;
	int GetHeight()const;
	float* GetDepthMap()const;                                          // ��ȡ�����ͼ
	Color GetPixel(int x, int y);                                       // ��ȡָ��λ�õ���ɫ
	void SetPixel(int x, int y, Color color);                           // ��ָ��λ������Ϊָ����ɫ
	void RasterizeTriangle(Triangle& triangle, Color* pointColors);     // ��դ�������Σ������εĶ�����������Ļ����
	void RasterizeTriangleDepthMap(Triangle& triangle);                 // ��դ�������Σ�����depthMap 
	void RasterizeTriangleMSAA(Triangle& triangle, Color* pointColors); // MSAA
	void RasterizeTriangle(const Mat4& p, const Mat4& normalMatrix, Image* diffuseMap, Triangle& triangle, const Vec3& lightPos, const Vec3& viewPos, bool shadow = false);  // ��դ�������Σ���ʽ���й��ռ���
	void RenderModel(const Mat4& m, const Mat4& p, const Mat4& mvp, Model& model, const Vec3& lightPos, const Vec3& viewPos, bool shadow = false);                           // ����ģ��
	void RenderModel(Model& model);                                     // ����ԭʼģ��
	void ConstructDepthMap(const Mat4& m,const Mat4& mvp, Model& model);// ��Դ�ӽ���Ⱦ������depthMap
	void ClearZ();                                                      // ����zBuffer
	void ClearDepth();                                                  // ����depthMap
private:
	int width;                                                          // ���ڿ��
	int height;                                                         // ���ڸ߶�
	int depth;                                                          // �������
	Color bgColor;                                                      // ������ɫ
	float* zBuffer;                                                     // z����
	float* depthMap;                                                    // �����ͼ
};
