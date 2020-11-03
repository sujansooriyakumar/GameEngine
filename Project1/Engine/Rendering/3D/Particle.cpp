#include "Particle.h"

Particle::Particle(GLuint shaderID_, glm::vec3 position_, glm::vec3 colour_, float lifeTime_)
{
	VAO = 0;
	VBO = 0;
	position = position_;
	colour = colour_;
	lifeTime = lifeTime_;
	size = 1.0f;

	GenerateBuffers();
}

Particle::~Particle()
{
	glDeleteVertexArrays(1, &VAO);

}

void Particle::Render(Camera* camera_)
{

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniform3fv(colourLoc, 1, glm::value_ptr(colour));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniform3fv(positionLoc, 1, glm::value_ptr(position));
	glUniform1fv(pointSizeLoc, 1, &size);


	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindVertexArray(VAO);

	glDrawArrays(GL_POINTS, 0, 1);
	
	glBindVertexArray(0);
	glDisable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_BLEND);
}

void Particle::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);



	GLuint shaderProg = ShaderHandler::GetInstance()->GetShader("ParticleShader");
	glUseProgram(shaderProg);
	colourLoc = glGetUniformLocation(shaderProg, "test");
	positionLoc = glGetUniformLocation(shaderProg, "pos");
	viewLoc = glGetUniformLocation(shaderProg, "view");
	projLoc = glGetUniformLocation(shaderProg, "proj");
	pointSizeLoc = glGetUniformLocation(shaderProg, "size");

}
