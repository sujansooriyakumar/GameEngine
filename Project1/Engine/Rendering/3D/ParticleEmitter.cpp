#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int count_, std::string shaderName_, glm::vec3 position_)
{
	position = position_;
	particleCount = count_;
	shaderProg = ShaderHandler::GetInstance()->GetShader(shaderName_);
	if (shaderProg == 0) {
		Debug::Error("Shader not found", "ParticleEmitter.cpp", __LINE__);
	}
	particles.reserve(particleCount * sizeof(Particle));
	for (int i = 0; i < particleCount; i++) {
		particles.push_back(new Particle(shaderProg, position_, glm::vec3(1.0f, 1.0f, 0.0f), glm::linearRand(1.0f, 10.0f)));
	}

}

void ParticleEmitter::Update(float deltaTime_)
{
	std::cout << particles.size() << std::endl;
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->lifeTime -= deltaTime_;
		particles.at(i)->size = glm::linearRand(100.0f, 1000.0f);
		particles.at(i)->colour = glm::vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0));
		if (particles.at(i)->lifeTime <= 0) {
			particles.erase(particles.begin() + i);
		}
		
	}
	
}

void ParticleEmitter::Render(Camera* camera_)
{
	glUseProgram(shaderProg);
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->Render(camera_);
	}
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Randomize()
{
}
