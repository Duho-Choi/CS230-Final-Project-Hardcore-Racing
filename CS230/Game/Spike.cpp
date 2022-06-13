
#pragma once
#include "Spike.h"
#include "GameObjectTypes.h"

Spike::Spike(math::ivec2 startPos)
	: GameObject(static_cast<math::vec2>(startPos), 0, { 1.5, 2 })
{
	AddGOComponent(new CS230::Sprite("Assets/Mode3/Spike.spt", this));
}