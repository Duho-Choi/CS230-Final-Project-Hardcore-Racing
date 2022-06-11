/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode2.h
Project: CS230
Author: Duho Choi
Creation date: 3/12/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"

class Ship;

class Mode2 : public CS230::GameState
{
public:
	Mode2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode 2"; }

private:
	Ship* shipPtr{ nullptr };

	CS230::InputKey modeReload;
	CS230::InputKey mainMenu;

	CS230::Texture GameOverTexture;
	CS230::Texture RestartTexture;
};
