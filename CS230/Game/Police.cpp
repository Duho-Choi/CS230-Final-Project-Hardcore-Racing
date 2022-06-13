
#include "../Engine/Collision.h"
#include "Police.h"
#include "GameObjectTypes.h"
#include "Police_Anims.h"

Police::Police(math::vec2 startPos)
	: GameObject(startPos, 0, { 0.75, 0.75 })
{
	AddGOComponent(new CS230::Sprite("Assets/Mode3/Police.spt", this));
}
void Police::Update(double dt)
{
	GameObject::Update(dt);
	 
	if (GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Police_Anim::Explode_Anim))
	{
		if (GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
		{
			SetShouldBeDestroyed(true);
		}
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
	if (CanCollideWith(objectB->GetObjectType()) == true)
	{
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Police_Anim::Explode_Anim));
		RemoveGOComponent<CS230::Collision>();
	}
}