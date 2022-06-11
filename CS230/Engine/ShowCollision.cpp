/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShowCollision.cpp
Project: CS230
Author: Duho Choi
Creation date: 5/9/2022
-----------------------------------------------------------------*/
#include "ShowCollision.h"

ShowCollision::ShowCollision(CS230::InputKey::Keyboard keyToUse)
    : showCollisionKey(keyToUse), enabled(false) {}

void ShowCollision::Update(double)
{
    if (showCollisionKey.IsKeyReleased() == true)
    {
        if (enabled == false)
            enabled = true;
        else
            enabled = false;
    }
}
bool ShowCollision::IsEnabled()
{
    return enabled;
}
