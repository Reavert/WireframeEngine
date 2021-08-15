#pragma once
#include <stdio.h>
#include <cstdint>

using namespace std;
struct SOM_Data
{
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;
	uint32_t two_sided;
	float sound_occlusion;
};

struct SOM_Info
{
	uint32_t version;
	uint32_t polygons_count;
	SOM_Data* polygon;

	void Serialize(const char* filename)
	{
		FILE* file;
		errno_t error = fopen_s(&file, filename, "wb");

		if (error == 0)
		{
			fwrite(&version, sizeof(version), 1, file);
			fwrite(&polygons_count, sizeof(polygons_count), 1, file);
			fwrite(polygon, sizeof(SOM_Data), polygons_count, file);

			fclose(file);
		}
	}
};

class SOMLoader
{
public:
	SOM_Info Load(const char* filename);
};

