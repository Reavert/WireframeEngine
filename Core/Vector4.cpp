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