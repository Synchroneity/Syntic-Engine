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
		common->Printf("Delta Time: %f\nTick: %d\nFPS: %d\n", common->GetDeltaTime(), common->GetTicks(), (int)common->GetFPS());
		if(common->GetTicks() > 120)
			common->Error(ERR_FATAL, "I'm such a troublemaker. I crashed the game because it ran for more than 15 ticks :D\n");
	}

	if (common->WasErrorThrown())
	{
		MessageBox(NULL, common->GetErrorStr(), "ERROR", MB_OK);
	}
	return 0;
}