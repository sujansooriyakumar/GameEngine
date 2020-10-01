#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>
#include "BoundingBox.h"
#include "CollisionDetection.h"
struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;
	float intersectionDist;
	inline Ray()
	{
		direction = glm::vec3();
		origin = glm::vec3();
		intersectionDist = 0.0f;
	}
	inline Ray(glm::vec3 origin_, glm::vec3 direction_)
	{
		direction = direction_;
		origin = origin_;
		intersectionDist = 0.0f;
	}
	inline Ray& operator =(const Ray& ray_)
	{
		direction = ray_.direction;
		origin = ray_.origin;
		intersectionDist = 0.0f;
	}
	inline bool IsColliding(BoundingBox* box_)
	{
		intersectionDist = -1.0f;
		return CollisionDetection::RayObbIntersection(this, box_);
	}
};
#endif 

