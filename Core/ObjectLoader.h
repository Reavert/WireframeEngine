#pragma once

#include <string>
#include "ObjectInfo.h"
#include <glew.h>
#include "Vector4.h"

using namespace std;

class ObjectLoader
{
public:
	ObjectInfo Load(const char* filename);
};

