#include "../Syntic.h"

class synticCommonLocal : public synticCommon {
public:
	synticCommonLocal(void);

	virtual void				Init(int argc, const char **argv, const char *cmdline);
	virtual void				Shutdown(void);
	virtual void				Quit(void);
	virtual bool				IsInitialized(void) const;
	virtual void				Frame(void);
	
	virtual void				Printf(const char* fmt, ...);

private:
	bool bIsInitialized = false;
};

synticCommonLocal	commonLocal;
synticCommon * common = &commonLocal;

synticCommonLocal::synticCommonLocal(void)
{
}

void synticCommonLocal::Init(int argc, const char ** argv, const char * cmdline)
{
	bIsInitialized = true;
}

void synticCommonLocal::Shutdown(void)
{
}

void synticCommonLocal::Quit(void)
{
}

bool synticCommonLocal::IsInitialized(void) const
{
	return bIsInitialized;
}

void synticCommonLocal::Frame(void)
{
}

void synticCommonLocal::Printf(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}
