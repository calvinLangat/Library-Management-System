#include "windowsAPI.h"

int file_Desc; // Definition
HANDLE hMapFile; // Definition

int createMemoryMap(const int* file_descriptor, char** mapview, HANDLE* hMapFile)
{
	// Get windows file handle from file descriptor
	HANDLE hFile = (HANDLE)_get_osfhandle(*file_descriptor);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Failed to get HANDLE from file descriptor (Error: %lu)\n", GetLastError());
		close(*file_descriptor);
		return 0;
	}

	// Create space in memory equal to the size of the file (rounded up to the nearest 4K bytes)
	hMapFile = CreateFileMappingA(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		0,
		NULL
	);
	if (hMapFile == NULL)
	{
		printf("Failed to create file mapping (Error: %lu)\n", GetLastError());
		close(*file_descriptor);
		return 0;
	}

	// Map View of file
	*mapview = (char*)MapViewOfFile(
		hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0
	);

	if (*mapview == NULL)
	{
		printf("Failed to map view of file (Error: %lu)\n", GetLastError());
		CloseHandle(hMapFile);
		close(*file_descriptor);
		return 0;
	}

	return 1;
}

int readFile(const char* file, char** out_fileContent, int* filesize)
{
	struct stat sb;
	if (stat(file, &sb))
	{
		printf_s("Error getting file info.\n");
		return 0;
	}

	*filesize = sb.st_size;			// Return file size

	// Open file and get file handle
	file_Desc = open(file, O_RDWR);
	if (file_Desc == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	//pMapView = NULL;
	hMapFile = INVALID_HANDLE_VALUE;

	if(!createMemoryMap(&file_Desc, out_fileContent, &hMapFile))
	{
		return 0;
	}

	return 1;
}

void freeResources(char* fileContents)
{
	CloseHandle(hMapFile);
	close(file_Desc);
	UnmapViewOfFile(fileContents);
}