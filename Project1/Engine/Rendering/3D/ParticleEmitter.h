#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#include <string>
#include "..//..//Graphics/ShaderHandler.h"
#include "..//..//Core/CoreEngine.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include "Particle.h"
class ParticleEmitter {
public:
	ParticleEmitter(int count_, std::string shaderName_, glm::vec3 position_);
	void Update(float deltaTime_);
	void Render(Camera* camera_);
	~ParticleEmitter();
private:
	void Randomize();
	int particleCount;
	GLuint shaderProg;
	std::vector<Particle*> particles;
	glm::vec3 position;
};
#endif // !PARTICLEEMITTER_H
