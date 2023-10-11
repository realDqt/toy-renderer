#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Image.h"
#include <vector>
class Model {
public:
	Model(const char* filePath);         // �����ļ�·������ģ��
	~Model(); 
	int NumOfVertices();                 // ������
	int NumOfFaces();                    // ����
	Vec3 Vertex(int idx);                // ����Ϊidx��λ������
	Vec3 Normal(int idx);                // ����Ϊidx�ķ�����
	Vec2 TexCoord(int idx);              // ����Ϊidx����������
	Vec3 Vertex(int iFace, int iVertex); // ��iFace����ĵ�iVertex������ĸ�����
	Image* GetDiffuseMap();              // ��ȡ��������ͼ
private:
	std::vector<Vec3> vertices;           // ����λ������       
	std::vector<Vec3> normals;            // ���㷨����
	std::vector<Vec2> texCoords;          // ������������
	std::vector<std::vector<Vec3>> faces; // ÿ�����ÿ�������λ�á�����ͷ��ߵ�����
	Image* diffuseMap;                    // ��������ͼ
};
