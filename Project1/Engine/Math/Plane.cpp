#include "Plane.h"

Plane::Plane(glm::vec3 p1_, glm::vec3 p2_, glm::vec3 p3_)
{
	v = p2_ - p1_;
	u = p3_ - p1_;
	normal = glm::cross(v, u);
	normal = glm::normalize(normal);
	d = -(glm::dot(normal, p1_));
}

Plane::Plane() {
}

Plane::~Plane()
{
}

void Plane::SetNormal(glm::vec3 normal_)
{
	normal = normal_;

}

float Plane::Distance(glm::vec3 point_)
{

	return (d + glm::dot(normal, point_));
}
