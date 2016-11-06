#include <zlib.h>
#include <iostream>
#define printline(x) std::cout << x << std::endl;
int main(int argc, char * argv[])
{
	printline("== Syntic Linker ==");
	printline("using zlib version " << zlibVersion());
    return 0;
}

