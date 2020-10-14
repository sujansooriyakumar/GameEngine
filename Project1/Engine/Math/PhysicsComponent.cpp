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
	
	glm::quat q = glm::quat(0, 0, 0, 1);
	glm::vec3 v = glm::vec3(0, 2, 0);
	q = q + 0.5f * glm::quat(0, 0, 2, 0) * q;
	q = glm::normalize(q);
	orientation = glm::quat(parent->GetRotation());
	orientation = orientation +  glm::quat(0, 0.785398f, 0, 0) * (deltaTime_/2);
	orientation = glm::normalize(orientation);
	std::cout << q.x << " " << q.y << " " << q.z << " " << q.w << std::endl;
	parent->SetRotation(glm::vec3(orientation.x, orientation.y, orientation.z));
	parent->SetAngle(orientation.w);
	
	

}

void PhysicsComponent::SetVelocity(glm::vec3 velocity_)
{
	linearVelocity = velocity_;
}

void PhysicsComponent::SetAngularVelocity(glm::vec3 angularVelocity_)
{
	angularVelocity = angularVelocity_;
}


