#pragma once

#ifdef _DEBUG
#define BUILD_STR "dev"
#else
#define BUILD_STR "ship"
#endif

#define VERSION_STR "Syntic - "##BUILD_STR

typedef enum {
	ERR_MINOR,
	ERR_FATAL
};

class synticCommon {
public:
	virtual						~synticCommon(void) {}
	virtual void				Init(int argc = 0, const char **argv = 0, const char *cmdline = 0) = 0;
	virtual void				Shutdown(void) = 0;
	virtual void				Quit(void) = 0;
	virtual bool				IsInitialized(void) const = 0;
	virtual void				Frame(void) = 0;

	virtual void				Printf(const char* fmt, ...) = 0;
	virtual void				VPrintf(const char * fmt, va_list args) = 0;

	virtual void				Error(int level, const char* fmt, ...) = 0;

	virtual bool				WasErrorThrown() = 0;
	virtual const char*			GetErrorStr() = 0;

	virtual int					GetTicks(void) = 0;

	//int gameTicks = 0;
};

extern synticCommon * common;