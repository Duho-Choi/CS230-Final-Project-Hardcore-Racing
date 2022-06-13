#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

namespace math {
    struct irect2;
}

class Finish : public CS230::GameObject {
public:
    Finish(math::irect2 rect);
    std::string GetObjectTypeName() override { return "Finish"; }
    GameObjectType GetObjectType() override { return GameObjectType::Finish; }
private:
};