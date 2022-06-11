/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Project: CS230
Author: Duho Choi
Creation date: 4/3/2022
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Component.h"

namespace math
{
	class TransformMatrix;
}

namespace CS230 {

	class Camera : public Component {
	public:
		Camera(math::rect2 movableRange);
		void SetPosition(math::vec2 newPosition);
		const math::vec2& GetPosition() const;
		void SetExtent(math::irect2 newExtent);
		void Update(const math::vec2& followObjPos); 

		math::TransformMatrix GetMatrix();
	private:
		math::irect2 extent;
		math::vec2 position;
		math::rect2 movableRange;
	};
}