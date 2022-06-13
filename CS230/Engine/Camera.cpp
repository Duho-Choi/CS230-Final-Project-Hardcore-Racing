/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/3/2022
-----------------------------------------------------------------*/
#include "Camera.h"
#include "..\Engine\TransformMatrix.h"

namespace CS230 {

	Camera::Camera(math::rect2 movableRange)
		: movableRange(movableRange), position({0, 0})
	{}
	void Camera::SetPosition(math::vec2 newPosition) {
		position = newPosition;
	}
	const math::vec2& Camera::GetPosition() const {
		return position;
	}
	void Camera::SetExtent(math::irect2 newExtent) {
		extent = newExtent;
	}
	void Camera::Update(const math::vec2& followObjPos) {

		if (followObjPos.x - position.x < movableRange.Left())
		{
			position.x = followObjPos.x - movableRange.Left();
		}
		else if (followObjPos.x - position.x > movableRange.Right())
		{
			position.x = followObjPos.x - movableRange.Right();
		}

		if (position.x < extent.Left())
		{
			position.x = extent.Left();
		}
		else if (position.x > extent.Right())
		{
			position.x = extent.Right();
		}
	}

	void Camera::Mode3_Update(double dt, int speed)
	{
		if (position.y < extent.Top())
		{
			position.y += dt * speed;
		}

		if (position.y > extent.Top())
		{
			position.y = extent.Top();
		}
		
	}

	math::TransformMatrix Camera::GetMatrix()
	{
		math::TransformMatrix result = math::TranslateMatrix(-position);
		return result;
	}
}
