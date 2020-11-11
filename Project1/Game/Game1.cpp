#include "Game1.h"
Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr)
{

}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	
	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader",
		"Engine/Shaders/VertexShader.glsl",
		"Engine/Shaders/FragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("test", "Engine/Shaders/SpriteVertShader.glsl", "Engine/Shaders/SpriteFragShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("ParticleShader", "Engine/Shaders/ParticleVertexShader.glsl", "Engine/Shaders/ParticleFragShader.glsl");
	
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::FatalError("Engine's scene is not initialized to 0", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene())
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	currentScene->Render();
	Draw();
	SDL_GL_SwapWindow(CoreEngine::GetInstance()->GetWindow()->GetWindow());
	

}

void Game1::Draw()
{
	currentScene->Draw();
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default: 
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate())
	{
		CoreEngine::GetInstance()->Exit();
	}
}
