#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#ifndef WINDOWSAPI_H
#define WINDOWSAPI_H

#include <fcntl.h>
#include <sys/stat.h>

extern int file_Desc;
//extern char* pMapView;
extern HANDLE hMapFile;

int createMemoryMap(const int* file_descriptor, char** mapview, HANDLE* hMapFile);
int readFile(const char* file, char** out_fileContent, int* filesize);
void freeResources(char* fileContents);

#endif