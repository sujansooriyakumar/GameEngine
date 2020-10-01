#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
	parent = nullptr;
}

PhysicsComponent::~PhysicsComponent()
{
	delete &linearVelocity;
}

bool PhysicsComponent::OnCreate(GameObject* parent_)
{
	parent = parent_;
	linearVelocity = glm::vec3(0, 0, 0);
	orientation = glm::quat(parent->GetRotation());
	angularVelocity = glm::vec3(0, 45, 0);
	return true;
	
}

void PhysicsComponent::Update(float deltaTime_)
{
	parent->SetPosition(parent->GetPosition() + linearVelocity * deltaTime_);
	/*
	glm::vec3 axis = glm::cross(glm::vec3(0, 1, 0), linearVelocity);
	axis = glm::normalize(axis);
	glm::vec3 angularVel = axis * glm::length(linearVelocity);
	parent->SetRotation(parent->GetRotation() + (0.5f * angularVel * parent->GetRotation() * deltaTime_));
	*/

	glm::vec3 result = glm::eulerAngles(orientation + (orientation * 0.5f * deltaTime_ * glm::quat(angularVelocity)));
	
	parent->SetRotation(result);
	std::cout << parent->GetRotation().x << parent->GetRotation().y << parent->GetRotation().z << std::endl;


}

void PhysicsComponent::SetVelocity(glm::vec3 velocity_)
{
	linearVelocity = velocity_;
}

void PhysicsComponent::SetAngularVelocity(glm::vec3 angularVelocity_)
{
	angularVelocity = angularVelocity_;
}


