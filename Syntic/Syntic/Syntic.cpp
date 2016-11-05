// Syntic.cpp : Defines the entry point for the application.
//

#include "Syntic.h"

#if defined(_WINDOWS)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char * argv[])
#endif
{
#if defined(_WINDOWS)
	int argc = __argc;
	char ** argv = __argv; // hacky workaround for windows :D
#endif
	common->Init();
	renderer->Init(&argc, argv);
	common->Printf("Entering main game loop\n");
	while (renderer->ShouldClose() == 0 && !common->WasErrorThrown())
	{
		common->Frame();
		renderer->Render();
		common->Error(ERR_FATAL, "such a troublemaker");
	}

	if (common->WasErrorThrown())
	{
		MessageBox(NULL, common->GetErrorStr(), "ERROR", MB_OK);
	}
	return 0;
}