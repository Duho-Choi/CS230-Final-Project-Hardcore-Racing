/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.h
Project: CS230
Author: Kevin Wright
Creation date: 2/12/2021
-----------------------------------------------------------------*/
#pragma once

#include "Rect.h"
#include "Component.h"

namespace math {
    class TransformMatrix;
}

namespace CS230 {
    class GameObject;

    class Collision : public Component {
    public:
        enum class CollideType {
            Rect_Collide,
            Circle_Collide,
        };
        virtual void Draw(math::TransformMatrix cameraMatrix) = 0;
        virtual CollideType GetCollideType() = 0;

        virtual bool DoesCollideWith(GameObject* objectB) = 0;
        virtual bool DoesCollideWith(math::vec2 point) = 0;

    };

    class RectCollision : public Collision {
    public:
        RectCollision(math::irect2 rect, GameObject* objectPtr) : rect(rect), objectPtr(objectPtr) {}
        void Draw(math::TransformMatrix cameraMatrix) override;
        CollideType GetCollideType() override { return Collision::CollideType::Rect_Collide; };
        math::rect2 GetWorldCoorRect();

        bool DoesCollideWith(GameObject* objectB) override;
        virtual bool DoesCollideWith(math::vec2 point);

    private:
        GameObject* objectPtr;
        math::irect2 rect;
    };

    class CircleCollision : public Collision {
    public:
        CircleCollision(double radius, GameObject* objectPtr) : radius(radius), objectPtr(objectPtr) {}
        void Draw(math::TransformMatrix cameraMatrix) override;
        CollideType GetCollideType() override { return Collision::CollideType::Circle_Collide; };
        double GetRadius();

        bool DoesCollideWith(GameObject* objectB) override;
        virtual bool DoesCollideWith(math::vec2 point);

    private:
        GameObject* objectPtr;
        double radius;
    };
}