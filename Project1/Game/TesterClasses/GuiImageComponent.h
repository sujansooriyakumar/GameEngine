#ifndef GUIIMAGECOMPONENT_H
#define GUIIMAGECOMPONENT_H

#include "../..//Engine/Rendering/2D/GuiComponent.h"
#include "../..//Engine/Events/MouseEventListener.h"
#include <string>
#include <glm/glm.hpp>
#include "../../Engine/Camera/Camera.h"
#include "../..//Engine/Rendering/2D/SpriteSurface.h"

class GuiImageComponent : public GuiComponent {
public:
	GuiImageComponent();
	virtual ~GuiImageComponent();
	void OnCreate(std::string name_, float scale_, glm::vec4 tint_, float angle_, glm::vec2 offset_) override;
	void Draw(Camera* camera_, glm::vec3 position_) override;
	bool FindContainingPoint(glm::vec3 position_) override;

private:
	SpriteSurface* sprite;
	glm::vec2 offset;
	float scale;
	float angle;
	glm::vec4 tint;
	
};
#endif