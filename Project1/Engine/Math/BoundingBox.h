#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox
{
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;

	inline BoundingBox()
	{
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_)
	{
		minVert = minVert_;
		maxVert = maxVert_;
		transform = transform_;
	}
	inline bool Intersects(BoundingBox* box_)
	{
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);
		glm::vec3 otherMinCorner = GetTransformedPoint(box_->minVert, box_->transform);
		glm::vec3 otherMaxCorner = GetTransformedPoint(box_->maxVert, box_->transform);
		if (minCorner.x <= otherMaxCorner.x && maxCorner.x >= otherMinCorner.x)
		{

		}
		else
		{
			return false;
		}
		if (minCorner.y <= otherMaxCorner.y && maxCorner.y >= otherMinCorner.y)
		{
		}
		else
		{
			return false;
		}
		if (minCorner.z <= otherMaxCorner.z && maxCorner.z >= otherMinCorner.z)
		{

		}
		else
		{
			return false;

		}

		return true;
	}
private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_)
	{
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};

#endif