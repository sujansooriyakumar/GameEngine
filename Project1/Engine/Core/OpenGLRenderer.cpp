#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer()
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

SDL_Window* OpenGLRenderer::CreateWindow(std::string name_, int width_, int height_)
{
	SDL_Window* window;
	SetPreAttributes();
	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_OPENGL);
	if (!window)
	{
		Debug::Error("Failed to create window", "Window.cpp ", __LINE__);
		return nullptr;
	}

	context = SDL_GL_CreateContext(window);
	SetPostAttributes();
	GLenum error = glewInit();


	if (error != GLEW_OK)
	{
		Debug::FatalError("GLEW Failed", "Window.cpp ", __LINE__);
		return false;
	}


	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width_, height_);

	std::cout << "Graphics card: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	return window;
}

void OpenGLRenderer::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
}

void OpenGLRenderer::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

}

void OpenGLRenderer::init()
{
}

void OpenGLRenderer::run()
{
}
