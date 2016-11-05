#pragma once
#include "../Syntic.h"

class synticRenderer {
public:
	virtual						~synticRenderer(void) {}
	virtual	void				Init(int *argc, char* argv[], int w = 640, int h = 480) = 0;
	virtual void				Shutdown(void) = 0;

	virtual void				Render(void) = 0;
	virtual void				Resize(void) = 0;

	virtual bool				ShouldClose(void) = 0;

};


extern synticRenderer * renderer;