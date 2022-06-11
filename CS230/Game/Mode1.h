/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode1.h
Project: CS230
Author: Duho Choi
Creation date: 3/12/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "..\Engine\Camera.h"
#include "..\Engine\GameObjectManager.h"

class Hero;

class Mode1 : public CS230::GameState
{
public:    
	Mode1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode 1"; }

	static void RemoveLife();

private:
	static constexpr double floor = 126.0f;

	CS230::InputKey modeReload;
	CS230::InputKey mainMenu;
	Hero* heroPtr{ nullptr };

	static inline int lives{ 3 };
	CS230::Texture livesTexture;
};
