#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// �����ļ�·������ģ��
Model::Model(const char* filePath)
{
	std::ifstream in;
	// ���ļ�
	in.open(filePath, std::ifstream::in);
	// ����ʧ�ܣ��򷵻�
	if (in.fail())return;
	// �洢obj�ļ�ÿһ�е�����
	std::string line;
	while (!in.eof()) {
		// ��ȡ�ļ���һ��
		std::getline(in, line);
		// ��line��ʼ��iss����������Ķ�ȡ
		std::istringstream iss(line.c_str());
		// �洢�ļ��еĲ���Ҫ���ַ�
		char trash;
		if (!line.compare(0, 2, "v ")) {
			// ��ȡ�����λ������
			iss >> trash;
			Vec3 vertex;
			for (int i = 0; i < 3; ++i)iss >> vertex[i];
			vertices.push_back(vertex);
		}
		else if (!line.compare(0, 3, "vn ")) {
			// ��ȡ������
			iss >> trash >> trash;
			Vec3 normal;
			for (int i = 0; i < 3; ++i)iss >> normal[i];
			normals.push_back(normal);
		}
		else if (!line.compare(0, 3, "vt ")) {
			// ��ȡ��������
			iss >> trash >> trash;
			Vec2 texCoord;
			for (int i = 0; i < 2; ++i)iss >> texCoord[i];
			texCoords.push_back(texCoord);
		}
		else if (!line.compare(0, 2, "f ")) {
			// ��ȡ��ĸ�����������Ϣ
			iss >> trash;
			std::vector<Vec3> face;
			// ��������������
			for (int i = 0; i < 3; ++i) {
				Vec3 idx;
				iss >> idx[0] >> trash >> idx[1] >> trash >> idx[2];
				// ������1
				for (int j = 0; j < 3; ++j)idx[j]--;
				face.push_back(idx);
			}
			faces.push_back(face);
		}
	}
	// ����������ͼ
	diffuseMap = new Image("nothing");
	// debug
	std::cout << "NumOfVertices: " << vertices.size() << std::endl;
	std::cout << "NumOfTexCoords: " << texCoords.size() << std::endl;
	std::cout << "NumOfFaces: " << faces.size() << std::endl;
}

Model::~Model()
{
}

// ������
int Model::NumOfVertices()
{
	return vertices.size();
}

// ����
int Model::NumOfFaces()
{
	return faces.size();
}

// ����Ϊidx��λ������
Vec3 Model::Vertex(int idx)
{
	return vertices[idx];
}

// ����Ϊidx�ķ�����
Vec3 Model::Normal(int idx)
{
	return normals[idx];
}

// ����Ϊidx����������
Vec2 Model::TexCoord(int idx)
{
	return texCoords[idx];
}

// ��iFace����ĵ�iVertex������ĸ�����
Vec3 Model::Vertex(int iFace, int iVertex)
{
	return faces[iFace][iVertex];
}

// ��ȡ��������ͼ
Image* Model::GetDiffuseMap()
{
	return diffuseMap;
}