#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), projLoc(0), viewLoc(0), modelLoc(0),
lightDiffuseLoc(0), lightAmbientLoc(0), lightPosLoc(0), lightColourLoc(0), diffuseMapLoc(0),
shininessLoc(0), transparencyLoc(0), ambientLoc(0), diffuseLoc(0), specularLoc(0)
{

	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0)
	{
		subMesh.vertexList.clear();
	}
	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	glUniform1fv(lightDiffuseLoc, 1, camera_->GetLightSources().front()->GetDiffuse());
	glUniform1fv(lightAmbientLoc, 1, camera_->GetLightSources().front()->GetAmbient());
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera_->GetLightSources().front()->GetPosition()));
	glUniform3fv(lightColourLoc, 1, glm::value_ptr(camera_->GetLightSources().front()->GetColour()));

	glUniform1i(diffuseMapLoc, 0);
	glUniform1fv(transparencyLoc, 1, &(subMesh.material.transparency));
	glUniform1fv(shininessLoc, 1, &(subMesh.material.shininess));
	glUniform3fv(ambientLoc, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(diffuseLoc, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(specularLoc, 1, glm::value_ptr(subMesh.material.specular));


	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));

	glBindVertexArray(VAO);
	for (int i = 0; i < instances_.size(); i++)glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
	glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	modelLoc = glGetUniformLocation(shaderProgram, "model");

	viewPositionLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColour");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");

	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	specularLoc = glGetUniformLocation(shaderProgram, "material.specular");
	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");

}