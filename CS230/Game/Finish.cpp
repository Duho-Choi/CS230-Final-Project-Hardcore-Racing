
#include "../Engine/Rect.h"
#include "../Engine/Collision.h"
#include "Finish.h"

Finish::Finish(math::irect2 rect)
	: GameObject(static_cast<math::vec2>(rect.point1))
{
	AddGOComponent(new CS230::RectCollision(rect, this));
}