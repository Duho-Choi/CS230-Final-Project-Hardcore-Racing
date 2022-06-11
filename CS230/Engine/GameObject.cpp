/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/29/2022
-----------------------------------------------------------------*/
#include "GameObject.h"
#include "Collision.h"
#include "ShowCollision.h"
#include "Engine.h"

#include <doodle/doodle.hpp>

CS230::GameObject::GameObject() : GameObject({ 0, 0 }, 0, { 1, 1 }) {}

CS230::GameObject::GameObject(math::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

CS230::GameObject::GameObject(math::vec2 position, double rotation, math::vec2 scale)
    : velocity{ 0,0 }, position(position), updateMatrix(true), shouldBeDestroyed(false),
    scale(scale), rotation(rotation), currState(&state_nothing) {
}

CS230::GameObject::~GameObject()
{
    ClearGOComponents();
}

void CS230::GameObject::Update(double dt) {
    currState->Update(this, dt);    
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
    UpdateGOComponents(dt);
    currState->TestForExit(this);
}

void CS230::GameObject::Draw(math::TransformMatrix displayMatrix) {
    Sprite* spritePtr = GetGOComponent<Sprite>();
    if (spritePtr != nullptr)
        spritePtr->Draw(displayMatrix * GetMatrix());

#ifdef _DEBUG
    // Show Collision
    if(Engine::GetGSComponent<ShowCollision>()->IsEnabled()
        && GetGOComponent<CS230::Collision>() != nullptr)
        GetGOComponent<CS230::Collision>()->Draw(displayMatrix);
#endif
}

const math::TransformMatrix& CS230::GameObject::GetMatrix() {
    if (updateMatrix == true) {
        objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix(scale);
        updateMatrix = false;
    }
    return objectMatrix;
}

void CS230::GameObject::SetPosition(math::vec2 newPosition) {
    position = newPosition;
    updateMatrix = true;
}

void CS230::GameObject::SetVelocity(math::vec2 newVelocity) {
    velocity = newVelocity;
}

void CS230::GameObject::UpdatePosition(math::vec2 adjustPosition) {
    position += adjustPosition;
    updateMatrix = true;
}

const math::vec2& CS230::GameObject::GetPosition() const { return position; }

math::vec2& CS230::GameObject::GetVelocity()
{
    return velocity;
}

const math::vec2& CS230::GameObject::GetScale() const
{
    return scale;
}

double CS230::GameObject::GetRotation() const
{
    return rotation;
}

void CS230::GameObject::UpdateVelocity(math::vec2 adjustPosition)
{
    velocity += adjustPosition;
}

void CS230::GameObject::SetScale(math::vec2 newScale)
{
    scale = newScale;
    updateMatrix = true;
}

void CS230::GameObject::SetRotation(double newRotationAmount)
{
    rotation = newRotationAmount;
    updateMatrix = true;
}

void CS230::GameObject::UpdateRotation(double newRotationAmount)
{
    rotation += newRotationAmount;
    updateMatrix = true;
}

void CS230::GameObject::ChangeState(State* newState) {
    currState = newState;
    currState->Enter(this);
}

// Collision Functions
bool CS230::GameObject::CanCollideWith(GameObjectType)
{
// Todo: create the CanCollideWith base game function
// This is the function that will decide if an object of type 
// objectA(this object) can collide with an object of type objectB(objectBType)
// for our base game object we this should return false
    return false;
}
bool CS230::GameObject::DoesCollideWith(GameObject* objectB)
{
    return GetGOComponent<Collision>()->DoesCollideWith(objectB);
}
bool CS230::GameObject::DoesCollideWith(math::vec2 point)
{
    return GetGOComponent<Collision>()->DoesCollideWith(point);
}
void CS230::GameObject::ResolveCollision(GameObject*)
{
    Engine::GetLogger().LogError("Base class ResolveCollision Called");
}
void CS230::GameObject::SetShouldBeDestroyed(bool canBeDestroyed)
{
    shouldBeDestroyed = canBeDestroyed;
}