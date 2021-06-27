#pragma once
#include <glew.h>
#include <stdio.h>
#include <string>
#define MAX_FILE_SIZE 8192

using namespace std;

class Utils
{
public:
	static void TraceGLError(string tag);
	static GLchar* LoadFile(const char* filename);
};

