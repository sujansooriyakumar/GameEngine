#ifndef PLANE_H
#define PLANE_H
#include <glm/glm.hpp>
class Plane
{
public:
	float d;

	Plane(glm::vec3 p1_, glm::vec3 p2_, glm::vec3 p3_);
	Plane();
	~Plane();
	void Normalize();
	void SetNormal(glm::vec3 normal_);
	float Distance(glm::vec3 point_);
	glm::vec3 normal;
	glm::vec3 v;
	glm::vec3 u;
private:

};


#endif // !PLANE_H
