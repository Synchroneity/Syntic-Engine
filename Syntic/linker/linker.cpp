#include <zlib.h>
#include <iostream>

#include "../Shared/SF.h"
#define printline(x) std::cout << x << std::endl;


sfFile_s ProcessFile(char path[])
{
	FILE *in;
	sfFile_s out;
	memset(&out, 0, sizeof(out));
	out.processed = false;
	fopen_s(&in, path, "rb");
	if (in == NULL)
	{
		printline("ERROR: Couldn't find file!\n      Path:" << path);
		return out;
	}
	fseek(in, 0, SEEK_END);
	out.uncompressedSize = ftell(in);
	rewind(in);
	out.uncompressedFile = (unsigned char *)malloc(out.uncompressedSize);
	fread(out.uncompressedFile, out.uncompressedSize, 1, in);
	fclose(in);
	in = NULL;
	uLongf compressedBufferSize = (out.uncompressedSize * 1.01) + 12;
	out.compressedFile = (unsigned char*)malloc(compressedBufferSize);
	printline("Compressing " << path);
	int z_result = compress(out.compressedFile, &compressedBufferSize, out.uncompressedFile, out.uncompressedSize);
	out.compressedSize = compressedBufferSize;
	switch (z_result)
	{
	case Z_OK:
		break;

	case Z_MEM_ERROR:
		printf("out of memory\n");
		exit(1);   // quit.
		break;
	case Z_BUF_ERROR:
		printf("output buffer wasn't large enough!\n");
		exit(1);    // quit.
		break;
	default:
		printf("unknown exception\nError code: %d\n", z_result);
		exit(1);
		break;
	}
	out.processed = true;
	return out;
}

void PrintUsage()
{
	printline("test");
}

int main(int argc, char * argv[])
{
	printline("== Syntic Linker ==" << std:: endl);
	printline("using zlib version " << zlibVersion());
	char k;
	if (argc < 2) PrintUsage();
	for (int i = 1; i < argc; i++)
	{
		sfFile_s f = ProcessFile(argv[i]);
		if(f.processed)
		{
			char respath[512];
			sprintf_s(respath, "%s.sf", argv[i]);
			printf("Writing to %s\n", respath);
			FILE *out;
			fopen_s(&out, respath, "wb");
			fwrite((void *)&f.uncompressedSize, 1, sizeof(f.uncompressedSize), out);
			fwrite((void *)&f.compressedSize, 1, sizeof(f.compressedSize), out);
			fwrite((void *)f.compressedFile, f.compressedSize, 1, out);
			fclose(out);
			out = NULL;
			FILE *in;
			fopen_s(&in, respath, "rb");
			unsigned long size = 0;
			unsigned long csize = 0;
			fread((void *)&size, 1, sizeof(unsigned long), in);
			fread((void *)&csize, 1, sizeof(unsigned long), in);
			printline("Size: " << size << std::endl << "CSize: " << csize);
			unsigned char *cmpdata = new unsigned char[csize];
			fread((void *)cmpdata, sizeof(unsigned char), csize, in);
			char *uc = new char[size];
			uncompress((Bytef *)uc, &size, cmpdata, csize);
			std::cout << uc;
			std::cin >> k;
		}
	}

    return 0;
}

