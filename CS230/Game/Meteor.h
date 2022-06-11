/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.h
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"

class Meteor : public CS230::GameObject {
public:
	Meteor();    
	Meteor(Meteor& original);
	void Update(double dt) override;

	// Object Types
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override;

	void ResolveCollision(GameObject* objectB) override;

private:    
	int health;
	int size;
	static constexpr double PI{ 3.14 };
};