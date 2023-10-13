#include "Screen.h"
#include "Global.h"
#include <cstring>
#include <algorithm>
#include <iostream>
Screen::Screen(int width, int height, int depth, Color bgColor)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->bgColor = bgColor;
	
	// Ϊ��Ȼ��������ڴ�
	zBuffer = new float[width * height];
	// ��ʼ����Ȼ���Ϊ��Զֵ
	for (int i = 0; i < width * height; ++i)zBuffer[i] = -INF;
}

Screen::~Screen()
{
	delete[] zBuffer;
}

void Screen::Create()
{
	initgraph(width, height);
	// ��[0, 1]ӳ����[0, 255]
	int r = static_cast<int>(bgColor.R() * 255);
	int g = static_cast<int>(bgColor.G() * 255);
	int b = static_cast<int>(bgColor.B() * 255);
	setbkcolor(RGB(r, g, b));
	cleardevice();
}

void Screen::Close()
{
	closegraph();
}

int Screen::GetWidth()
{
	return width;
}

int Screen::GetHeight()
{
	return height;
}

// ��ȡָ��λ�õ���ɫ
Color Screen::GetPixel(int x, int y)
{
	COLORREF tem = getpixel(x, height - y);
	// ��[0, 255]ӳ����[0, 1]
	float r = static_cast<float>(GetRValue(tem) / 255.0f);
	float g = static_cast<float>(GetGValue(tem) / 255.0f);
	float b = static_cast<float>(GetBValue(tem) / 255.0f);
	Color res(r, g, b);
	return res;
}

// ��ָ��λ������Ϊָ����ɫ
void Screen::SetPixel(int x, int y, Color color)
{
	// ��[0, 1]ӳ����[0, 255]
	int r = static_cast<int>(color.R() * 255);
	int g = static_cast<int>(color.G() * 255);
	int b = static_cast<int>(color.B() * 255);
	putpixel(x, height - y, RGB(r, g, b));
}

// ��դ�������Σ������εĶ�����������Ļ����
void Screen::RasterizeTriangle(Triangle& triangle, Color* pointColors)
{

	//std::cout << "In Screen!" << std::endl;
	//for (int i = 0; i < 3; ++i)std::cout << triangle[i] << std::endl;
	//std::cout << std::endl;
	// ���������ΰ�Χ��
	Vec2 bboxmin(INF, INF);
	Vec2 bboxmax(-INF, -INF);
	for (int i = 0; i < 3; ++i) {
		bboxmin.SetX(std::min(bboxmin.X(), triangle[i].X()));
		bboxmin.SetY(std::min(bboxmin.Y(), triangle[i].Y()));

		bboxmax.SetX(std::max(bboxmax.X(), triangle[i].X()));
		bboxmax.SetY(std::max(bboxmax.Y(), triangle[i].Y()));
	}
	//std::cout << "minx: " << bboxmin.X() << " miny: " << bboxmin.Y() << std::endl;
	//std::cout << "maxx: " << bboxmax.X() << " maxy: " << bboxmax.Y() << std::endl;
	// ƫ��������
	float offsetX[4] = { -0.25f, 0.25f, 0.25f, -0.25f };
	float offsetY[4] = { 0.25f, 0.25f, -0.25f, -0.25f };
	// ������Χ���е�ÿһ������
	for (int x = bboxmin.X(); x <= bboxmax.X(); ++x) {
		for (int y = bboxmin.Y(); y <= bboxmax.Y(); ++y) {
			// ������������
			Vec3 bary = triangle.Barycentric(Vec2(x, y));
			// �ж��Ƿ����������ڲ�
			if (!InRange(bary.X(), 0.0f, 1.0f) || !InRange(bary.Y(), 0.0f, 1.0f) || !InRange(bary.Z(), 0.0f, 1.0f))continue;
			// ��ֵ�������
			float z = bary.X() * triangle[0].Z() + bary.Y() * triangle[1].Z() + bary.Z() * triangle[2].Z();
			// �ж��Ƿ�����Ļ�ڲ�
			if (!InRange(z, -1.0, 1.0f))continue;
			// ��Ȳ���
			int idx = (height - y) * width + x;
			if (zBuffer[idx] < z)continue;
			// ������Ȼ���
			zBuffer[idx] = z;
			// ��ֵ������ɫ
			Color color = bary.X() * pointColors[0] + bary.Y() * pointColors[1] + bary.Z() * pointColors[2];
			// ��ɫ
			SetPixel(x, y, color);
		}
	}
}

