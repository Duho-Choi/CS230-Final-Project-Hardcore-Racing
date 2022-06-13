/*--------------------------------------------------------------
Copyright(C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hp.cpp
Project: CS230
Author: Minsu Kim
Creation date: 6/13/2022
-----------------------------------------------------------------*/

#include "..\Engine\Engine.h"
#include "Hp.h"
#include "Fonts.h"

Hp::Hp(int startingHp, Fonts fontToUse)
	: hp(startingHp), fontToUse(fontToUse)
{
	RenderText();
}
void Hp::MinusHp(int damage)
{
	hp -= damage;
	RenderText();
}
void Hp::Draw(math::ivec2 location)
{
	hpTexture.Draw(math::TranslateMatrix(math::ivec2{ location - hpTexture.GetSize() }));
}
void Hp::RenderText()
{
	std::string hpString = "Hp : " + std::to_string(hp);
	hpTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(hpString, 0xFFFFFFFF, true);
}