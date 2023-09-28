#include "Color.h"
#include "Global.h"

// Ĭ�Ϲ��캯��
Color::Color()
{
	this->r = this->g = this->b = this->a = 0.0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(float r, float a)
{
	this->r = this->g = this->b = r;
	this->a = a;
}

// �������캯��
Color::Color(const Color& rhs)
{
	this->r = rhs.r;
	this->g = rhs.g;
	this->b = rhs.b;
	this->a = rhs.a;
}

Color::~Color()
{
}

float Color::R()const
{
	return r;
}
float Color::G()const
{
	return g;
}
float Color::B()const
{
	return b;
}
float Color::A()const
{
	return a;
}

Vec3 Color::RGB()const
{
	return *new Vec3(r, g, b);
}

void Color::SetR(float r)
{
	this->r = r;
}
void Color::SetG(float g)
{
	this->g = g;
}
void Color::SetB(float b)
{
	this->b = b;
}
void Color::SetA(float a)
{
	this->a = a;
}

// ��ֵ���������
Color& Color::operator=(const Color& rhs)
{
	r = rhs.r;
	g = rhs.g;
	b = rhs.b;
	a = rhs.a;
	return *this;
}

// �����ӷ�
Color operator+(const Color& a, const Color& b)
{
	return Color(a.R() + b.R(), a.G() + b.G(), a.B() + b.B(), a.A() + b.A());
}
// ��������
Color operator-(const Color& a, const Color& b)
{
	return Color(a.R() - b.R(), a.G() - b.G(), a.B() - b.B(), a.A() - b.A());
}
// ��������
Color operator*(float k, const Color& c)
{
	return Color(k * c.R(), k * c.G(), k * c.B(), k * c.A());
}
// ��������
Color operator/(const Color& c, float k)
{
	return Color(c.R() / k, c.G() / k, c.B() / k, c.A() / k);
}

bool operator==(const Color& a, const Color& b)
{
	return FloatEqual(a.R(), b.R()) && FloatEqual(a.G(), b.G()) && FloatEqual(a.B(), b.B());
}
bool operator!=(const Color& a, const Color& b)
{
	return !(a == b);
}
