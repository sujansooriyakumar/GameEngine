#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <vector>
#include "GuiComponent.h"
#include <glm/glm.hpp>
#include "../../Camera/Camera.h"
#include <stdio.h>
#include <string>

class GuiObject {
public:
	GuiObject(glm::vec3 position_);
	~GuiObject();
	void Draw(Camera* camera);
	bool FindContainingPoints();
	void SetTag(std::string tag_);
	template<typename T> void AddComponent();
	template<typename T>  T* GetComponent();
	template<typename T> void RemoveComponent();
	
private:
	std::vector<GuiComponent*> guiComponents;
	glm::vec3 position;
	std::string tag;

};

template<typename T>
void GuiObject::AddComponent()
{
	T* t = new T;
	// verify that the game object is a child of the component class
	if (dynamic_cast<GuiComponent*>(t) == nullptr) {
		Debug::Error("not a component", "GuiObject.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}
	// if not write an error in the log file
	// then delete the object and stop the function

	//verify that the game object has no other component of that type
	// use getcomponent
	// if it returns nullptr, continue
	// else log error
	if (GetComponent<T>() != nullptr) {
		Debug::Error("duplicate component", "GuiObject.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}


	//if both checks pass
	// add component to vector and call oncreate of the component
	// pass this as the parent parameter

	guiComponents.push_back(t);
}

template<typename T>
T* GuiObject::GetComponent()
{
	for (auto m : guiComponents) {
		if (dynamic_cast<T*>(m) != nullptr) {
			return dynamic_cast<T*>(m);
		}
	}


	return nullptr;

}

template<typename T>
void GuiObject::RemoveComponent()
{

	for (int i = 0; i < guiComponents.size(); i++) {
		if (dynamic_cast<T*>(guiComponents.at(i)) != nullptr) {
			guiComponents.at(i) = nullptr;

			delete guiComponents.at(i);
			guiComponents.erase(guiComponents.begin() + i);

		}
	}
}

#endif