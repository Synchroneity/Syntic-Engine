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
	virtual void				VPrintf(const char * fmt, va_list args);

	virtual void				Error(int level, const char* fmt, ...);

	virtual bool				WasErrorThrown();
	virtual const char*			GetErrorStr();

	virtual int					GetTicks(void);

	virtual double				GetDeltaTime(void);
	virtual double				GetFPS(void);

	unsigned int gameTicks = 0;
	bool errorThrown = false;
	char errstr[512];

	sTimer	g_timer;

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
#if defined(_WINDOWS)
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
	}
#endif
	common->Printf(VERSION_STR"\n");
	common->Printf("Starting...\n");
	common->Printf("=========== common->Init() ===========\n");

	bIsInitialized = true;
	common->Error(ERR_MINOR, "I am a random error that doesn't crash the game.\n");
	common->Error(ERR_MINOR, "Another one\n");
	common->Printf("Finished initializing common\n");
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
	g_timer.UpdateTime();
	gameTicks++;
}

void synticCommonLocal::Printf(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

void synticCommonLocal::VPrintf(const char * fmt, va_list args)
{
	vprintf(fmt, args);
}

void synticCommonLocal::Error(int level, const char * fmt, ...)
{
	common->Printf("ERROR: ");
	va_list args;
	va_start(args, fmt);
	common->VPrintf(fmt, args);
	vsprintf_s(errstr, fmt, args);
	va_end(args);
	if (level == ERR_FATAL)
	{
		errorThrown = true;
	}
}

bool synticCommonLocal::WasErrorThrown()
{
	return errorThrown;
}

const char * synticCommonLocal::GetErrorStr()
{
	return errstr;
}

int synticCommonLocal::GetTicks(void)
{
	return gameTicks;
}

double synticCommonLocal::GetDeltaTime(void)
{
	return g_timer.GetTimePassed();
}

double synticCommonLocal::GetFPS(void)
{
	return g_timer.GetFPS();
}
