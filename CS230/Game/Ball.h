/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Duho Choi
Creation date: 3/25/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObject.h"

class Ball : public CS230::GameObject
{
public:
    Ball(math::vec2 startPos);

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;

private:
    class State_Bounce : public State {
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "bounce"; }
    };
    class State_Land : public State {
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "squish"; }
    };
    State_Bounce stateBounce;
    State_Land stateLand;

    static constexpr double bounceVelocity{ 640 };
};