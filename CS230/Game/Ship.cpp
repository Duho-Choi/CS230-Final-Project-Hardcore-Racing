/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/22/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetLogger, GetWindow
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "Ship.h"
#include "Laser.h"
#include "Flame_Anims.h"
#include "Ship_Anims.h"
#include "ScreenWrap.h"
#include "GameObjectTypes.h"	//GameObjectType

Ship::Ship(math::vec2 startPos)
	: GameObject(startPos, 0, { 0.75, 0.75 }), rotateCounterKey(CS230::InputKey::Keyboard::A),
	rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W),
	laserKey(CS230::InputKey::Keyboard::Space), isDead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/Ship.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	leftFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	rightFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
}
void Ship::Update(double dt) {
	GetGOComponent<CS230::Sprite>()->Update(dt);
	leftFlameSprite.Update(dt);
	rightFlameSprite.Update(dt);

	if (isDead == false)
	{
		// Rotation
		if (rotateCounterKey.IsKeyDown() == true)
			UpdateRotation(1.5 * dt);
		if (rotateClockKey.IsKeyDown() == true)
			UpdateRotation(-1.5 * dt);

		// Acceleration
		if (accelerateKey.IsKeyDown() == true)
		{
			UpdateVelocity(math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
			if (wasAccelKeyPressed == false)
			{
				leftFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				rightFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			}
		}
		else if (accelerateKey.IsKeyReleased() == true && accelerateKey.IsKeyDown() == false)
		{
			leftFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			rightFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		}

		// Laser
		CS230::GameObjectManager* gameObjectManager = Engine::GetGSComponent<CS230::GameObjectManager>();
		if (laserKey.IsKeyDown() == true)
		{
			if (wasLaserKeyPressed == false)
			{
				gameObjectManager->Add(new Laser(GetPosition() + math::RotateMatrix{ GetRotation() } * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(3) - GetGOComponent<CS230::Sprite>()->GetHotSpot(0)),
					GetRotation(), GetScale(), math::RotateMatrix{ GetRotation() } * Laser::LaserVelocity));
				gameObjectManager->Add(new Laser(GetPosition() + math::RotateMatrix{ GetRotation() } * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(4) - GetGOComponent<CS230::Sprite>()->GetHotSpot(0)),
					GetRotation(), GetScale(), math::RotateMatrix{ GetRotation() } * Laser::LaserVelocity));
			}
		}
	}

	UpdateVelocity(-GetVelocity() * Ship::drag * dt);
	UpdatePosition(GetVelocity() * dt);

	GetGOComponent<ScreenWrap>()->Update(dt);
	wasAccelKeyPressed = accelerateKey.IsKeyDown();
	wasLaserKeyPressed = laserKey.IsKeyDown();
}

void Ship::Draw(math::TransformMatrix cameraMatrix)
{
	leftFlameSprite.Draw(cameraMatrix * GetMatrix() *
		math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1) - GetGOComponent<CS230::Sprite>()->GetHotSpot(0)));
	rightFlameSprite.Draw(cameraMatrix * GetMatrix() *
		math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2) - GetGOComponent<CS230::Sprite>()->GetHotSpot(0)));

	GameObject::Draw(cameraMatrix);
}

// Object Type & CanCollideWith
GameObjectType Ship::GetObjectType()
{
	return GameObjectType::Ship;
}
std::string Ship::GetObjectTypeName()
{
	return "Ship";
}
bool Ship::CanCollideWith([[maybe_unused]] GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Meteor)
		return true;
	else
		return false;
}

// Resolve Collision
void Ship::ResolveCollision(CS230::GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Meteor)
	{
		leftFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		rightFlameSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		RemoveGOComponent<CS230::Collision>();
		isDead = true;
	}
}