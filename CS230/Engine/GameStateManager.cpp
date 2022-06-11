/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Project: CS230
Author: Duho Choi
Creation date: 3/12/2022
-----------------------------------------------------------------*/

#include "GameState.h"
#include "GameStateManager.h"
#include "engine.h"

CS230::GameStateManager::GameStateManager()
	: state(CS230::GameStateManager::State::START), currGameState(nullptr), nextGameState(nullptr)
{
}
void CS230::GameStateManager::AddGameState(GameState& gameState)
{
	gameStates.push_back(&gameState);
}
void CS230::GameStateManager::Update(double dt)
{
	switch (state)
	{
	case CS230::GameStateManager::State::START:
		if (gameStates.empty() == true)
		{
			Engine::GetLogger().LogError("No gameStates in vector");
			state = CS230::GameStateManager::State::SHUTDOWN;
		}
		else
		{
			nextGameState = gameStates[0];
			state = CS230::GameStateManager::State::LOAD;
		}
		break;

	case CS230::GameStateManager::State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		state = CS230::GameStateManager::State::UPDATE;
		break;

	case CS230::GameStateManager::State::UPDATE:
		if (nextGameState != currGameState)
			state = CS230::GameStateManager::State::UNLOAD;
		else
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());

		currGameState->Update(dt);
		currGameState->Draw();
		break;
			
	case CS230::GameStateManager::State::UNLOAD:
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		currGameState->Unload();

		// Unload Texture when going different game state
		if(nextGameState != currGameState)
			Engine::GetTextureManager().Unload();

		if (nextGameState == nullptr)
			state = CS230::GameStateManager::State::SHUTDOWN;
		else
			state = CS230::GameStateManager::State::LOAD;
		break;

	case CS230::GameStateManager::State::SHUTDOWN:
		state = CS230::GameStateManager::State::EXIT;
		break;

	case CS230::GameStateManager::State::EXIT:
		break;
	}
}
void CS230::GameStateManager::SetNextState(int initState)
{
	nextGameState = gameStates[initState];
}
void CS230::GameStateManager::Shutdown()
{
	nextGameState = nullptr;
}
void CS230::GameStateManager::ReloadState()
{
	state = CS230::GameStateManager::State::UNLOAD;
}