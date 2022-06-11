/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/29/2022
-----------------------------------------------------------------*/
#include "Meteor.h"
#include "../Engine/Engine.h"	//GetWindow
#include "../Engine/Vec2.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Collision.h"
#include "ScreenWrap.h"
#include "Meteor_Anims.h"
#include "GameParticles.h"
#include "GameObjectTypes.h"	//GameObjectType
#include "Score.h"
#include "Laser.h"

Meteor::Meteor() : GameObject({ 0, 0 }), health(100), size(1)
{
	SetPosition(static_cast<math::vec2>
		(math::ivec2{ rand() % Engine::GetWindow().GetSize().x, rand() % Engine::GetWindow().GetSize().y }));
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	double radians{ 0 };
	while (radians < 0 || radians > 2 * PI)
	{
		radians = rand() % 100 / 100.0;
	}
	SetRotation(radians);
	SetVelocity(static_cast<math::vec2>(math::ivec2{ (rand() * rand() * rand()) % 100 ,
		(rand() * rand() * rand()) % 100 }));
	double scalar{ 0 };
	while (scalar < 0.75 || scalar > 1)
	{
		scalar = rand() % 100 / 100.0;
	}
	SetScale({ scalar , scalar });
}

Meteor::Meteor(Meteor& original) : Meteor()
{
	// For size 2, the scale should be 50 % -75 % of the full size
	// For size 3, the scale should be 25 % -50 % of the full size
	health = 100;
	size = original.size + 1;
	double scalar{ 0 };
	switch (size)
	{
	case 2:
		while (scalar < 0.5 || scalar > 0.75)
		{
			scalar = rand() % 100 / 100.0;
		}
		break;

	case 3:

		while (scalar < 0.5 || scalar > 0.66)
		{
			scalar = rand() % 100 / 100.0;
		}
		break;

	default:
		break;
	}
	SetScale(original.GetScale() * scalar);
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	if (GetGOComponent<ScreenWrap>() != nullptr)
	{
		GetGOComponent<ScreenWrap>()->Update(dt);
	}

	if (GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Meteor_Anim::Fade_Anim))
	{
		if (GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
		{
			SetShouldBeDestroyed(true);
		}
	}
}

// Object Type
GameObjectType Meteor::GetObjectType()
{
	return GameObjectType::Meteor;
}
std::string Meteor::GetObjectTypeName()
{
	return "Meteor";
}

void Meteor::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Laser)
	{
		health -= 10;
		if (health <= 0)
		{
			if (size != 3)
			{
				Meteor* new_meteor1 = new Meteor(*this);
				Meteor* new_meteor2 = new Meteor(*this);
				new_meteor1->SetPosition(GetPosition());
				new_meteor2->SetPosition(GetPosition());
				new_meteor1->SetRotation(GetRotation() + (PI / 6));
				new_meteor2->SetRotation(GetRotation() - (PI / 6));
				new_meteor1->SetVelocity(math::RotateMatrix{ new_meteor1->GetRotation() } * GetVelocity());
				new_meteor2->SetVelocity(math::RotateMatrix{ new_meteor2->GetRotation() } * GetVelocity());

 				Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new_meteor1);
				Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new_meteor2);
			}
 
			// Play the fade out animation on the old meteor, and remove the collision
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
			RemoveGOComponent<CS230::Collision>();

			//Add 100 points * size to our score.
			Engine::GetGSComponent<Score>()->AddScore(100 * size);
		}
		else
		{
			UpdateVelocity(objectB->GetVelocity() * 0.01);
		}

		if (GetGOComponent<CS230::CircleCollision>() != nullptr)
		{
			math::vec2 vectorToObject = (objectB->GetPosition() - GetPosition()).Normalize();
			math::vec2 emitterPosition = GetPosition() + vectorToObject * GetGOComponent<CS230::CircleCollision>()->GetRadius();
			math::vec2 emitVector = ((vectorToObject * 2 + objectB->GetVelocity().Normalize()).Normalize());

			Engine::GetGSComponent<HitEmitter>()->Emit(1, emitterPosition, GetVelocity(), { 0, 0 }, 0);
			Engine::GetGSComponent<MeteorBitEmitter>()->Emit(10, emitterPosition, GetVelocity(), emitVector * 50, PI / 2);
		}
	}
}