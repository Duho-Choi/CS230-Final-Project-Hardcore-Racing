/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.h
Project: CS230
Author: Duho Choi
Creation date: 3/13/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "..\Engine\Texture.h"

class Splash : public CS230::GameState {
public:
	Splash();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;    
	void Draw() override;

	std::string GetName() override { return "Splash"; }
private:
	double elapsedTime = 0;
	CS230::Texture* texturePtr{ nullptr };
};