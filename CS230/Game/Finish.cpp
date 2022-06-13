
#include "../Engine/Rect.h"
#include "../Engine/Sprite.h"
#include "Finish.h"

Finish::Finish(math::ivec2 startPos)
	: GameObject(static_cast<math::vec2>(startPos), 0, { 7.5, 5 })
{
	AddGOComponent(new CS230::Sprite("Assets/Mode3/Finish_line.spt", this));
}