#ifndef WINDOWS_H
#define WINDOWS_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Debug.h"

class Window
{
public:
	Window();
	~Window();
	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();

	int GetWidth();
	int GetHeight();
	SDL_Window* GetWindow() const;
private:

	void SetPreAttributes();
	void SetPostAttributes();
	int width, height;
	SDL_Window* window;
	SDL_GLContext context;
};
#endif