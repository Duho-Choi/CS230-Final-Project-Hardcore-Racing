
#pragma once

#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\GameObject.h"

class Runner : public CS230::GameObject
{
public:
    Runner(math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(CS230::GameObject* objectB) override;

    bool IsDead() { return isDead; }

private:
    CS230::Sprite explosionSprite{ "Assets/Mode3/Explosion.spt", this };

    CS230::InputKey frontKey;
    CS230::InputKey backKey;
    CS230::InputKey leftKey;
    CS230::InputKey rightKey;

    double rotation;

    static constexpr double left_right_accel = 600;
    static constexpr float maxRotation = 0.5f;
    static constexpr double accel = 600;
    static constexpr int maxVelocity = 1000;
    static constexpr float drag = 2.0f;
    static constexpr float hurtTime = 1.2f;

    double hurtTimer;
    bool drawRunner;
    bool isDead;
};
