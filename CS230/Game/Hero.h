/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Duho Choi
Creation date: 3/22/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\GameObject.h"

class Hero : public CS230::GameObject
{
public:
    Hero(math::vec2 startPos);

    math::vec2 GetPosition() { return GameObject::GetPosition(); }

    void Draw(math::TransformMatrix displayMatrix);
    void Update(double dt);

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;

    bool IsDead() { return isDead; }

private:   
    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey jumpKey;

    static constexpr double acceleration{ 400 };
    static constexpr double drag{ 800 };
    static constexpr double maxVelocity{ 800 };
    static constexpr double jumpVelocity{ 850 };

    static constexpr double hurtTime = 2;

    double hurtTimer;
    bool drawHero;
    bool isDead;

    GameObject* standingOnObject{ nullptr };

private:
    class State_Idle : public State {
    public:
        void Enter(GameObject* object) override;
        void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Skidding : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Skidding"; }
    };
    class State_Jumping : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Falling : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };
    State_Idle stateIdle;
    State_Running stateRunning;
    State_Skidding stateSkidding;
    State_Jumping stateJumping;
    State_Falling stateFalling;

    void UpdateXVelocity(double dt);     //Change X velocity stuff
};