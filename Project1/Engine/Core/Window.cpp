#include "Window.h"
Window::Window()
{

}
Window::~Window()
{

}

bool Window::OnCreate(std::string name_, int width_, int height_, Renderer* renderer_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Debug::FatalError("SDL_INIT_VIDEO Failed", "Window.cpp ", __LINE__);
		return false;
	}
	width = width_;
	height = height_;


	window = renderer_->CreateWindow(name_, width, height);
	if (!window)
	{
		Debug::Error("Failed to create window", "Window.cpp ", __LINE__);
		return false;
	}


	

	return true;
}

void Window::OnDestroy()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}