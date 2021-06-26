#include <string>
#include "WireframeObject.h"
#include <glew.h>

#pragma once

using namespace std;

struct Vertex
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

struct Face
{
	GLint vertexIndices[3];
};

struct ObjectInfo
{
	vector<Vertex> vertices;
	vector<Face> faces;
};
class ObjectLoader
{
public:
	ObjectInfo Load(const char* filename);
};

