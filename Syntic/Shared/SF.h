#pragma once
#include <iostream>
#include "syntic_AssetTypes.h"

typedef struct {
	bool processed;
	unsigned long compressedSize;
	unsigned long uncompressedSize; // a single file can be max 4GB... too much? lol
	char name[256];
	unsigned char type; //fit that shit in a byte
	unsigned char *compressedFile;
	unsigned char *uncompressedFile;
} sfFile_s;

typedef struct {
	unsigned short version;
	unsigned short fileCount;
} sfHeader_s;

typedef struct {
	sfHeader_s header;
	sfFile_s *files;
} sf_s;
