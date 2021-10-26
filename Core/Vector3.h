#pragma once
#include <glew.h>
#include "IArray.h"

using namespace std;
class Vector3 : public IArray<GLfloat>
{
public:
	Vector3(void);
	Vector3(GLfloat x, GLfloat y, GLfloat z);
	vector<GLfloat> ToArray() override;

	Vector3 operator+(Vector3) const;
	Vector3 operator-(Vector3) const;
	Vector3 operator*(Vector3) const;
	Vector3 operator*(GLfloat) const;

	GLfloat x;
	GLfloat y;
	GLfloat z;
};

