#include "Vector4.h"

Vector4::Vector4() : Vector4(0.0f, 0.0f, 0.0f) { }

Vector4::Vector4(GLfloat x, GLfloat y, GLfloat z) : Vector4(x, y, z, 1.0f) { }

Vector4::Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vector<GLfloat> Vector4::ToArray()
{
	vector<GLfloat> v = { x, y, z, w };
	return v;
}

Vector4 Vector4::operator+(Vector4 rhs)
{
	return Vector4(
		this->x + rhs.x,
		this->y + rhs.y,
		this->z + rhs.z,
		this->w + rhs.w
	);
}

Vector4 Vector4::operator-(Vector4 rhs)
{
	return Vector4(
		this->x - rhs.x,
		this->y - rhs.y,
		this->z - rhs.z,
		this->w - rhs.w
	);
}

Vector4 Vector4::operator*(Vector4 rhs)
{
	return Vector4(
		this->x * rhs.x,
		this->y * rhs.y,
		this->z * rhs.z,
		this->w * rhs.w
	);
}

Vector4 Vector4::operator*(GLfloat rhs)
{
	return Vector4(
		this->x * rhs,
		this->y * rhs,
		this->z * rhs,
		this->w * rhs
	);
}