#include "SOMLoader.h"

SOM_Info SOMLoader::Load(const char* filename)
{
	FILE* file;
	errno_t error = fopen_s(&file, filename, "rb");
	SOM_Info somInfo = SOM_Info();

	if (error == 0)
	{
		fread_s(&somInfo.version, sizeof(somInfo.version), sizeof(somInfo.version), 1, file);
		fread_s(&somInfo.polygons_count, sizeof(somInfo.polygons_count), sizeof(somInfo.polygons_count), 1, file);
		somInfo.polygon = new SOM_Data[somInfo.polygons_count];

		fread_s(somInfo.polygon, somInfo.polygons_count * sizeof(SOM_Data), sizeof(SOM_Data), somInfo.polygons_count, file);
		fclose(file);
	}
	else
	{
		printf("Error when loading file '%s'\n", filename);
	}
	return somInfo;
}