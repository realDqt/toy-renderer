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
	void Create();                                                      // 创建窗口
	void Close();                                                       // 关闭窗口
	int GetWidth();
	int GetHeight();
	Color GetPixel(int x, int y);                                       // 获取指定位置的颜色
	void SetPixel(int x, int y, Color color);                           // 将指定位置设置为指定颜色
	void RasterizeTriangle(Triangle& triangle, Color* pointColors);     // 光栅化三角形，三角形的顶点坐标是屏幕坐标
	void RasterizeTriangleMSAA(Triangle& triangle, Color* pointColors); // MSAA
	void RasterizeTriangle(const Mat4& normalMatrix, Image* diffuseMap, Triangle& triangle, const Vec3& lightPos, const Vec3& viewPos);  // 光栅化三角形，正式进行光照计算
	void RenderModel(const Mat4& m, const Mat4& mvp, Model& model, const Vec3& lightPos, const Vec3& viewPos);                           // 绘制模型
	void RenderModel(Model& model);                                     // 绘制原始模型
	void ClearZ();                                                      // 清理zBuffer
private:
	bool InScreen(Triangle& triangle);                                  // 判断三角形是否在屏幕内
	int width;                                                          // 窗口宽度
	int height;                                                         // 窗口高度
	int depth;                                                          // 窗口深度
	Color bgColor;                                                      // 背景颜色
	float* zBuffer;                                                     // z缓冲
};
