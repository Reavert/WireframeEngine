#include "Vector3.h"

Vector3::Vector3() : Vector3(0.0f, 0.0f, 0.0f) { }

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}