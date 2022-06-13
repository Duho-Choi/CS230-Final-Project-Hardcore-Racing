
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "Police.h"
#include "Mode3.h"
#include "Score.h"
#include "GameObjectTypes.h"
#include "Police_Anims.h"
#include "Explosion_Anims.h"

Police::Police(GameObject* player, math::vec2 startPos)
	: player(player), GameObject(startPos, 0, { 0.6, 0.6 })
{
	AddGOComponent(new CS230::Sprite("Assets/Mode3/Police.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Police_Anim::Siren_Anim));
	explosionSprite.PlayAnimation(static_cast<int>(Explosion_Anim::None_Anim));
}
void Police::Update(double dt)
{
	GameObject::Update(dt);

	if (explosionSprite.GetCurrentAnim() == static_cast<int>(Explosion_Anim::Explode_Anim))
	{
		if (explosionSprite.IsAnimationDone() == true)
		{
			SetShouldBeDestroyed(true);
		}
	}

	math::vec2 facingVector = (math::RotateMatrix(GetRotation()) * math::vec2{ 0,1 }).Normalize();
	math::vec2 playerVector = (player->GetPosition() - GetPosition()).Normalize();



	if (facingVector.Cross(playerVector) > 0.05)
	{
		UpdateRotation(1.5 * dt);
	}
	else if (facingVector.Cross(playerVector) < -0.05)
	{
		UpdateRotation(-1.5 * dt);
	}
//if (facingVector.Cross(playerVector) <= -0.05)
//{
//	UpdateRotation(-rotationRate * dt);
//}
//	UpdateVelocity(math::RotateMatrix(GetRotation()) * math::vec2{ 0,accel * dt });
//}
//UpdateVelocity(-(GetVelocity() * drag * dt));

	UpdateVelocity(-GetVelocity() * Police::drag * dt);
	UpdatePosition({ GetVelocity().x * dt, (Mode3::speed + GetVelocity().y) * dt });
}

void Police::Draw(math::TransformMatrix cameraMatrix)
{
	CS230::Sprite* spritePtr = GetGOComponent<CS230::Sprite>();
	math::TransformMatrix displayMatrix = cameraMatrix * GetMatrix();

	if (spritePtr != nullptr)
		spritePtr->Draw(displayMatrix);
	
	if (explosionSprite.GetCurrentAnim() == static_cast<int>(Explosion_Anim::Explode_Anim))
	{
		if (explosionSprite.IsAnimationDone() == true)
			explosionSprite.PlayAnimation(static_cast<int>(Explosion_Anim::None_Anim));
		else
			explosionSprite.Draw(cameraMatrix * GetMatrix() * math::ScaleMatrix({ 3.5, 3.5 }));
	}
}

GameObjectType Police::GetObjectType()
{
	return GameObjectType::Police;
}
std::string Police::GetObjectTypeName()
{
	return "Police";
}
bool Police::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Police)
		return true;
	else
		return false;
}
void Police::ResolveCollision(CS230::GameObject* objectB)
{
	if (objectB != this)
	{
		if (CanCollideWith(objectB->GetObjectType()) == true)
		{
			// Add Score
			Engine::GetGSComponent<Score>()->AddScore(100);

			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Police_Anim::None_Anim));
			explosionSprite.PlayAnimation(static_cast<int>(Explosion_Anim::Explode_Anim));
			RemoveGOComponent<CS230::Collision>();
		}
	}
}