// Syntic.cpp : Defines the entry point for the application.
//

#include "Syntic.h"

#ifdef _WINDOWS
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
	common->Init();
	renderer->Init();
	return 0;
}