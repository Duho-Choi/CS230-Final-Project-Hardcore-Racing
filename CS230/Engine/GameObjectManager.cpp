/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/28/2022
-----------------------------------------------------------------*/
#include "Engine.h"		// GetLogger()
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collision.h"
#include "TransformMatrix.h"

CS230::GameObjectManager::~GameObjectManager()
{	
	for (GameObject* gameObject : gameObjects)
	{
 		delete gameObject;
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void CS230::GameObjectManager::Update(double dt)
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->Update(dt);
	}
	for (GameObject* gameObject : gameObjects)
	{
		if (gameObject->GetShouldBeDestroyed() == true)
		{
 			destroyList.push_back(gameObject);
		}
	}
	for (GameObject* deleteObject : destroyList)
	{
		gameObjects.remove(deleteObject);
		delete deleteObject;
	}
	destroyList.clear();

	CollideTest();
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->Draw(cameraMatrix);
	}
}

void CS230::GameObjectManager::CollideTest()
{
// Todo: This should go through all the gameObjects(objectA) and compare every other object(objectB).
// Yes, we will even compare objects against themselves Check if objectA can collide with objectB, 
// if so then test if objectA does collide with objectB, if so, log an event to say 
// "Collision Detected: " objectA type " and " objectB type

	for (GameObject* objectA : gameObjects)
	{
		for (GameObject* objectB : gameObjects)
		{
			if (objectA->CanCollideWith(objectB->GetObjectType()) == true)
			{
				if (objectA->GetGOComponent<Collision>() != nullptr && objectB->GetGOComponent<Collision>() != nullptr)
				{
					if (objectA->DoesCollideWith(objectB) == true)
					{
						if (objectA != objectB)
						{
							Engine::GetLogger().LogEvent("Collision Detected: " + objectA->GetObjectTypeName()
								+ " and " + objectB->GetObjectTypeName());
							objectA->ResolveCollision(objectB);
						}
					}
				}
			}
			
		}
	}
}