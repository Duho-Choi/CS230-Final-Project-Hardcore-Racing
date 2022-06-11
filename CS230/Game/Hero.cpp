/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/22/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"		// LogDebug
#include "../Engine/Camera.h"
#include "../Engine/Collision.h"	// RectCollision
#include "Hero.h"
#include "Mode1.h"	
#include "Hero_Anims.h"
#include "Gravity.h"
#include "Score.h"
#include "GameObjectTypes.h"		// GameObjectType
#include "GameParticles.h"

Hero::Hero(math::vec2 startPos)
	: GameObject(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right), jumpKey(CS230::InputKey::Keyboard::Up),
	hurtTimer(0), drawHero(true), isDead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/Hero.spt", this));
	for (CS230::GameObject* object : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
	{
		// Add code to go through all the objects in our GameObjectManager.
		// If it's a Floor, and the hero is colliding with it, move him and set the standingOnObject pointer
		// to that GameObject and reposition the hero

		if (object->GetObjectType() == GameObjectType::Floor
			&& GetGOComponent<CS230::Collision>()->DoesCollideWith(GetPosition()))
		{
			standingOnObject = object;
			SetPosition({ startPos.x, standingOnObject->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Top() });
		}
	}

	currState = &stateIdle;
	currState->Enter(this);
}
void Hero::Draw(math::TransformMatrix displayMatrix)
{
	if (drawHero == true)
	{
		GameObject::Draw(displayMatrix);
	}
}
void Hero::Update(double dt) {
	GameObject::Update(dt);

	// boundary check
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	if (GetPosition().x < Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + heroRect.Size().x / 2.0)
	{
		SetPosition({ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + heroRect.Size().x / 2.0, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
	else if (GetPosition().x > Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - heroRect.Size().x / 2.0)
	{
		SetPosition({ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - heroRect.Size().x / 2.0, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}

	// Todo: if the hurtTimer is not 0, decrement it and toggle the drawHero value
	if (hurtTimer > 0)
	{
		hurtTimer -= dt;
		drawHero = !drawHero;
	}
	else if (drawHero == false)
		drawHero = true;

	// if isDead is true, reduce life (do same thing when timer is 0)
	if (isDead == true)
	{
		Mode1::RemoveLife();
	}
}
void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		if (GetVelocity().x > -maxVelocity && GetVelocity().x <= 0)
		{
			// -Accelerating
			UpdateVelocity({ -acceleration * dt, 0 });
		}
		else if (GetVelocity().x < -maxVelocity)
		{
			// -Max velocity
			SetVelocity({ -maxVelocity, GetVelocity().y });
		}
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		if (GetVelocity().x < maxVelocity && GetVelocity().x >= 0)
		{
			// +Accelerating
			UpdateVelocity({ acceleration * dt, 0 });
		}
		else if (GetVelocity().x > maxVelocity)
		{
			// +Max velocity
			SetVelocity({ maxVelocity, GetVelocity().y });
		}
	}
	if (moveLeftKey.IsKeyDown() == false && moveRightKey.IsKeyDown() == false)
	{
		if (GetVelocity().x < -20)
		{
			UpdateVelocity({ drag * dt, 0 });
		}

		else if (GetVelocity().x > 20)
		{
			UpdateVelocity({ -drag * dt, 0 });
		}

		else if (GetVelocity().x <= 20 && GetVelocity().x >= -20 && GetVelocity().x != 0)
		{
			SetVelocity({ 0, GetVelocity().y });
		}
	}
}

// Object Type & CanCollideWith
GameObjectType Hero::GetObjectType()
{
	return GameObjectType::Hero;
}
std::string Hero::GetObjectTypeName()
{
	return "Hero";
}
bool Hero::CanCollideWith([[maybe_unused]] GameObjectType objectBType)
{
// These objects (Hero, Ship) should collide with everything, so return true
	if (objectBType == GameObjectType::Particle)
		return false;
	else
		return true;
}
void Hero::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Floor:

		[[fallthrough]];

	case GameObjectType::TreeStump:
		if (collideRect.Top() > GetPosition().y && objectB->DoesCollideWith(GetPosition()))			// TreeStump Top
		{
			standingOnObject = objectB;
			SetPosition({ GetPosition().x, collideRect.Top() });
			currState->TestForExit(this);
		}
		else if (heroRect.Right() > collideRect.Left() && heroRect.Left() < collideRect.Left())		// TreeStump Left
			SetPosition({ collideRect.Left() - heroRect.Size().x / 2 - 3, GetPosition().y });
		else if(heroRect.Left() < collideRect.Right() && heroRect.Right() > collideRect.Right())	// TreeStump Right
			SetPosition({ collideRect.Right() + heroRect.Size().x / 2 + 3, GetPosition().y });

		// Particle : When the hero lands on floor or TreeStump and his falling velocity is more than what he jumps with
		// (that means he fell from a larger height than what he can jump) create a particle at his feet
		if (std::abs(GetVelocity().y) > jumpVelocity)
		{
			Engine::GetGSComponent<SmokeEmitter>()->Emit(1, GetPosition(), { 0, 0 }, { 0, 0 }, 0);
		}

		break;

	case GameObjectType::Ball:
		if (collideRect.Top() > GetPosition().y && objectB->DoesCollideWith(GetPosition()))			// Ball Top
		{
			SetVelocity({ GetVelocity().x, jumpVelocity });
		}
		else if (heroRect.Right() > collideRect.Left() && heroRect.Left() < collideRect.Left())		// Ball Left
		{
			SetPosition({ collideRect.Left() - heroRect.Size().x / 2 - 3, GetPosition().y });
			hurtTimer = hurtTime;
			SetVelocity({ -maxVelocity / 3, jumpVelocity / 2 });
			ChangeState(&stateFalling);
		}
		else if (heroRect.Left() < collideRect.Right() && heroRect.Right() > collideRect.Right())	// Ball Right
		{
			SetPosition({ collideRect.Right() + heroRect.Size().x / 2 + 3, GetPosition().y });
			hurtTimer = hurtTime;
			SetVelocity({ maxVelocity / 3, jumpVelocity / 2 });
			ChangeState(&stateFalling);
		}

		break;

	case GameObjectType::Bunny:
	
	// Particle : Create a single smoke particle when the hero lands on the bunny or slides into the bunny
	//		For the location of the smoke particle find the middle between the hero and bunny collision box overlap
	//			(so if the hero collided on the left side, find the point between his right and the bunny left, 
	//		if on the right side find the middle between the hero left and the bunny right)
	//		If landing on the bunny, find the average between the hero bottom and the bunny top

		if (currState == &stateSkidding)
		{
			objectB->ResolveCollision(this);
			Engine::GetGSComponent<Score>()->AddScore(100);
			Engine::GetGSComponent<SmokeEmitter>()->Emit(1, { (heroRect.Left() + collideRect.Right()) / 2, GetPosition().y }, { 0, 0 }, { 0, 0 }, 0);
		}
		else
		{
			if (collideRect.Top() > GetPosition().y && objectB->DoesCollideWith(GetPosition()))		// Bunny Top
			{
				ChangeState(&stateFalling);
				SetVelocity({ GetVelocity().x, jumpVelocity / 2 });
				standingOnObject = nullptr;
				objectB->ResolveCollision(this);
				Engine::GetGSComponent<Score>()->AddScore(100);

				Engine::GetGSComponent<SmokeEmitter>()->Emit(1, { GetPosition().x, (heroRect.Bottom() + collideRect.Top()) / 2 }, { 0, 0 }, { 0, 0 }, 0);
			}
			else if (heroRect.Right() > collideRect.Left() && heroRect.Left() < collideRect.Left())		// Bunny Left
			{
				SetPosition({ collideRect.Left() - heroRect.Size().x / 2 - 3, GetPosition().y });
				hurtTimer = hurtTime;
				SetVelocity({ -maxVelocity / 3, jumpVelocity / 2 });
				ChangeState(&stateFalling);
			}
			else if (heroRect.Left() < collideRect.Right() && heroRect.Right() > collideRect.Right())	// Bunny Right
			{
				SetPosition({ collideRect.Right() + heroRect.Size().x / 2 + 3, GetPosition().y });
				hurtTimer = hurtTime;
				SetVelocity({ maxVelocity / 3, jumpVelocity / 2 });
				ChangeState(&stateFalling);
			}
		}

		break;

	case GameObjectType::Trigger:
		objectB->ResolveCollision(this);
		break;

	default:
		break;
	}
}

// Object States
// State_Jumping
void Hero::State_Jumping::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->SetVelocity({ hero->GetVelocity().x, Hero::jumpVelocity });  // Set the velocity.y

	// Set the hero's standingOnObject to a nullptr since he is no longer standing on that object 
	hero->standingOnObject = nullptr;
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt});  // Apply Gravity
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);

	if (hero->jumpKey.IsKeyDown() == false) {  // Jump Key not pressed
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
		hero->ChangeState(&hero->stateFalling);
	}

	if (hero->GetVelocity().y <= 0) {
		hero->ChangeState(&hero->stateFalling);  // Highest y position
	}
}

