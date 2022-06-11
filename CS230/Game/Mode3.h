/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3.h
Project: CS230
Author: Minsu Kim
Creation date: 6/9/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "..\Engine\Camera.h"
#include "..\Engine\GameObjectManager.h"
#include "Background.h"


class Mode3 : public CS230::GameState {
public:
	Mode3();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode 3"; }
private:
	CS230::InputKey modeMain;
	CS230::InputKey modeReload;

	CS230::GameObjectManager* gameObjectManagerPtr;

	Background* backgroundPtr;
};