#include "../Syntic.h"
class synticRendererLocal : public synticRenderer {
public:
	synticRendererLocal(void);

	virtual void				Init(int w = 640, int h = 480);
	virtual void				Shutdown(void);

	bool bIsInitialized = false;
};
synticRendererLocal	rendererLocal;
synticRenderer * renderer = &rendererLocal;

synticRendererLocal::synticRendererLocal(void)
{
}

void synticRendererLocal::Init(int w, int h)
{
}

void synticRendererLocal::Shutdown(void)
{
}
