
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\GameObject.h"

class Spike : public CS230::GameObject
{
public:
    Spike(math::vec2 startPos);

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;

private:
};
