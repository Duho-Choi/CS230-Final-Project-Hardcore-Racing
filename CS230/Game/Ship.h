/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Duho Choi
Creation date: 3/22/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\GameObject.h"

class Ship : public CS230::GameObject
{
public:
    Ship(math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType objectBType) override; 
    void ResolveCollision(CS230::GameObject* objectB) override;

    bool IsDead() { return isDead; }

private:
    CS230::Sprite leftFlameSprite{ "Assets/flame.spt", this };
    CS230::Sprite rightFlameSprite{ "Assets/flame.spt", this };

    CS230::InputKey rotateCounterKey;
    CS230::InputKey rotateClockKey;
    CS230::InputKey accelerateKey;
    CS230::InputKey laserKey;
    bool wasAccelKeyPressed{ false };
    bool wasLaserKeyPressed{ false };

    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;

    bool isDead;
};
