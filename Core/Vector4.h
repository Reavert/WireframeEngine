#pragma once
#include <glew.h>
#include <vector>
using namespace std;
class Vector4
{
public:
	Vector4(void);
	Vector4(GLfloat x, GLfloat y, GLfloat z);
	Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;

	vector<GLfloat> ToArray(void);
};

