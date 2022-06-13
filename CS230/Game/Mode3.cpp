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


	CS230::Camera* cameraPtr = new CS230::Camera({});
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0, 0 }, { backgroundPtr->GetSize() - Engine::GetWindow().GetSize()}});
}

void Mode3::Update(double dt)
{
	gameObjectManagerPtr->Update(dt);

	GetGSComponent<CS230::Camera>()->Mode3_Update(dt, Mode3::camera_speed);
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
	// Background / Camera
	Engine::GetWindow().Clear(0x6495edFF);
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();

	math::ivec2 background_vec = { (Engine::GetWindow().GetSize().x - backgroundPtr->GetSize().x) / 2, 0 };
	backgroundPtr->Draw(math::TranslateMatrix( static_cast<math::vec2>(background_vec) - cameraPtr->GetPosition() ) );
	
	// GameObjectManager
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManagerPtr->DrawAll(cameraMatrix);


	// Score
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 5 });


}