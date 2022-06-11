/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.h
Project: CS230
Author: Duho Choi
Creation date: 4/29/2022
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject.h"

class Bunny : public CS230::GameObject 
{
public:
	Bunny(math::vec2 pos);

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;        
    void ResolveCollision(GameObject* objectA) override;

private:
};
