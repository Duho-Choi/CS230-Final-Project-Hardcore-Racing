/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/13/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Splash.h"

Splash::Splash()
	: texturePtr(Engine::GetTextureManager().Load("Assets/DigiPen_BLACK_1024px.png")) {}

void Splash::Load() {
	
}
void Splash::Update(double dt) {
	if (elapsedTime > 3) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	elapsedTime += dt;
}
void Splash::Draw() {
	Engine::GetWindow().Clear(0xFFFFFFFF);
	texturePtr->Draw(math::TranslateMatrix((Engine::GetWindow().GetSize() - texturePtr->GetSize()) / 2));
}
void Splash::Unload() {
}