// MSAA
void Screen::RasterizeTriangleMSAA(Triangle& triangle, Color* pointColors)
{
	//std::cout << "In Screen!" << std::endl;
	//for (int i = 0; i < 3; ++i)std::cout << triangle[i] << std::endl;
	//std::cout << std::endl;
	// ���������ΰ�Χ��
	Vec2 bboxmin(INF, INF);
	Vec2 bboxmax(-INF, -INF);
	for (int i = 0; i < 3; ++i) {
		bboxmin.SetX(std::min(bboxmin.X(), triangle[i].X()));
		bboxmin.SetY(std::min(bboxmin.Y(), triangle[i].Y()));

		bboxmax.SetX(std::max(bboxmax.X(), triangle[i].X()));
		bboxmax.SetY(std::max(bboxmax.Y(), triangle[i].Y()));
	}
	//std::cout << "minx: " << bboxmin.X() << " miny: " << bboxmin.Y() << std::endl;
	//std::cout << "maxx: " << bboxmax.X() << " maxy: " << bboxmax.Y() << std::endl;
	// ƫ��������
	float offsetX[4] = { -0.25f, 0.25f, 0.25f, -0.25f };
	float offsetY[4] = { 0.25f, 0.25f, -0.25f, -0.25f };
	// ������Χ���е�ÿһ������
	for (int x = bboxmin.X(); x <= bboxmax.X(); ++x) {
		for (int y = bboxmin.Y(); y <= bboxmax.Y(); ++y) {
			// �ж��Ƿ�����Ļ�ڲ�
			if (!InRange(x, 0.0f, width) || !InRange(y, 0.0f, height))continue;
			// ��Ȳ���
			// ������������
			Vec3 bary = triangle.Barycentric(Vec2(x, y));
			float z = bary.X() * triangle[0].Z() + bary.Y() * triangle[1].Z() + bary.Z() * triangle[2].Z();
			// �ж��Ƿ�����Ļ�ڲ�
			if (!InRange(z, -1.0, 1.0f))continue;
			// ��ά����ת����һά���꣬ע�ⷴתy��
			int idx = (height - y) * width + x;
			if (z < zBuffer[idx])continue;
			// ����zBuffer
			zBuffer[idx] = z;

			// ���ز��������
			Color color(0.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < 4; ++i) {
				// ����ƫ�ƺ������
				float nx = static_cast<float>(x) + offsetX[i];
				float ny = static_cast<float>(y) + offsetY[i];
				// ������������
				Vec3 bary = triangle.Barycentric(Vec2(nx, ny));
				// �ж��Ƿ����������ڲ�
				if (!InRange(bary.X(), 0.0f, 1.0f) || !InRange(bary.Y(), 0.0f, 1.0f) || !InRange(bary.Z(), 0.0f, 1.0f))
					continue;
				// ��ֵ������ɫ
				Color sampleColor = bary.X() * pointColors[0] + bary.Y() * pointColors[1] + bary.Z() * pointColors[2];
				// �ۼ���color
				color = color + 0.25 * sampleColor;
			}
			if(color != Color(0.0f, 0.0f, 0.0f, 1.0f))SetPixel(x, y, color);
		}
	}
}

// ��դ�������Σ���ʽ���й��ռ���
void Screen::RasterizeTriangle(const Mat4& normalMatrix, Image* diffuseMap, Triangle& triangle, const Vec3& lightPos, const Vec3& viewPos)
{
	//for (int i = 0; i < 3; ++i)std::cout << triangle[i] << std::endl;
	// ���������ΰ�Χ��
	Vec2 bboxmin(INF, INF);
	Vec2 bboxmax(-INF, -INF);
	for (int i = 0; i < 3; ++i) {
		bboxmin.SetX(std::min(bboxmin.X(), triangle[i].X()));
		bboxmin.SetY(std::min(bboxmin.Y(), triangle[i].Y()));

		bboxmax.SetX(std::max(bboxmax.X(), triangle[i].X()));
		bboxmax.SetY(std::max(bboxmax.Y(), triangle[i].Y()));
	}

	for (int x = bboxmin.X(); x < bboxmax.X(); ++x) {
		for (int y = bboxmin.Y(); y < bboxmax.Y(); ++y) {
			// �ж��Ƿ�����Ļ�ڲ�
			if (!InRange(x, 0.0f, width) || !InRange(y, 0.0f, height))continue;
			// ������������
			Vec3 bary = triangle.Barycentric(Vec2(x, y));
			// �ж��Ƿ����������ڲ�
			if (!InRange(bary.X(), 0.0f, 1.0f) || !InRange(bary.Y(), 0.0f, 1.0f) || !InRange(bary.Z(), 0.0f, 1.0f))
				continue;
			// ��Ȳ���
			float z = bary.X() * triangle[0].Z() + bary.Y() * triangle[1].Z() + bary.Z() * triangle[2].Z();
			// �ж��Ƿ�����Ļ�ڲ�
			if (!InRange(z, -1.0, 1.0f))continue;
			int idx = (height - y) * width + x;
			if (z < zBuffer[idx])continue;
			// ����zBuffer
			zBuffer[idx] = z;
			// ���ռ���
			Color color = BlinPhong(normalMatrix, diffuseMap, triangle, bary, lightPos, viewPos);
			// ��ɫ
			SetPixel(x, y, color);
		}
	}
}

