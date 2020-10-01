#include "Frustum.h"
#include <iostream>
Frustum::
Frustum()
{

}

Frustum::~Frustum()
{

}

void Frustum::CreateFrustum(glm::mat4 projectionMatrix_, glm::mat4 viewMatrix_)
{

	

	glm::mat4x4 viewProj;
	viewProj = projectionMatrix_ * viewMatrix_;

	Planes[0].x = viewProj[0][3] - viewProj[0][2];
	//std::cout << Planes[0].x << std::endl;
	Planes[0].y = viewProj[1][3] - viewProj[1][2];
	Planes[0].z = viewProj[2][3] - viewProj[2][2];
	Planes[0].w = viewProj[3][3] - viewProj[3][2];

	Planes[1].x = viewProj[0][3] + viewProj[0][2];
	Planes[1].y = viewProj[1][3] + viewProj[1][2];
	Planes[1].z = viewProj[2][3] + viewProj[2][2];
	Planes[1].w = viewProj[3][3] + viewProj[3][2];

	Planes[2].x = viewProj[0][3] - viewProj[0][0];
	Planes[2].y = viewProj[1][3] - viewProj[1][0];
	Planes[2].z = viewProj[2][3] - viewProj[2][0];
	Planes[2].w = viewProj[3][3] - viewProj[3][0];

	Planes[3].x = viewProj[0][3] + viewProj[0][0];
	Planes[3].y = viewProj[1][3] + viewProj[1][0];
	Planes[3].z = viewProj[2][3] + viewProj[2][0];
	Planes[3].w = viewProj[3][3] + viewProj[3][0];

	Planes[4].x = viewProj[0][3] - viewProj[0][1];
	Planes[4].y = viewProj[1][3] - viewProj[1][1];
	Planes[4].z = viewProj[2][3] - viewProj[2][1];
	Planes[4].w = viewProj[3][3] - viewProj[3][1];

	Planes[5].x = viewProj[0][3] + viewProj[0][1];
	Planes[5].y = viewProj[1][3] + viewProj[1][1];
	Planes[5].z = viewProj[2][3] + viewProj[2][1];
	Planes[5].w = viewProj[3][3] + viewProj[3][1];
	for (int i = 0; i < 5; i++)
	{
		float length;

		length = sqrt((Planes[i].x * Planes[i].x) + (Planes[i].y * Planes[i].y) + (Planes[i].z * Planes[i].z));
		Planes[i].x /= length;
		Planes[i].y /= length;
		Planes[i].z /= length;
		Planes[i].w /= length;
		//std::cout << Planes[i].x << " " << Planes[i].y << " " << Planes[i].z << " " << Planes[i].w << std::endl;
	}
}
bool Frustum::CheckBoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_)
{
	return true;
}