/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include <vector>
#include "GameState.h"

namespace CS230 {

	class GameStateManager {
	public:
		GameStateManager();

		void AddGameState(GameState& gameState);
		void Update(double dt);
		void SetNextState(int initState);
		void Shutdown();
		void ReloadState();
		bool HasGameEnded() { return state == State::EXIT; }
		
		template<typename T>
		T* GetGSComponent() { return currGameState->GetGSComponent<T>(); }

	private:
		enum class State {
			START,
			LOAD,
			UPDATE,
			UNLOAD,
			SHUTDOWN,
			EXIT,
		};

		std::vector<GameState*> gameStates;
		State state;
		GameState* currGameState;
		GameState* nextGameState;
	};
}