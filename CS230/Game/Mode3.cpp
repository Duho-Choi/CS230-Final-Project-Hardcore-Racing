
#include "../Engine/Engine.h"	//GetGameStateManager
#include "../Engine/ShowCollision.h"
#include "Mode3.h"
#include "Runner.h"
#include "Police.h"
#include "Spike.h"
#include "Fonts.h"
#include "Score.h"
#include "Screens.h"
#include "Finish.h"
#include "GameParticles.h"
#include "Hp.h"
#include "Mode3_background.h"

Mode3::Mode3() 
	: modeReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape),
	policeTimer(2)
{}

void Mode3::Load()
{
	// Reset Game clear
	gameClear = false; 
	policeTimer = 2;
	policeCount = 0;

	// Add GameObjectManager
	AddGSComponent(new CS230::GameObjectManager);

	// Add GameObjects to GameObjectManager
	CS230::GameObjectManager* gameObjectManagerPtr = GetGSComponent<CS230::GameObjectManager>(); 
	runnerPtr = new Runner(math::vec2{ Engine::GetWindow().GetSize() / 2 });
	gameObjectManagerPtr->Add(runnerPtr);

	int spike_x{ 0 };
	int spike_y{ 0 };
	for (int i = 0; i < 15; i++)
	{
		spike_y = rand() % finish_line;
		
		if (spike_y % 2 == 0)
			spike_x = 430;
		else spike_x = 1010;

		gameObjectManagerPtr->Add(new Spike(math::ivec2{ spike_x, spike_y }));
	}
	gameObjectManagerPtr->Add(new Finish(math::ivec2{ Engine::GetWindow().GetSize().x / 2, finish_line - 500 } ));

	// backgroundPtr
	AddGSComponent(new Mode3_background("Assets/Mode3/background_track.jpg"));

	CS230::Camera* cameraPtr = new CS230::Camera({});
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0, 0 }, { 0, finish_line - Engine::GetWindow().GetSize().y }});

	// Add Fonts
	// Score
	AddGSComponent(new Score{ 0, Fonts::Font1 });
	// Hp
	AddGSComponent(new Hp{ 100, Fonts::Font1 });
	// Game Over
	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	GameClearTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Game Clear! Congratulations!", 0x00FFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);

	// Add Particle
	AddGSComponent(new DustEmitter());
	
	// if Debug, Add ShowCollision
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode3::Update(double dt)
{
	GetGSComponent<CS230::GameObjectManager>()->Update(dt);
	GetGSComponent<CS230::Camera>()->Mode3_Update(dt, Mode3::speed);
	GetGSComponent<Mode3_background>()->Update(GetGSComponent<CS230::Camera>()->GetPosition());

	// Spawn Police
	policeTimer -= dt;
	CS230::GameObjectManager* gameObjectManagerPtr = GetGSComponent<CS230::GameObjectManager>();
	if (gameClear == false)
	{
		if (policeCount < maxPoliceCount)
		{
			if (policeTimer < 0)
			{
				policeTimer = policeTime;
				gameObjectManagerPtr->Add(new Police(runnerPtr,
					math::vec2{ static_cast<double>(rand() % Engine::GetWindow().GetSize().x), runnerPtr->GetPosition().y - 1000 }));
				policeCount++;
			}
		}
	}


	// @ Modify update to player Ptr
	//GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#if _DEBUG
	// mode Reload
	if (modeReload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
	// Update ShowCollision
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
}

void Mode3::Draw()
{	
	// Background / Camera
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	GetGSComponent<Mode3_background>()->Draw(math::vec2{0, 0} - cameraPtr->GetPosition());

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	if (runnerPtr->IsDead() == false)
	{
		GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 5 });
	}
	else if (runnerPtr->IsDead() == true)
	{
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, 
			winSize.y / 2 + GameOverTexture.GetSize().y / 2 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - RestartTexture.GetSize().x / 2, 
			winSize.y / 2 - RestartTexture.GetSize().y / 2 }));
	}

	// GameObjectManager
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(cameraMatrix);

	// Draw Fonts
	// Score & Hp
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 5 });
	GetGSComponent<Hp>()->Draw(math::ivec2{ winSize.x - 10, winSize.y - 5 });
}
void Mode3::Unload()
{
	runnerPtr = nullptr;
	ClearGSComponent();
}