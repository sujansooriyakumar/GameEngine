#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {
	
	CoreEngine::GetInstance()->SetGameInterface(new Game1, Renderer::RendererType::OpenGL);
	if (!CoreEngine::GetInstance()->OnCreate("Game 258 Engine", 1280, 720)) {
		std::cout << "Engine failed to be created" << std::endl;
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;


}