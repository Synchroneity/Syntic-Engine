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

void WriteSFTHeader(FILE * f, unsigned short count)
{
	fwrite((void *)SFMagic, sizeof(SFMagic), sizeof(char), f);
	fwrite((void *)&SFVersion, 1, sizeof(unsigned char), f);
	fwrite((void *)&count, 1, sizeof(count), f);
	//count = _byteswap_ushort(count);
}

void WriteSFTFileEntry(FILE * f, sftFileEntry_s ft)
{
	fwrite((void *)ft.name, sizeof(ft.name), 1, f);
	fwrite((void *)&ft.type, 1, sizeof(unsigned char), f);
	fwrite((void *)&ft.offset, 1, sizeof(unsigned long), f);
}

int main(int argc, char * argv[])
{
	printline("== Syntic Linker ==" << std:: endl);
	printline("using zlib version " << zlibVersion());
	char k;
	if (argc < 2) PrintUsage();

	unsigned short fileCount = argc - 1;
	char respath[512];
	char respatht[512];
	//sprintf_s(respath, "%s.sf", argv[i]);
	sprintf_s(respath, "%s.sf", "common");
	sprintf_s(respatht, "%s.sft", "common");
	FILE *out;
	FILE *outt;
	fopen_s(&out, respath, "wb");
	fopen_s(&outt, respatht, "wb");
	WriteSFTHeader(outt, fileCount);
	for (int i = 1; i < argc; i++)
	{
		sfFile_s f = ProcessFile(argv[i]);
		sftFileEntry_s ft;
		strcpy_s(ft.name, argv[i]);//strcat_s(ft.name, argv[i]);
		ft.offset = ftell(out);
		ft.type = ASSET_RAWFILE;
		WriteSFTFileEntry(outt, ft);
		if (f.processed)
		{
			printf("Writing to %s\n", respath);
			fwrite((void *)&f.uncompressedSize, 1, sizeof(f.uncompressedSize), out);
			fwrite((void *)&f.compressedSize, 1, sizeof(f.compressedSize), out);
			fwrite((void *)f.compressedFile, f.compressedSize, 1, out);
			
		}
	}
	fclose(out);
	fclose(outt);
	out = NULL;
	outt = NULL;


	return 0;
}

