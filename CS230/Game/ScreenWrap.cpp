/*--------------------------------------------------------------
Copyright(C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.cpp
Project: CS230
Author: Duho Choi
Creation date: 5/09/2022
-----------------------------------------------------------------*/
#include "ScreenWrap.h"
#include "..\Engine\Engine.h"
#include "..\Engine\GameObject.h"

void ScreenWrap::Update([[maybe_unused]] double dt)
{
	CS230::Sprite* spritePtr = object.GetGOComponent<CS230::Sprite>();
	if (object.GetPosition().x > Engine::GetWindow().GetSize().x + spritePtr->GetFrameSize().x / 2.0)
		object.SetPosition({ 0 - spritePtr->GetFrameSize().x / 2.0, object.GetPosition().y });
	if (object.GetPosition().x < 0 - spritePtr->GetFrameSize().x / 2.0)
		object.SetPosition({ Engine::GetWindow().GetSize().x + spritePtr->GetFrameSize().x / 2.0, object.GetPosition().y });
	if (object.GetPosition().y > Engine::GetWindow().GetSize().y + spritePtr->GetFrameSize().y / 2.0)
		object.SetPosition({ object.GetPosition().x, -spritePtr->GetFrameSize().y / 2.0 });
	if (object.GetPosition().y < 0 - spritePtr->GetFrameSize().y / 2.0)
		object.SetPosition({ object.GetPosition().x, Engine::GetWindow().GetSize().y + spritePtr->GetFrameSize().y / 2.0 });
}
