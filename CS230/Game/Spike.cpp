
#pragma once
#include "Spike.h"
#include "GameObjectTypes.h"

Spike::Spike(math::vec2 startPos)
	: GameObject(startPos, 0, { 1.5, 2 })
{
	AddGOComponent(new CS230::Sprite("Assets/Mode3/Spike.spt", this));
}

GameObjectType Spike::GetObjectType() {
	return GameObjectType::Spike;
}
std::string Spike::GetObjectTypeName() {
	return "Spike";
}