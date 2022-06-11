/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/12/2021
-----------------------------------------------------------------*/
#include "Collision.h"
#include "TransformMatrix.h"
#include "GameObject.h"
#include "doodle/drawing.hpp"
#include "Camera.h"
#include "Engine.h"

void CS230::RectCollision::Draw(math::TransformMatrix cameraMatrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    math::rect2 displayRect = GetWorldCoorRect();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_rectangle(displayRect.Left(), displayRect.Bottom(), displayRect.Size().x, displayRect.Size().y);
    doodle::pop_settings();
}
bool CS230::RectCollision::DoesCollideWith(GameObject* objectB)
{
    if (GetWorldCoorRect().Left() < objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Right()
        && GetWorldCoorRect().Right() > objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Left()
        && GetWorldCoorRect().Bottom() < objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Top()
        && GetWorldCoorRect().Top() > objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Bottom())
    {
        return true;
    }
    else return false;
}
math::rect2 CS230::RectCollision::GetWorldCoorRect()
{
    return { objectPtr->GetMatrix() * static_cast<math::vec2>(rect.point1),
        objectPtr->GetMatrix() * static_cast<math::vec2>(rect.point2) };
}
bool CS230::RectCollision::DoesCollideWith(math::vec2 point)
{
    if (GetWorldCoorRect().Left() < point.x && GetWorldCoorRect().Right() > point.x
        && GetWorldCoorRect().Bottom() < point.y && GetWorldCoorRect().Top() > point.y)
    {
        return true;
    }
    else return false;
}

void CS230::CircleCollision::Draw(math::TransformMatrix cameraMatrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_ellipse(objectPtr->GetPosition().x, objectPtr->GetPosition().y, GetRadius() * 2);
    doodle::pop_settings();
}
bool CS230::CircleCollision::DoesCollideWith(GameObject* objectB)
{   
    if ((objectPtr->GetPosition().x - objectB->GetPosition().x) * (objectPtr->GetPosition().x - objectB->GetPosition().x)
        + (objectPtr->GetPosition().y - objectB->GetPosition().y) * (objectPtr->GetPosition().y - objectB->GetPosition().y)
        < (GetRadius() + objectB->GetGOComponent<CircleCollision>()->GetRadius()) * (GetRadius() + objectB->GetGOComponent<CircleCollision>()->GetRadius()))
    {
        return true;
    }
    else return false;
}
double CS230::CircleCollision::GetRadius()
{
    return (math::ScaleMatrix(objectPtr->GetScale()) * math::vec2{ radius, 0 }).x;
}
bool CS230::CircleCollision::DoesCollideWith(math::vec2 point)
{
    if ((objectPtr->GetPosition().x - point.x) * (objectPtr->GetPosition().x - point.x)
        + (objectPtr->GetPosition().y - point.y) * (objectPtr->GetPosition().y - point.y)
        < GetRadius() * GetRadius())
    {
        return true;
    }
    else return false;
}