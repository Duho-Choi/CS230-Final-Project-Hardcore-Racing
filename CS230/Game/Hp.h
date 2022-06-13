/*--------------------------------------------------------------
Copyright(C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hp.h
Project: CS230
Author: Minsu Kim
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h"
#include "..\Engine\Component.h"

enum class Fonts;

class Hp : public CS230::Component {
public:
	Hp(int startingScore, Fonts fontToUse);
	void MinusHp(int damage);
	void Draw(math::ivec2 location);
private:
	void RenderText();
	Fonts fontToUse;
	unsigned int hp;
	CS230::Texture hpTexture;
};