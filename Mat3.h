#pragma once
#include<vector>
class Mat3 {
public:
	Mat3();                // Ĭ�Ϲ��캯��
	Mat3(const Mat3& rhs); // �������캯��
	Mat3(float value);
	~Mat3();
	Mat3& operator= (const Mat3& rhs);
	std::vector<float>& operator[](int idx);
	const std::vector<float>& operator[](int idx)const;
	Mat3 Transpose()const;
	Mat3 Inverse()const;
	float Det()const;
private:
	std::vector<float> data[3];
};

Mat3 operator*(const Mat3& a, const Mat3& b); // ����˷�
Mat3 operator+(const Mat3& a, const Mat3& b); // ����ӷ�
Mat3 operator*(float k, const Mat3& M);       // ��������
Mat3 operator/(const Mat3& M, float k);       // ��������

