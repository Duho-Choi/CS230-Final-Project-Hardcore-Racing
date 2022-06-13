
#pragma once

#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\GameObject.h"

class Police : public CS230::GameObject
{
public:
    Police(math::vec2 startPos);
    void Update(double dt) override;
    //void Draw(math::TransformMatrix cameraMatrix) override;

    // Object Types
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(CS230::GameObject* objectB) override;

private:
    static constexpr double accel = 500;
    static constexpr double drag = 1.5f;

};
