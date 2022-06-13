
#include "../Engine/Engine.h"	//GetGameStateManager
#include "../Engine/ShowCollision.h"
#include "Mode3.h"
#include "Runner.h"
#include "Police.h"
#include "Fonts.h"
#include "Score.h"
#include "Screens.h"
#include "GameParticles.h"

Mode3::Mode3() : modeReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape) {}

void Mode3::Load() {
	// Add GameObjectManager
	AddGSComponent(new CS230::GameObjectManager);

	// Add GameObjects to GameObjectManager
	CS230::GameObjectManager* gameObjectManagerPtr = GetGSComponent<CS230::GameObjectManager>(); 
	runnerPtr = new Runner({ 200, 200 });
	gameObjectManagerPtr->Add(runnerPtr);

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
	cameraPtr->SetExtent({ { 0, 0 }, { GetGSComponent<Background>()->Size() - Engine::GetWindow().GetSize() } });

	// Add Fonts
	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Game Over", 0x00FFFFFF, true);
	AddGSComponent(new Score(0, Fonts::Font1));
	ScoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Score : ", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);

	// Add Particle
	AddGSComponent(new DirtEmitter());
	
	// if Debug, Add ShowCollision
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

}
void Mode3::Update(double dt)
{
	GetGSComponent<CS230::GameObjectManager>()->Update(dt);

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

}
void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x50FF50FF);
	//GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
	math::TransformMatrix cameraMatrix = GetGSComponent<CS230::Camera>()->GetMatrix();
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(cameraMatrix);

	// Draw Fonts
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	
	if (runnerPtr->IsDead() == false)
	{
		GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 5 });
	}
	else if (runnerPtr->IsDead() == true)
	{
		//GetGSComponent<Score>()->Draw(math::ivec2{ winSize.x / 2 -  });
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y / 2 + GameOverTexture.GetSize().y / 2 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - RestartTexture.GetSize().x / 2, winSize.y / 2 - RestartTexture.GetSize().y / 2 }));
	}
}
void Mode3::Unload()
{
	GetGSComponent<Background>()->Unload();
	runnerPtr = nullptr;
	ClearGSComponent();
}
