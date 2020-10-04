#include "GuiImageComponent.h"

GuiImageComponent::GuiImageComponent()
{
	
}

GuiImageComponent::~GuiImageComponent()
{
	delete sprite;
	sprite = nullptr;
}

void GuiImageComponent::OnCreate(std::string name_)
{
	offset = glm::vec2(0,0);
	scale = 1.0f;
	angle = 0.0f;
	tint = glm::vec4(1, 1, 1, 1);
	sprite = new SpriteSurface(name_, glm::vec2(scale, scale), angle, tint);

}

void GuiImageComponent::Draw(Camera* camera_, glm::vec3 position_)
{
	sprite->Draw(camera_, position_);
}

bool GuiImageComponent::FindContainingPoint()
{
	return false;
}
