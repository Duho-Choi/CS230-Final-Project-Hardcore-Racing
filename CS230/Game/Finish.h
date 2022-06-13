#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Finish : public CS230::GameObject {
public:
    Finish(math::ivec2 startPos);
    std::string GetObjectTypeName() override { return "Finish"; }
    GameObjectType GetObjectType() override { return GameObjectType::Finish; }
private:
};