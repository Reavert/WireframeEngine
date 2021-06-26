#include <glew.h>
#include <stdio.h>
#include <string>

#define MAX_FILE_SIZE 5012

using namespace std;
#pragma once
class Utils
{
public:
	static void TraceGLError(string tag);
	static GLchar* LoadFile(const char* filename);
};

