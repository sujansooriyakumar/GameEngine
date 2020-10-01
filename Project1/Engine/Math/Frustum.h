#ifndef FRUSTUM_H
#define FRUSTUM_H
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
class Frustum
{
public:
	Frustum();

	~Frustum();

	void CreateFrustum(glm::mat4 projectionMatrix_, glm::mat4 viewMatrix_);
	bool CheckBoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_);
private:

	glm::vec4 Planes[6];

};
#endif