// State_Idle
void Hero::State_Idle::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));

	// check to make sure the hero is standing on an object(the pointer is not nullptr)
	// If it is, log an error message
	if (hero->standingOnObject == nullptr)
		Engine::GetLogger().LogError("Standing Object is nullptr");
}
void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {

}
void Hero::State_Idle::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);

	if (hero->jumpKey.IsKeyDown() == true)  // Jump Key pressed
		hero->ChangeState(&hero->stateJumping);

	if (hero->moveLeftKey.IsKeyDown() == true || hero->moveRightKey.IsKeyDown() == true)  // Left or Right Key pressed
		hero->ChangeState(&hero->stateRunning);

	// If the hero's position no longer collides with the object 
	// (his position, not his collision box) he is standing on, make him fall
	// I did this also in Idle	
	if (hero->standingOnObject == nullptr)
	{
		hero->ChangeState(&hero->stateFalling);
	}
	else if (hero->standingOnObject != nullptr && hero->standingOnObject->GetGOComponent<CS230::Collision>() != nullptr)
	{
		if (hero->standingOnObject->GetGOComponent<CS230::Collision>()->DoesCollideWith({ hero->GetPosition().x, hero->GetPosition().y - 1 }) == false)
		{
			hero->standingOnObject = nullptr;
			hero->ChangeState(&hero->stateFalling);
		}
	}
}

