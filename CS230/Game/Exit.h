/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Exit.h
Project: CS230
Author: Kevin Wright
Creation date: 2/20/2021
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

namespace math {
    struct irect2;
}

class Exit : public CS230::GameObject {
public:
    Exit(math::irect2 rect);
    void ResolveCollision(GameObject* objectA) override;
    std::string GetObjectTypeName() { return "Exit"; }
private:
    virtual GameObjectType GetObjectType() override { return GameObjectType::Trigger; }
};