/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.cpp
Project: CS230
Author: Duho Choi
Creation date: 5/25/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "Laser.h"

Laser::Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity)
	: GameObject(pos, rotation, scale)
{
	AddGOComponent(new CS230::Sprite("assets/Laser.spt", this));
	SetVelocity(laserVelocity);
}
void Laser::Update(double dt)
{
	GameObject::Update(dt);

	UpdatePosition(GetVelocity() * dt); 

	CS230::Sprite* spritePtr = GetGOComponent<CS230::Sprite>();
	if ((GetPosition().x > Engine::GetWindow().GetSize().x + spritePtr->GetFrameSize().x / 2.0)
		|| (GetPosition().x < 0 - spritePtr->GetFrameSize().x / 2.0)
		|| (GetPosition().y > Engine::GetWindow().GetSize().y + spritePtr->GetFrameSize().y / 2.0)
		|| (GetPosition().y < 0 - spritePtr->GetFrameSize().y / 2.0))
	{
		SetShouldBeDestroyed(true);
	}
	
}
bool Laser::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Meteor)
		return true;
	else
		return false;
}
void Laser::ResolveCollision(GameObject* objectB)
{
	if (CanCollideWith(objectB->GetObjectType()) == true)
	{
		objectB->ResolveCollision(this);
		SetShouldBeDestroyed(true);
	}
}