#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H

#include <glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../..//Graphics/TextureHandler.h"
#include "../../Graphics/ShaderHandler.h"


struct Vertex2D {
	glm::vec2 position;
	glm::vec2 textureCoords;
};

class SpriteSurface {
public:
	SpriteSurface(std::string name_, glm::vec2 scale_, float angle_, glm::vec4 tint_);
	~SpriteSurface();

	void Draw(Camera* camera_, glm::vec3 position_);
	float GetWidth();
	float GetHeight();

	std::vector<Vertex2D> vertexList;



private:
	glm::vec2 scale;
	float angle, width, height;
	std::string name;
	glm::vec4 tint;

	GLuint VAO, VBO, textureID;
	GLuint tintColourLoc, inputTextureLoc, positionLoc, textureCoordsLoc, modelLoc, proj;

	void GenerateBuffers();


};

#endif