// State_Running
void Hero::State_Running::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));

	if (hero->moveLeftKey.IsKeyDown() == true)
		hero->SetScale({ -1.0, 1.0 });

	else if (hero->moveRightKey.IsKeyDown() == true)
		hero->SetScale({ 1.0, 1.0 });

	// check to make sure the hero is standing on an object(the pointer is not nullptr)
	// If it is, log an error message
	if (hero->standingOnObject == nullptr)
		Engine::GetLogger().LogError("Standing Object is nullptr");
}
void Hero::State_Running::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);	// Change X Velocity stuff
}
void Hero::State_Running::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == true)	// Jump Key pressed
		hero->ChangeState(&hero->stateJumping);
	if (hero->GetVelocity().x == 0)	 //velocity.x == 0
		hero->ChangeState(&hero->stateIdle);
	if ((hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x < 0 && hero->moveLeftKey.IsKeyDown() == false) ||
		(hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0 && hero->moveRightKey.IsKeyDown() == false))	// Pressed other direction
		hero->ChangeState(&hero->stateSkidding);

	// If the hero's position no longer collides with the object 
	// (his position, not his collision box) he is standing on, make him fall
	if (hero->standingOnObject == nullptr)
	{
		hero->ChangeState(&hero->stateFalling);
	}
	else if (hero->standingOnObject != nullptr && hero->standingOnObject->GetGOComponent<CS230::Collision>() != nullptr)
	{
		if (hero->standingOnObject->GetGOComponent<CS230::Collision>()->DoesCollideWith({ hero->GetPosition().x, hero->GetPosition().y - 1 }) == false)
		{
			hero->standingOnObject = nullptr;
			hero->ChangeState(&hero->stateFalling);
		}
	}
}

// State _Falling
void Hero::State_Falling::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}
void Hero::State_Falling::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });  //Apply Gravity
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Falling::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);

	if (hero->standingOnObject != nullptr)
	{
		hero->SetVelocity({ hero->GetVelocity().x, 0 });

		if (hero->GetVelocity().x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == true)
				hero->ChangeState(&hero->stateSkidding);
			else
				hero->ChangeState(&hero->stateRunning);
		}
		else if (hero->GetVelocity().x < 0)
		{
			if (hero->moveRightKey.IsKeyDown() == true)
				hero->ChangeState(&hero->stateSkidding);
			else
				hero->ChangeState(&hero->stateRunning);
		}
		else
			hero->ChangeState(&hero->stateIdle);
	}
	else	
	{
		// When we land on an object we will set the standingOnObject pointer and reuse this function
		for (CS230::GameObject* objectA : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
		{
			if (objectA->GetObjectType() != GameObjectType::Hero)
			{
				if (objectA->GetGOComponent<CS230::Collision>() != nullptr)
				{
					if (objectA->GetGOComponent<CS230::Collision>()->DoesCollideWith(hero->GetPosition())
						&& objectA->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Top() > hero->GetPosition().y)
					{
						hero->standingOnObject = objectA;
						hero->currState->TestForExit(hero);
						return;
					}
				}
			}
		}
	}

	// Todo: if the hero is travels below -300 pixels, set the hero to dead
	if (hero->GetPosition().y < -300)
	{
		hero->isDead = true;
	}
}

// State_Skidding
void Hero::State_Skidding::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}
void Hero::State_Skidding::Update(GameObject* object, double dt) {

	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x > 0)
			hero->UpdateVelocity({ -(drag * 2) * dt, 0 });
	}
	if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x < 0)
			hero->UpdateVelocity({ (drag * 2) * dt, 0 });
	}
}
void Hero::State_Skidding::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == true)	// Jump key pressed
		hero->ChangeState(&hero->stateJumping);
	else if (hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x <= 0)	// Left key down
		hero->ChangeState(&hero->stateRunning);
	else if (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x >= 0)	// Right key down
		hero->ChangeState(&hero->stateRunning);
	else if (hero->moveRightKey.IsKeyDown() == false && hero->moveLeftKey.IsKeyDown() == false)
		hero->ChangeState(&hero->stateRunning);
}