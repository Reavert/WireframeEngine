#pragma once
#include <glew.h>
#include "IArray.h"

using namespace std;
class Vector4 : public IArray<GLfloat>
{
public:
	Vector4(void);
	Vector4(GLfloat x, GLfloat y, GLfloat z);
	Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;

	virtual vector<GLfloat> ToArray(void);
};

