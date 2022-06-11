/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Duho Choi
Creation date: 3/12/2022
-----------------------------------------------------------------*/
#include "Engine.h"

Engine::Engine() :
	frameCount(0), lastTick(std::chrono::system_clock::now()),
#ifdef _DEBUG				
	logger(CS230::Logger::Severity::Debug, true, lastTick)
#else 						
	logger(CS230::Logger::Severity::Event, false, lastTick)
#endif
{}

Engine::~Engine() {}

void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(windowName);
	fpsCalcTime = lastTick;

	seed = static_cast<int>(time(NULL));
	logger.LogEvent("Seed = " + std::to_string(seed));
	srand(seed);
}
void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
}
void Engine::Update()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();
	if (dt > 1 / Target_FPS)
	{
		lastTick = now;
		logger.LogVerbose("Engine Update");
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
		frameCount++;
		if (frameCount > FPS_IntervalFrameCount)
		{
			double averageFrameRate = frameCount / std::chrono::duration<double>(now - fpsCalcTime).count();
			logger.LogEvent("FPS:\t" + std::to_string(averageFrameRate));
			frameCount = 0;
			fpsCalcTime = now;
		}
	}
}

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();
}

void Engine::AddSpriteFont(const std::filesystem::path& fileName)
{
	fonts.push_back(CS230::SpriteFont{ fileName });
}