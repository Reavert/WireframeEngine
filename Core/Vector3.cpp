#include "Vector3.h"

Vector3::Vector3() : Vector3(0.0f, 0.0f, 0.0f) { }

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z) 
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vector<GLfloat> Vector3::ToArray()
{
	vector<GLfloat> v = { x, y, z };
	return v;
}

Vector3 Vector3::operator+(const Vector3 rhs) const
{
	return Vector3(
		this->x + rhs.x,
		this->y + rhs.y,
		this->z + rhs.z
	);
}

Vector3 Vector3::operator-(const Vector3 rhs) const
{
	return Vector3(
		this->x - rhs.x,
		this->y - rhs.y,
		this->z - rhs.z
	);
}

Vector3 Vector3::operator*(const Vector3 rhs) const
{
	return Vector3(
		this->x * rhs.x,
		this->y * rhs.y,
		this->z * rhs.z
	);
}

Vector3 Vector3::operator*(const GLfloat rhs) const
{
	return Vector3(
		this->x * rhs,
		this->y * rhs,
		this->z * rhs
	);
}
