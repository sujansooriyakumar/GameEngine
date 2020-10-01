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
	//dice->AddComponent<PhysicsComponent>();
	//dice->GetComponent<PhysicsComponent>()->SetVelocity(glm::vec3(0.5f, 0, 0));
	GameObject* apple = new GameObject(model, glm::vec3(3.0f, 0.0f, 0.0f));
	apple->SetScale(glm::vec3(0.1f));
	apple->AddComponent<PhysicsComponent>();
	apple->GetComponent<PhysicsComponent>()->SetVelocity(glm::vec3(-0.5f, 0, 0));
	apple->GetComponent<PhysicsComponent>()->SetAngularVelocity(glm::vec3(0, 45.0f, 0));
	apple->RemoveComponent<PhysicsComponent>();
	//dice->GetComponent<PhysicsComponent>()->SetAngularVelocity(glm::vec3(0, 45.0f, 0));
	apple->SetAngle(45);
	dice->SetAngle(-45);
	SceneGraph::GetInstance()->AddGameObject(apple, "Apple");
	
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	

}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
