#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "..//Core/CoreEngine.h"
#include <glm/gtc/quaternion.hpp>

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	bool OnCreate(GameObject* parent_) override;
	void Update(float deltaTime_) override;
	void SetVelocity(glm::vec3 velocity_);
	void SetAngularVelocity(glm::vec3 angularVelocity_);
private:
	glm::vec3 linearVelocity;
	glm::quat orientation;
	glm::vec3 angularVelocity;

};


#endif // !PHYSICSCOMPONENT
