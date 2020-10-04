#ifndef GUIIMAGECOMPONENT_H
#define GUIIMAGECOMPONENT_H

#include "../..//Engine/Rendering/2D/GuiComponent.h"
#include <string>
#include <glm/glm.hpp>
#include "../../Engine/Camera/Camera.h"
#include "../..//Engine/Rendering/2D/SpriteSurface.h"

class GuiImageComponent : public GuiComponent {
public:
	GuiImageComponent();
	virtual ~GuiImageComponent();
	void OnCreate(std::string name_) override;
	void Draw(Camera* camera_, glm::vec3 position_) override;
	bool FindContainingPoint() override;

private:
	SpriteSurface* sprite;
	glm::vec2 offset;
	float scale;
	float angle;
	glm::vec4 tint;
	
};
#endif