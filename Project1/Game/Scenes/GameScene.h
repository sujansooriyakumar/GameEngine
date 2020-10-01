#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Graphics/TextureHandler.h"
#include "..//TesterClasses/ComponentA.h"
#include "../../Engine/Math/PhysicsComponent.h"

class GameScene : public Scene
{
public:
	GameScene();
	ComponentA a;
	virtual ~GameScene();
	virtual bool OnCreate();
	virtual void Render();

	virtual void Update(const float deltaTime_);
private:
};
#endif
