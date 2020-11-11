#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"
#include "rapidxml.hpp"
#include <iostream>
#include<fstream>

int SDL_main(int argc, char* argv[]) {
	std::ifstream myfile("doc.xml");
	rapidxml::xml_document<> doc;
	std::stringstream buffer;
	buffer << myfile.rdbuf();
	myfile.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<>* root = doc.first_node();
	int id = atoi(root->first_node("game")->first_attribute("id")->value());
	std::string title = root->first_node("game")->first_node("window")->first_node("title")->value();
	int width = atoi(root->first_node("game")->first_node("window")->first_node("width")->value());
	
	int height = atoi(root->first_node("game")->first_node("window")->first_node("height")->value());


	CoreEngine::GetInstance()->SetGameInterface(new Game1, Renderer::RendererType::OpenGL);
	if (!CoreEngine::GetInstance()->OnCreate(title, width, height)) {
		std::cout << "Engine failed to be created" << std::endl;
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;


}