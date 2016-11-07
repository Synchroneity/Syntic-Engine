// SFInfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "../Shared/SF.h"

void PrintUsage()
{

}

void PrintAppInfo()
{

}

sftHeader_s ReadHeader(FILE * f)
{
	char magic[7];
	unsigned char version;
	unsigned short fileCount;
	fread(magic, 7, sizeof(char), f);
	//fseek(f, 6, SEEK_SET);
	fread(&version, 1, sizeof(unsigned char), f);
	fread(&fileCount, 1, sizeof(unsigned short), f);
	//fileCount = _byteswap_ushort(fileCount);
	std::cout << "Magic: " << magic << std::endl << "Version: " << (int)version << std::endl << "File Count: " << fileCount << std::endl;
	sftHeader_s header;
	memset(&header, 0, sizeof(header));
	header.fileCount = fileCount;
	strcpy_s(header.magic, SFMagic);
	header.version = version;
	return header;
}

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		PrintUsage();
		return 0;
	}
	for (int i = 0; i < argc - 1; i++)
	{
		FILE * f;
		FILE * ft;
		char sf[512];
		char sft[512];
		sprintf_s(sf, "%s.sf", argv[i+1]);
		sprintf_s(sft, "%s.sft", argv[i+1]);
		fopen_s(&ft, sft, "rb");
		if (ft == NULL)
		{
			std::cout << "ERROR WHILE OPENING STREAM FOR " << sft << std::endl;
			continue;
		}
		sftHeader_s header = ReadHeader(ft);
		fclose(ft);
		ft = NULL;
	}
    return 0;
}

