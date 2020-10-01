#ifndef COMPONENETA_H
#define COMPONENETA_H

#include "../../Engine/Core/CoreEngine.h"


class ComponentA : public Component
{
public:
	ComponentA();
	virtual ~ComponentA();
	bool OnCreate(GameObject* parent_) override;
	void Update(float deltaTime_) override;
	
private:
};
#endif