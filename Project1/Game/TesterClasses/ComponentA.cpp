#include "ComponentA.h"

ComponentA::ComponentA() : Component()
{
}



 ComponentA::~ComponentA()
{
}

bool ComponentA::OnCreate(GameObject* parent_)
{
	parent = parent_;
	std::cout << "component a added" << std::endl;
	return true;

}


void ComponentA::Update(float deltaTime_)
{
	parent->SetPosition(parent->GetPosition() - glm::vec3(0.01f, 0.0f, 0.0f));
	std::cout << "component a updating" << std::endl;

}
