/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.h
Project: CS230
Author: Duho Choi
Creation date: 3/13/2022
-----------------------------------------------------------------*/
#include "Input.h"
#include "Engine.h"

CS230::InputKey::InputKey(Keyboard button)
	: button(button)
{
}
bool CS230::InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(button);
}
bool CS230::InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(button);
}

CS230::Input::Input()
{
	keyDown.resize(static_cast<int>(CS230::InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<int>(CS230::InputKey::Keyboard::Count));
}
void CS230::Input::Update()
{
	wasKeyDown = keyDown;
}
bool CS230::Input::IsKeyDown(InputKey::Keyboard key) const
{
	return keyDown[static_cast<int>(key)];
}
bool CS230::Input::IsKeyReleased(InputKey::Keyboard key) const
{
	return (wasKeyDown[static_cast<int>(key)] && keyDown[static_cast<int>(key)] == false);
}
void CS230::Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}