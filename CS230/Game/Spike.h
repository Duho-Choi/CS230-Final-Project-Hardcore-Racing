
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Spike : public CS230::GameObject
{
public:
    Spike(math::ivec2 startPos);

    // Object Types
    GameObjectType GetObjectType() override { return GameObjectType::Spike; }
    std::string GetObjectTypeName() override { return "Spike"; }

private:
};
