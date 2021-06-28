#pragma once
#include <glew.h>
#include <vector>
#include "Vector4.h"

using namespace std;

struct Face
{
	GLint vertexIndices[3];
};

struct ObjectInfo
{
	vector<Vector4> vertices;
	vector<Face> faces;
};

