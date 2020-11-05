#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "3D/GameObject.h"
#include "..//Graphics/ShaderHandler.h"
#include "2D/GuiObject.h"
#include "../Math/CollisionHandler.h"
#include "3D/OpenGLMesh.h"
class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator = (const SceneGraph&) = delete;
	SceneGraph& operator = (SceneGraph&&) = delete;

	static SceneGraph* GetInstance();
	void OnDestroy();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, std::string tag_ = "");
	void AddGuiObject(GuiObject* guiObj_, std::string tag_ = "");
	GuiObject* GetGuiObject(std::string tag_);
	GameObject* GetGameObject(std::string tag_);

	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void Draw(Camera* camera_);
private:
	SceneGraph();
	~SceneGraph();

	friend std::default_delete<SceneGraph>;
	static std::unique_ptr<SceneGraph> sceneGraphInstance;


	static std::map<std::string, GameObject*> sceneGameObjects;
	static std::map<std::string, GuiObject*> sceneGuiObjects;
	static std::map<GLuint, std::vector<Model*>> sceneModels;
};
#endif
