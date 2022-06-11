/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once
#include <list>

namespace math { class TransformMatrix; }

namespace CS230 {
	class GameObject;

	class GameObjectManager : public Component {
	public:
		~GameObjectManager();

		void Add(GameObject* obj);

		void Update(double dt) override;
		void DrawAll(math::TransformMatrix& cameraMatrix);

		void CollideTest();

		const std::list<GameObject*>& Objects() { return gameObjects; }

	private:
		std::list<GameObject*> gameObjects;
		std::list<GameObject*> destroyList;
	};
}