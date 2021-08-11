#pragma once
#include <glew.h>
#include "IArray.h"

using namespace std;
class Vector3 : public IArray<GLfloat>
{
public:
	Vector3(void);
	Vector3(GLfloat x, GLfloat y, GLfloat z);
	virtual vector<GLfloat> ToArray();

	GLfloat x;
	GLfloat y;
	GLfloat z;
};

