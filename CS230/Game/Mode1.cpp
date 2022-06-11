/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode1.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/12/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "../Engine/ShowCollision.h"
#include "Screens.h"
#include "Mode1.h"
#include "Hero.h"
#include "Ball.h"
#include "Bunny.h"
#include "TreeStump.h"
#include "Fonts.h"
#include "Background.h"
#include "Gravity.h"
#include "Score.h"
#include "Timer.h"
#include "Floor.h"
#include "Exit.h"
#include "GameParticles.h"

Mode1::Mode1() : modeReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape) {}

void Mode1::Load() {
	// Add GameObjectManager
	AddGSComponent(new CS230::GameObjectManager);

	CS230::GameObjectManager* gameObjectManagerPtr = GetGSComponent<CS230::GameObjectManager>();

	// Add GameObjects to GameObjectManager
	gameObjectManagerPtr->Add(new Ball({ 600, Mode1::floor }));
	gameObjectManagerPtr->Add(new Ball({ 2700, Mode1::floor }));
	gameObjectManagerPtr->Add(new Ball({ 4800, Mode1::floor }));
	gameObjectManagerPtr->Add(new Bunny({ 1000, Mode1::floor }));
	gameObjectManagerPtr->Add(new Bunny({ 2000, Mode1::floor }));
	gameObjectManagerPtr->Add(new Bunny({ 3200, Mode1::floor }));
	gameObjectManagerPtr->Add(new Bunny({ 3800, Mode1::floor }));
	gameObjectManagerPtr->Add(new TreeStump({ 300, Mode1::floor }, 3));
	gameObjectManagerPtr->Add(new TreeStump({ 1200, Mode1::floor }, 2));
	gameObjectManagerPtr->Add(new TreeStump({ 2200, Mode1::floor }, 1));
	gameObjectManagerPtr->Add(new TreeStump({ 2800, Mode1::floor }, 5));
	gameObjectManagerPtr->Add(new TreeStump({ 5100, Mode1::floor }, 5));
	gameObjectManagerPtr->Add(new Floor({ {0, 0}, {1471, static_cast<int>(Mode1::floor)} }));
	gameObjectManagerPtr->Add(new Floor({ {1602, 0}, {4262, static_cast<int>(Mode1::floor)} }));
	gameObjectManagerPtr->Add(new Floor({ {4551, 0}, {5760, static_cast<int>(Mode1::floor)} }));
	gameObjectManagerPtr->Add(new Exit({ {5550, static_cast<int>(Mode1::floor)}, {5760, 683} }));
	heroPtr = new Hero({ 100, Mode1::floor - 1 });
	gameObjectManagerPtr->Add(heroPtr);

	// Add Gravity
	AddGSComponent(new Gravity(1500));

	// Add Backgrounds
	AddGSComponent(new Background);
	Background* backgroundPtr = GetGSComponent<Background>();
	backgroundPtr->Add("Assets/clouds.png", 4);
	backgroundPtr->Add("Assets/Mountains.png", 2);
	backgroundPtr->Add("Assets/foreground.png", 1);

	// Add Camera
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 },
		{0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0, 0 }, { GetGSComponent<Background>()->Size() - Engine::GetWindow().GetSize() }});

	// Add Fonts
	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Timer(60));

	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);

	// Add ShowCollision
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

	// Add ParticleEmitter (SmokeEmitter)
	AddGSComponent(new SmokeEmitter());
}
void Mode1::Update(double dt) 
{
	GetGSComponent<CS230::GameObjectManager>()->Update(dt);
	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());
	
	if (mainMenu.IsKeyReleased() == true) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#if _DEBUG
	if (modeReload.IsKeyReleased() == true) 
	{		
		Engine::GetGameStateManager().ReloadState();
	}
#endif
	// Update ShowCollision
#if _DEBUG
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
	
	// Update timer and lives
	GetGSComponent<Timer>()->Update(dt);
	if (GetGSComponent<Timer>()->hasEnded() == true)
	{
		RemoveLife();
	}
}
void Mode1::Draw() 
{
	Engine::GetWindow().Clear(0x3399DAFF);
	GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
	math::TransformMatrix cameraMatrix = GetGSComponent<CS230::Camera>()->GetMatrix();
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(cameraMatrix);

	// Draw Fonts
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 5 });
	GetGSComponent<Timer>()->Draw((math::ivec2{winSize.x - 10, winSize.y - 5}));
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - livesTexture.GetSize().x / 2, winSize.y - livesTexture.GetSize().y - 5}));
}
void Mode1::Unload() 
{
	GetGSComponent<Background>()->Unload();
	heroPtr = nullptr;
	ClearGSComponent();
}
void Mode1::RemoveLife()
{
	lives--;
	if (lives <= 0)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		lives = 3;
	}
	else
		Engine::GetGameStateManager().ReloadState();
}