#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Core/Component.h"
#include "..//..//Audio/AudioSource.h"



class GameObject {
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void Render(Camera* camera_);
	void Update(const float deltaTime_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetScale() const;
	glm::vec3 GetRotation() const;
	BoundingBox GetBoundingBox();
	std::string GetTag() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	template<typename T, typename ... Args> void AddComponent(Args&&... param_);
	template<typename T>  T* GetComponent();
	template<typename T> void RemoveComponent();
private:
	Model* model;
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	int modelInstance;

	BoundingBox box;
	std::vector<Component*> components;

	std::string tag;
	bool hit;
};

template<typename T, typename ... Args>
void GameObject::AddComponent(Args&& ... param_)
{
	T* t = new T(std::forward<Args>(param_)...);
	// verify that the game object is a child of the component class
	if (dynamic_cast<Component*>(t) == nullptr) {
		Debug::Error("not a component", "GameObject.cpp", __LINE__);
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
		Debug::Error("duplicate component", "GameObject.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}

	
	//if both checks pass
	// add component to vector and call oncreate of the component
	// pass this as the parent parameter

	components.push_back(t);
	components.back()->OnCreate(this);
}

template<typename T>
 T* GameObject::GetComponent()
{
	 for (auto m : components) {
		 if (dynamic_cast<T*>(m) != nullptr) {
			 return dynamic_cast<T*>(m);
		 }
	 }
	

	return nullptr;
	
}

template<typename T>
void GameObject::RemoveComponent()
{

	for (int i = 0; i < components.size(); i++) {
		if (dynamic_cast<T*>(components.at(i)) != nullptr) {

			delete components.at(i);
			components.at(i) = nullptr;

			components.erase(components.begin() + i);

		}
	}
}

#endif


