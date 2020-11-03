#ifndef PARTICLE_H
#define PARTICLE_H
#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "..//..//Camera/Camera.h"
#include "../../Graphics/ShaderHandler.h"

#include <glm/gtc/type_ptr.hpp>

class Particle {
public:
	Particle(GLuint shaderID_, glm::vec3 position_, glm::vec3 colour_, float lifeTime_);
	~Particle();
	void Render(Camera* camera_);

	float lifeTime;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 colour;
	float size;

private:
	void GenerateBuffers();

	GLuint VAO, VBO;
	GLuint modelLoc, viewLoc, projLoc, pointSizeLoc, positionLoc, colourLoc;
};
#endif // !PARTICLE_H