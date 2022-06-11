/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode2.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/12/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "../Engine/ShowCollision.h"
#include "Screens.h"
#include "Mode2.h"
#include "Ship.h"
#include "Fonts.h"
#include "Meteor.h"
#include "Score.h"
#include "GameParticles.h"

Mode2::Mode2()
	: mainMenu(CS230::InputKey::Keyboard::Escape), modeReload(CS230::InputKey::Keyboard::R) {}
void Mode2::Load() {
	// Add GameObjectManager
	AddGSComponent(new CS230::GameObjectManager);

	// Add GameObjects
	CS230::GameObjectManager* gameObjectManagerPtr = GetGSComponent<CS230::GameObjectManager>();
	shipPtr = new Ship({ static_cast<math::vec2>(Engine::GetWindow().GetSize() / 2) });
	gameObjectManagerPtr->Add(new Meteor());
	gameObjectManagerPtr->Add(new Meteor());
	gameObjectManagerPtr->Add(new Meteor());
	gameObjectManagerPtr->Add(new Meteor());
	gameObjectManagerPtr->Add(new Meteor());
	gameObjectManagerPtr->Add(new Meteor());
	gameObjectManagerPtr->Add(shipPtr);

	// Add Fonts
	AddGSComponent(new Score(0, Fonts::Font2));
	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);

	// Add ShowCollision
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

	// Add ParticleEmitter (HitEmitter, MeteorBitEmitter)
	AddGSComponent(new HitEmitter());
	AddGSComponent(new MeteorBitEmitter());
}
void Mode2::Update(double dt) {

	// Update GameObjectManager
	GetGSComponent<CS230::GameObjectManager>()->Update(dt);

	// Update ShowCollision
#ifdef _DEBUG
	GetGSComponent<ShowCollision>()->Update(dt);
#endif

	if (mainMenu.IsKeyReleased()) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#if _DEBUG
	if (modeReload.IsKeyReleased()) {
		Engine::GetGameStateManager().ReloadState();
	}
#else
	if (shipPtr->IsDead() == true)
	{
		if (modeReload.IsKeyReleased()) {
			Engine::GetGameStateManager().ReloadState();
		}
	}
#endif
}
void Mode2::Draw(){
	Engine::GetWindow().Clear(0x000000FF);
	math::TransformMatrix cameraMatrix = math::TransformMatrix();
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(cameraMatrix);

	// Draw Fonts
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y });

	// If ship is dead, draw GameOver & Restart Texture
	if (shipPtr->IsDead() == true)
	{
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y / 2 + GameOverTexture.GetSize().y / 2 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - RestartTexture.GetSize().x / 2, winSize.y / 2 - RestartTexture.GetSize().y / 2 }));
	}
}
void Mode2::Unload() {
	ClearGSComponent();
}
