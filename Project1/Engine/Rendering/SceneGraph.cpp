#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<std::string, GuiObject*> SceneGraph::sceneGuiObjects = std::map<std::string, GuiObject*>();


SceneGraph::SceneGraph()
{

}

SceneGraph::~SceneGraph()
{

}

SceneGraph* SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr)
	{
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0)
	{
		for (auto go : sceneGameObjects)
		{
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0)
	{
		for (auto entry : sceneModels)
		{
			if (entry.second.size() > 0)
			{
				for (auto m : entry.second)
				{
					delete m;

					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_)
{
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end())
	{

		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp));
	}
	else
	{
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* go_, std::string tag_)
{
	if (tag_ == "")
	{
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end())
	{
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;
	}
	else
	{
		Debug::Error("Trying to add a GameObject with a tag " + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);
}

void SceneGraph::AddGuiObject(GuiObject* guiObj_, std::string tag_)
{
	if (tag_ == "")
	{
		std::string newTag = "GuiObjeect" + std::to_string(sceneGameObjects.size() + 1);
		guiObj_->SetTag(newTag);
		sceneGuiObjects[newTag] = guiObj_;
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end())
	{
		guiObj_->SetTag(tag_);
		sceneGuiObjects[tag_] = guiObj_;
	}
	else
	{
		Debug::Error("Trying to add a GuiObject with a tag " + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GuiObject" + std::to_string(sceneGameObjects.size() + 1);
		guiObj_->SetTag(newTag);
		sceneGuiObjects[newTag] = guiObj_;
	}
}

GuiObject* SceneGraph::GetGuiObject(std::string tag_)
{
	if (sceneGuiObjects.find(tag_) != sceneGuiObjects.end())
	{
		return sceneGuiObjects[tag_];
	}
	return nullptr;
}

GameObject* SceneGraph::GetGameObject(std::string tag_)
{
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end())
	{
		return sceneGameObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_)
{
	for (auto go : sceneGameObjects)
	{
		go.second->Update(deltaTime_);
	}

}

void SceneGraph::Render(Camera* camera_)
{
	for (auto entry : sceneModels)
	{
		glUseProgram(entry.first);
		for (auto m : entry.second)
		{
			m->Render(camera_);
		}
	}
}

void SceneGraph::Draw(Camera* camera_)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::map<std::string, GuiObject*>::iterator it = sceneGuiObjects.begin();
	while (it != sceneGuiObjects.end()) {
		glUseProgram(ShaderHandler::GetInstance()->GetShader("test"));
		it->second->Draw(camera_);
		it++;
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

