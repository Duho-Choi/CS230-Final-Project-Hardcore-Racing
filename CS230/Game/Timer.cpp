/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.cpp
Project: CS230
Author: Duho Choi
Creation date: 5/09/2022
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"
#include "Timer.h"
#include "Fonts.h"

Timer::Timer(int time)
	: timer(time)
{
	std::string timeString = "Time: " + std::to_string(static_cast<int>(timer + 1));
	timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timeString, 0xFFFFFFFF, true);
}
void Timer::Update(double dt)
{
	timer -= dt;
	if (timer - static_cast<int>(timer) > 0)
	{
		std::string timeString = "Time: " + std::to_string(static_cast<int>(timer + 1));
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timeString, 0xFFFFFFFF, true);
	}
}
bool Timer::hasEnded()
{
	if (timer <= 0)
	{
		timer = 5;
		return true;
	}
	return false;
}
void Timer::Draw(math::ivec2 location)
{
	timeTexture.Draw(math::TranslateMatrix(math::ivec2{ location.x - timeTexture.GetSize().x, location.y - timeTexture.GetSize().y }));
}
