#include "GuiImageComponent.h"

GuiImageComponent::GuiImageComponent()
{
	
}

GuiImageComponent::~GuiImageComponent()
{
	delete sprite;
	sprite = nullptr;
}

void GuiImageComponent::OnCreate(std::string name_, float scale_, glm::vec4 tint_, float angle_, glm::vec2 offset_)
{
	offset = offset_;
	scale = scale_;
	angle = angle_;
	tint = tint_;
	sprite = new SpriteSurface(name_, glm::vec2(scale, scale), angle, tint);

}

void GuiImageComponent::Draw(Camera* camera_, glm::vec3 position_)
{
	sprite->Draw(camera_, position_ + glm::vec3(offset, 0));
}

bool GuiImageComponent::FindContainingPoint(glm::vec3 position_)
{
	//std::cout << MouseEventListener::GetMousePosition().x << " " << MouseEventListener::GetMousePosition().y << std::endl;
	glm::vec2 mousePos = MouseEventListener::GetMousePosition();
	if (mousePos.x >= position_.x - sprite->GetWidth() * scale /2  && mousePos.x <= position_.x + (sprite->GetWidth() * scale/2)
		&& mousePos.y >= position_.y - sprite->GetHeight() * scale / 2 && mousePos.y <= position_.y + (sprite->GetHeight() * scale/2)) {
		sprite->SetTint(glm::vec4(0.3, 0.4f, 0.4, 1.0));
		return true;
	}
	sprite->SetTint(glm::vec4(1.0, 1.0, 1.0, 1.0));


	return false;
}
