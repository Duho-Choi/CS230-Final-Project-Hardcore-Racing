/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/29/2022
-----------------------------------------------------------------*/
#include "Bunny.h"
#include "Bunny_Anims.h"
#include "GameObjectTypes.h"		//GameObjectType
#include "../Engine/Collision.h"	//CS230::Collision

Bunny::Bunny(math::vec2 pos) : GameObject(pos) 
{
	AddGOComponent(new CS230::Sprite("Assets/bunny.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::None_Anim));
}

// Object Type
GameObjectType Bunny::GetObjectType()
{
	return GameObjectType::Bunny;
}
std::string Bunny::GetObjectTypeName()
{
	return "Bunny";
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		RemoveGOComponent<CS230::Collision>();
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	}
}