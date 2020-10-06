#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H
#include "..//..//Camera/Camera.h"
#include <string>
class GuiComponent {
public:
	inline GuiComponent() {}
	virtual ~GuiComponent() {}
	virtual void OnCreate(std::string name_, float scale_, glm::vec4 tint_, float angle_, glm::vec2 offset_) = 0;
	virtual void Draw(Camera* camera, glm::vec3 position_) = 0;
	virtual bool FindContainingPoint(glm::vec3 position_) = 0;
	

};


#endif