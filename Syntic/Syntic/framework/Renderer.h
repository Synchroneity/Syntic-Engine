#pragma once

class synticRenderer {
public:
	virtual						~synticRenderer(void) {}
	virtual	void				Init(int w = 640, int h = 480) = 0;
	virtual void				Shutdown(void) = 0;
};

extern synticRenderer * renderer;