// �ж��������Ƿ�����Ļ��
bool Screen::InScreen(Triangle& triangle)
{
	for (int i = 0; i < 3; ++i) {
		if (!InRange(triangle[i][0], 0.0f, width))return false;
		if (!InRange(triangle[i][1], 0.0f, height))return false;
		if (!InRange(triangle[i][2], -depth, 0.0f))return false;
	}
	return true;
}

// ����ģ��
void Screen::RenderModel(const Mat4& m, const Mat4& mvp, Model& model, const Vec3& lightPos, const Vec3& viewPos)
{
	int nFaces = model.NumOfFaces();
	Image* diffuseMap = model.GetDiffuseMap();
	//std::cout << "RenderModel m: " << std::endl << m << std::endl;
	//std::cout << "RenderModel m.inverse: " << std::endl << m.Inverse() << std::endl;
	Mat4 normalMatrix = m.Inverse().Transpose();
	//std::cout << "RenderModel normalMatrix: " << std::endl << normalMatrix << std::endl;
	for (int i = 0; i < nFaces; ++i) {
		// ����������
		Vec4* points = new Vec4[3];
		Vec2* texCoords = new Vec2[3];
		Vec3* normals = new Vec3[3];
		for (int j = 0; j < 3; ++j) {
			Vec3 idx = model.Vertex(i, j);
			for (int k = 0; k < 3; ++k)points[j][k] = model.Vertex(idx[0])[k];
			points[j][3] = 1.0f;
			texCoords[j] = model.TexCoord(idx[1]);
			//std::cout << "RenderModel texCoords: " << std::endl;
			//std::cout << texCoords[j] << std::endl;
			normals[j] = model.Normal(idx[2]);
			//std::cout << "RenderModel normals: " << std::endl;
			//std::cout << normals[j] << std::endl;
		}
		Triangle triangle(points, texCoords, normals);
		triangle.CalcWorldPoints(m);
		
		// ����任
		triangle.Transform(mvp, width, height, depth);

		// ��դ��
		RasterizeTriangle(normalMatrix, diffuseMap, triangle, lightPos, viewPos);

		// �ͷ��ڴ�
		delete[] points;
		delete[] texCoords;
		delete[] normals;
	}
}

// ����ԭʼģ��
void Screen::RenderModel(Model& model)
{
	int nFaces = model.NumOfFaces();
	int nVertices = model.NumOfVertices();

	float xl = INF, xr = -INF, yl = INF, yr = -INF;
	for (int i = 0; i < nVertices; ++i) {
		xl = std::min(xl, model.Vertex(i)[0]);
		xr = std::max(xr, model.Vertex(i)[0]);
		yl = std::min(yl, model.Vertex(i)[1]);
		yr = std::max(yr, model.Vertex(i)[1]);
	}

	for (int i = 0; i < nFaces; ++i) {
		// ����������
		Vec4* points = new Vec4[3];
		Vec2* texCoords = new Vec2[3];
		for (int j = 0; j < 3; ++j) {
			Vec3 idx = model.Vertex(i, j);
			for (int k = 0; k < 3; ++k)points[j][k] = model.Vertex(idx[0])[k];
			points[j][3] = 1.0f;
			// ӳ������Ļ����
			points[j][0] = (points[j][0] - xl) / (xr - xl) * width;
			points[j][1] = (points[j][1] - yl) / (yr - yl) * height;
			texCoords[j] = model.TexCoord(idx[1]);
		}
		Triangle triangle(points, texCoords);

		// ��դ��
		Color* pointColors = new Color[3];
		for (int j = 0; j < 3; ++j) {
			pointColors[j] = model.GetDiffuseMap()->GetPixel(texCoords[j]);
		}
		RasterizeTriangle(triangle, pointColors);

		// �ͷ��ڴ�
		delete[] points;
		delete[] texCoords;
		delete[] pointColors;
	}
}

// ����zBuffer
void Screen::ClearZ()
{
	for (int i = 0; i < height * width; ++i)zBuffer[i] = -INF;
}