#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H
#include "..//..//Camera/Camera.h"
#include <string>
class GuiComponent {
public:
	inline GuiComponent() {}
	virtual ~GuiComponent() {}
	virtual void OnCreate(std::string name_) = 0;
	virtual void Draw(Camera* camera, glm::vec3 position_) = 0;
	virtual bool FindContainingPoint() = 0;
	

};


#endif