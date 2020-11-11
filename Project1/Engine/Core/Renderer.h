#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <SDL.h>

class Renderer
{
public:
	enum  RendererType
	{
		OpenGL,
		Vulkan
	};
	Renderer() {
		window = nullptr;
	}
	virtual ~Renderer() {}
	virtual SDL_Window* CreateWindow(std::string name_, int width_, int height_) {
		window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_HIDDEN);
		return window;
	}
	virtual void init() = 0;
	virtual void run() = 0;
	SDL_Window* window;
};

#endif