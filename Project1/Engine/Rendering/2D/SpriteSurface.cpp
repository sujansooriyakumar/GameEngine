#include "SpriteSurface.h"


SpriteSurface::SpriteSurface(std::string name_, glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	VAO = 0;
	VBO=0;
	name = name_;
	scale = scale_;
	angle = angle_;
	tint = tint_;
	Vertex2D A;
	Vertex2D B;
	Vertex2D C;
	Vertex2D D;
	A.position= glm::vec2(-0.5f, 0.5f);
	A.textureCoords = glm::vec2(0,0);
	B.position = glm::vec2(0.5f, 0.5f);
	B.textureCoords = glm::vec2(1,0);
	C.position = glm::vec2(-0.5f, -0.5f);
	C.textureCoords = glm::vec2(0,1);
	D.position = glm::vec2(0.5f, -0.5f);
	D.textureCoords = glm::vec2(1, 1);
	
	vertexList.push_back(C);
	vertexList.push_back(A);
	vertexList.push_back(D);
	vertexList.push_back(B);
	

	if (TextureHandler::GetInstance()->GetTexture(name) == 0) {
		TextureHandler::GetInstance()->CreateTexture(name, "./Resources/Texture/" + name_ + ".png");
		
	}
	textureID = TextureHandler::GetInstance()->GetTexture(name);
		width = TextureHandler::GetInstance()->GetTextureData(name)->width;
		height = TextureHandler::GetInstance()->GetTextureData(name)->height;
	GenerateBuffers();
}

SpriteSurface::~SpriteSurface()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void SpriteSurface::Draw(Camera* camera_, glm::vec3 position_)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glUniform1i(inputTextureLoc, 0);

	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle, glm::vec3(0,1,0));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, 1));

	glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));

	glUniform4fv(tintColourLoc, 1, glm::value_ptr(tint));
	glBindVertexArray(VAO);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);


}

float SpriteSurface::GetWidth()
{
	return width;
}

float SpriteSurface::GetHeight()
{
	return height;
}

void SpriteSurface::GenerateBuffers()
{

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);


	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, textureCoords));

	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// tintColour, inputTexture, position, textureCoords;
	GLuint shaderprog = ShaderHandler::GetInstance()->GetShader("test");
	tintColourLoc = glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("test"), "tintColour");
	inputTextureLoc = glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("test"), "inputTexture");
	modelLoc = glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("test"), "model");
	proj = glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("test"), "proj");


}
