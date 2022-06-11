/*--------------------------------------------------------------
Copyright(C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.h
Project: CS230
Author: Kevin Wright
Creation date: 2/17/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h"
#include "..\Engine\Component.h"

enum class Fonts;

class Score : public CS230::Component {
public:
	Score(int startingScore, Fonts fontToUse);
	void AddScore(int newPoints);
	void Draw(math::ivec2 location);
private:
	void RenderText();
	Fonts fontToUse;
	unsigned int score;
	CS230::Texture scoreTexture;
};