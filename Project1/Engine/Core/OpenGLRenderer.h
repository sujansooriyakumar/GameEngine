#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include "Renderer.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Debug.h"

class OpenGLRenderer : public Renderer {
public:
	OpenGLRenderer();
	~OpenGLRenderer();
	SDL_Window* CreateWindow(std::string name_, int width_, int height_) override;
	void SetPreAttributes();
	void SetPostAttributes();
	void init() override;
	void run() override;
	SDL_GLContext context;
};

#endif // !OPENGLRENDERER_H