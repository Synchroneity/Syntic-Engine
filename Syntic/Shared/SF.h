#pragma once
#include <iostream>
#include "syntic_AssetTypes.h"

const unsigned char SFVersion = 1;
const char SFMagic[] = "SynSFT";

typedef struct {
	bool processed;	// used only in linker
	unsigned long compressedSize;
	unsigned long uncompressedSize; // a single file can be max 4GB... too much? lol
	unsigned char *compressedFile;
	unsigned char *uncompressedFile; // used only in linker
} sfFile_s;

typedef struct {
	char magic[sizeof(SFMagic)];     // SynSFT
	unsigned char version;
	unsigned short fileCount;
} sftHeader_s;

typedef struct {
	char name[256];
	unsigned char type; //fit that shit in a byte
	unsigned long offset;
} sftFileEntry_s;

typedef struct {
	sftHeader_s header;
	sftFileEntry_s *entries;
} sft_s;
