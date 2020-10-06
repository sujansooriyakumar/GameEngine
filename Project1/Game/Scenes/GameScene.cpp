#include "GameScene.h"
GameScene::GameScene() : Scene()
{

}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate()
{
	
	
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(1.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSources(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f));

	CollisionHandler::GetInstance()->OnCreate(100.0f);
	Model* model = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model);
	Model* model1 = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);

	GameObject* dice = new GameObject(model1, glm::vec3(0.0f, 0.0f, 0.0f));
	dice->SetScale(glm::vec3(0.5f));
	SceneGraph::GetInstance()->AddGameObject(dice, "Die");
	
	GameObject* apple = new GameObject(model, glm::vec3(3.0f, 0.0f, 0.0f));
	apple->SetScale(glm::vec3(0.1f));
	apple->AddComponent<ComponentA>();
	apple->GetComponent<ComponentA>();
	apple->RemoveComponent<ComponentA>();
	apple->AddComponent<PhysicsComponent>();
	dice->AddComponent<PhysicsComponent>();
	apple->GetComponent<PhysicsComponent>()->SetVelocity(glm::vec3(-1, 0, 0));
	dice->GetComponent<PhysicsComponent>()->SetVelocity(glm::vec3(1 , 0, 0));
	apple->SetAngle(45);
	dice->SetAngle(-45);

	SceneGraph::GetInstance()->AddGameObject(apple, "Apple");

	gui = new GuiObject(glm::vec3(720, 360, 0.0f));
	gui->AddComponent<GuiImageComponent>();
	gui->GetComponent<GuiImageComponent>()->OnCreate("start", 1.0f, glm::vec4(1,1,1,1), 0.0f, glm::vec2(0,0));

	SceneGraph::GetInstance()->AddGuiObject(gui);
	
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	gui->FindContainingPoints();
	

}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void GameScene::Draw()
{
	SceneGraph::GetInstance()->Draw(CoreEngine::GetInstance()->GetCamera());
}
