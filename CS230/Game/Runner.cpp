
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/ShowCollision.h"
#include "Runner.h"
#include "Mode3.h"
#include "GameObjectTypes.h"
#include "Runner_Anims.h"		// Runner_Anim
#include "GameParticles.h"
#include "Explosion_Anims.h"
#include "Hp.h"

Runner::Runner(math::vec2 startPos)
	: GameObject(startPos, 0, { 0.6, 0.6 }), leftKey(CS230::InputKey::Keyboard::A),
	rightKey(CS230::InputKey::Keyboard::D), frontKey(CS230::InputKey::Keyboard::W),
	backKey(CS230::InputKey::Keyboard::S), rotation(0),
	hurtTimer(0), drawRunner(true), isDead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/Mode3/Runner.spt", this));
	explosionSprite.PlayAnimation(static_cast<int>(Explosion_Anim::None_Anim));
}
void Runner::Update(double dt) 
{
	GetGOComponent<CS230::Sprite>()->Update(dt);

	if (isDead == false)
	{
		// Go Left & Right
		if (leftKey.IsKeyDown() == true)
		{
			if (rotation < maxRotation)
				rotation += 1.0 * dt;

			UpdateVelocity(math::vec2{ -left_right_accel * dt, 0 });
		}
		if (rightKey.IsKeyDown() == true)
		{
			if (rotation > -maxRotation)
				rotation -= 1.0 * dt;

			UpdateVelocity(math::vec2{ left_right_accel * dt, 0 });
		}
		if (leftKey.IsKeyDown() == false && rightKey.IsKeyDown() == false)
		{
			if (rotation > 0.02 || rotation < -0.02)
			{
				if (rotation > 0)
					rotation -= 0.7 * dt;
				else if (rotation < 0)
					rotation += 0.7 * dt;
			}
		}

		// Go Front
		if (frontKey.IsKeyDown() == true)
		{
			if(GetVelocity().y < maxVelocity)
				UpdateVelocity({ 0, accel * dt });
		}
		if (backKey.IsKeyDown() == true)
		{
			if (GetVelocity().y > -maxVelocity)
				UpdateVelocity({ 0, -accel * dt });
		}
		Engine::GetGSComponent<DustEmitter>()->Emit(1,
			GetPosition() + static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(1) - GetGOComponent<CS230::Sprite>()->GetHotSpot(0)),
			GetVelocity(), { 0, 0 }, 1);
		Engine::GetGSComponent<DustEmitter>()->Emit(1,
			GetPosition() + static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(2) - GetGOComponent<CS230::Sprite>()->GetHotSpot(0)),
			GetVelocity(), { 0, 0 }, 1);

		// Blink Runner
		if (hurtTimer > 0)
		{
			hurtTimer -= dt;
			drawRunner = !drawRunner;
		}
		else if (drawRunner == false)
			drawRunner = true;
	}

	UpdateVelocity(-GetVelocity() * Runner::drag * dt);
	UpdatePosition({ GetVelocity().x * dt, (Mode3::speed + GetVelocity().y) * dt });

	// Set position inside screen
	if (GetPosition().x < 0)
		SetPosition({ 0, GetPosition().y });
	else if (GetPosition().x > Engine::GetWindow().GetSize().x)
		SetPosition({ static_cast<double>(Engine::GetWindow().GetSize().x), GetPosition().y });

	math::vec2 cameraPosition = Engine::GetGSComponent<CS230::Camera>()->GetPosition();
	if (GetPosition().y < cameraPosition.y)
		SetPosition({ GetPosition().x, cameraPosition.y });
	else if (GetPosition().y > cameraPosition.y + Engine::GetWindow().GetSize().y)
		SetPosition({ GetPosition().x, cameraPosition.y + Engine::GetWindow().GetSize().y });

	if (explosionSprite.GetCurrentAnim() == static_cast<int>(Explosion_Anim::Explode_Anim))
	{
		explosionSprite.Update(dt);
	}
}
void Runner::Draw(math::TransformMatrix cameraMatrix)
{
	if (drawRunner == true)
	{
		CS230::Sprite* spritePtr = GetGOComponent<CS230::Sprite>();
		math::TransformMatrix displayMatrix = cameraMatrix * GetMatrix() * math::RotateMatrix{ rotation };

		if (spritePtr != nullptr)
			spritePtr->Draw(displayMatrix);
	}

	if (explosionSprite.GetCurrentAnim() == static_cast<int>(Explosion_Anim::Explode_Anim))
	{
		if(explosionSprite.IsAnimationDone() == true)
			explosionSprite.PlayAnimation(static_cast<int>(Explosion_Anim::None_Anim));
		else
			explosionSprite.Draw(cameraMatrix * GetMatrix() * math::ScaleMatrix({ 3.5, 3.5 }));
	}

#ifdef _DEBUG
	// Show Collision
	if (Engine::GetGSComponent<ShowCollision>()->IsEnabled()
		&& GetGOComponent<CS230::Collision>() != nullptr)
		GetGOComponent<CS230::Collision>()->Draw(cameraMatrix);
#endif
}

// Object Type & CanCollideWith
GameObjectType Runner::GetObjectType()
{
	return GameObjectType::Runner;
}
std::string Runner::GetObjectTypeName()
{
	return "Runner";
}
bool Runner::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Police || objectBType == GameObjectType::Spike 
		|| objectBType == GameObjectType::Finish)
		return true;
	else
		return false;
}

// Resolve Collision
void Runner::ResolveCollision(CS230::GameObject* objectB)
{
	if (CanCollideWith(objectB->GetObjectType()) == true)
	{
		switch (objectB->GetObjectType())
		{
		case GameObjectType::Police:

			if (hurtTimer <= 0)
			{
				hurtTimer = hurtTime;
				Engine::GetGSComponent<Hp>()->MinusHp(20);
				isDead = Engine::GetGSComponent<Hp>()->IsDead();
				if (isDead == true)
				{
					explosionSprite.PlayAnimation(static_cast<int>(Explosion_Anim::Explode_Anim));
					RemoveGOComponent<CS230::Collision>();
				}
			}
			break;

		case GameObjectType::Spike:

			if (hurtTimer <= 0)
			{
				hurtTimer = hurtTime;
				Engine::GetGSComponent<Hp>()->MinusHp(10);
				isDead = Engine::GetGSComponent<Hp>()->IsDead();
				if (isDead == true)
				{
					explosionSprite.PlayAnimation(static_cast<int>(Explosion_Anim::Explode_Anim));
					RemoveGOComponent<CS230::Collision>();
				}
			}
			break;

		case GameObjectType::Finish:
			Mode3::gameClear = true;
			RemoveGOComponent<CS230::Collision>();
			break;
		}
		
	}
}