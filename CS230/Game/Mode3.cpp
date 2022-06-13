/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3.cpp
Project: CS230
Author: Minsu Kim
Creation date: 6/9/2022
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"	//GetGameStateManager
#include "..\Engine\ShowCollision.h"
#include "Screens.h"
#include "Mode3.h"
#include "Fonts.h"
#include "Score.h"

Mode3::Mode3() :
	modeMain(CS230::InputKey::Keyboard::Escape), modeReload(CS230::InputKey::Keyboard::R)
{}

void Mode3::Load()
{
#if _DEBUG
	// ShowCollision
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

	// score
	AddGSComponent(new Score{ 0, Fonts::Font1 });

	// Gameobject
	AddGSComponent(new CS230::GameObjectManager);

	gameObjectManagerPtr = GetGSComponent<CS230::GameObjectManager>();

	// backgroundPtr
	backgroundPtr = Engine::GetTextureManager().Load("Assets/Mode3/background_track.jpg");

	// cameraPtr
	// @ Change new camera extent, position, movableRange
	CS230::Camera* cameraPtr = new CS230::Camera((math::rect2{ math::vec2(Engine::GetWindow().GetSize().x / 100.0 * 15, 0),
math::vec2(Engine::GetWindow().GetSize().x / 100.0 * 35, Engine::GetWindow().GetSize().y) }));
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent(math::irect2{ math::ivec2(0, 0),
	math::ivec2(backgroundPtr->GetSize().x - Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y) });
}

void Mode3::Update(double dt)
{
	gameObjectManagerPtr->Update(dt);

	// @ Modify update to player Ptr
	//GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());

	if (modeMain.IsKeyReleased()) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}

#if _DEBUG
	if (modeReload.IsKeyReleased()) {
		Engine::GetGameStateManager().ReloadState();
	}

	GetGSComponent<ShowCollision>()->Update(dt);
#endif
}

void Mode3::Unload() {
	ClearGSComponent();
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x6495edFF);
	backgroundPtr->Draw(math::TranslateMatrix((Engine::GetWindow().GetSize() - backgroundPtr->GetSize()) / 2));

	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();

	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();

	gameObjectManagerPtr->DrawAll(cameraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 5 });


}