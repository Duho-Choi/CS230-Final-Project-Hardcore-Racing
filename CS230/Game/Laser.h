/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.h
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class GameObjectManager;
enum class GameObjectType;

class Laser : public CS230::GameObject {
public:
    static constexpr math::vec2 LaserVelocity = math::vec2{ 0, 600 };

    Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity);
    void Update(double dt) override;
    std::string GetObjectTypeName() { return "Laser"; }
    virtual GameObjectType GetObjectType() override { return GameObjectType::Laser; }
    virtual bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;
private:
};