
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "..\Engine\Camera.h"
#include "..\Engine\GameObjectManager.h"
#include "Background.h"

class Runner;

class Mode3 : public CS230::GameState {
public:
	static constexpr int speed = 1000;
	static constexpr int finish_line = 100000;
	static inline int policeCount = 0;
	static inline bool gameClear = false;

	Mode3();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode 3"; }

	void DecrementPolice() { policeCount--; }
private:
	Runner* runnerPtr{ nullptr };

	CS230::InputKey mainMenu;
	CS230::InputKey modeReload;

	CS230::Texture GameOverTexture;
	CS230::Texture GameClearTexture;
	CS230::Texture RestartTexture;

	static constexpr int maxPoliceCount = 3;
	static constexpr double policeTime = 5;
	double policeTimer;
};