/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/3/2021
-----------------------------------------------------------------*/
#pragma once
#include "Background.h"
#include "..\Engine\Camera.h"
#include "..\Engine\Engine.h"

void Background::Add(const std::filesystem::path& texturePath, int level) {
	backgrounds.push_back(ParallaxInfo{ Engine::GetTextureManager().Load(texturePath), level });
}
void Background::Unload() {
	backgrounds.clear();
	std::vector<ParallaxInfo>().swap(backgrounds);
}
void Background::Draw(const CS230::Camera& camera) {
	for (unsigned int i = 0; i < backgrounds.size(); i++)
	{
		backgrounds.at(i).texturePtr->Draw(math::TranslateMatrix(math::vec2{ -camera.GetPosition() / backgrounds.at(i).level }));
	}
}
math::ivec2 Background::Size() {
	for (unsigned int i = 0; i < backgrounds.size(); i++)
	{
		if (backgrounds.at(i).level == 1)
			return backgrounds.at(i).texturePtr->GetSize();
	}
	return math::ivec2{ 0,0 };
}