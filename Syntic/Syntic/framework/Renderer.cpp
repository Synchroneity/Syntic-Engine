#include "../Syntic.h"
class synticRendererLocal : public synticRenderer {
public:
	synticRendererLocal(void);

	virtual void				Init(int* argc, char* argv[], int w = 640, int h = 480);
	virtual void				Shutdown(void);

	virtual void				Render(void);
	virtual void				Resize(void);

	virtual bool				ShouldClose(void);

	bool bIsInitialized = false;
	renderSettings_s			renderSettings;

	GLFWwindow* window;
};
synticRendererLocal	rendererLocal;
synticRenderer * renderer = &rendererLocal;

synticRendererLocal::synticRendererLocal(void)
{
}

void synticRendererLocal::Init(int *argc, char* argv[], int w, int h)
{
	common->Printf("=========== renderer->Init() ===========\n");
	renderSettings.height = h;
	renderSettings.width = w;
	renderSettings.renderer = RENDERER_OPENGL;

	if (!glfwInit())
	{
		common->Error(ERR_FATAL, "Couldn't initialize GLFW\n");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	window = glfwCreateWindow(640, 480, VERSION_STR, NULL, NULL);
	if (window == NULL) {
		common->Error(ERR_FATAL, "Failed to open GLFW window\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	//glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		common->Error(ERR_FATAL, "Failed to initialize GLEW\n");
		return;
	}
	common->Printf("Renderer initialized!\n");

}

void synticRendererLocal::Shutdown(void)
{
}

void synticRendererLocal::Render(void)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void synticRendererLocal::Resize(void)
{
	int width = renderSettings.width;
	int height = renderSettings.height;

}

bool synticRendererLocal::ShouldClose(void)
{
	return (glfwWindowShouldClose(window) > 0);
}
