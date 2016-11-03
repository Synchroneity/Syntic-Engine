#pragma once

#ifdef _DEBUG
#define BUILD_STR "dev"
#else
#define BUILD_STR "ship"
#endif

#define VERSION_STR "Syntic - "BUILD_STR

class synticCommon {
public:
	virtual						~synticCommon(void) {}
	virtual void				Init(int argc = 0, const char **argv = 0, const char *cmdline = 0) = 0;
	virtual void				Shutdown(void) = 0;
	virtual void				Quit(void) = 0;
	virtual bool				IsInitialized(void) const = 0;
	virtual void				Frame(void) = 0;

	virtual void				Printf(const char* fmt, ...) = 0;
};

extern synticCommon * common;