#ifndef OPENGLMESH_H
#define OPENGLMESH_H
#include "Mesh.h"

class OpenGLMesh : public Mesh {
public:
	OpenGLMesh(SubMesh subMesh_, GLuint shaderProgram_);
	~OpenGLMesh();
	void Render (Camera* camera_, std::vector<glm::mat4> instances_) override;

private:
	void GenerateBuffers();
	SubMesh subMesh;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;

	GLuint viewPositionLoc;
	GLuint	lightPosLoc;
	GLuint lightAmbientLoc;
	GLuint	lightDiffuseLoc;
	GLuint	lightColourLoc;

	GLuint diffuseMapLoc;
	GLuint	shininessLoc;
	GLuint ambientLoc;
	GLuint	specularLoc;
	GLuint transparencyLoc;
	GLuint diffuseLoc;
	
};
#endif // !OPENGLMESH_H