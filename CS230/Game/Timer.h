/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.h
Project: CS230
Author: Kevin Wright
Creation date: 2/17/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h"
#include "..\Engine\Component.h"
class Timer : public CS230::Component {
public:
	Timer(int time);
	void Update(double dt) override;
	void Draw(math::ivec2 location);
	bool hasEnded();
private:
	double timer;
	CS230::Texture timeTexture;
};