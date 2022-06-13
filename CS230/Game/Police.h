
#pragma once

#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\GameObject.h"

class Police : public CS230::GameObject
{
public:
    Police(GameObject* player, math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(CS230::GameObject* objectB) override;

private:
    GameObject* player;
    
    CS230::Sprite explosionSprite{ "Assets/Mode3/Explosion.spt", this };


    static constexpr int maxVelocity = 50;
    static constexpr double accel = 18;
    static constexpr float drag = 1.0f;

    static constexpr double rotationRate = 2;
};
