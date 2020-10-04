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

	glm::vec3 axis = glm::cross(glm::vec3(0, 1, 0), linearVelocity);
	axis = glm::normalize(axis);
	orientation = glm::quat(parent->GetRotation());
	orientation = orientation + 0.5f * glm::quat(0, axis.x, axis.y, axis.z) * orientation * deltaTime_;
	parent->SetRotation(glm::normalize(glm::eulerAngles(orientation)));
	
	

}

void PhysicsComponent::SetVelocity(glm::vec3 velocity_)
{
	linearVelocity = velocity_;
}

void PhysicsComponent::SetAngularVelocity(glm::vec3 angularVelocity_)
{
	angularVelocity = angularVelocity_;
}


