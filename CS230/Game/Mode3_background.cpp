/*--------------------------------------------------------------
Copyright(C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3_background.cpp
Project: CS230
Author: Minsu Kim
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"
#include "Mode3_background.h"

Mode3_background::Mode3_background(const std::filesystem::path& filePath) : 
	background1( Engine::GetTextureManager().Load(filePath) ), 
	background2( Engine::GetTextureManager().Load(filePath) ),
	background1_position(math::vec2{ 0, 0 }),
	background2_position(math::vec2{ 0, static_cast<double>(background2->GetSize().y) })
{}

void Mode3_background::Update(math::vec2 cameraVector)
{
	if (background1_position.y + background1->GetSize().y < cameraVector.y)
		background1_position.y += background1->GetSize().y * 2;

	if (background2_position.y + background1->GetSize().y < cameraVector.y)
		background2_position.y += background2->GetSize().y * 2;
}

void Mode3_background::Draw(math::vec2 location)
{
	background1->Draw( math::TranslateMatrix(location + background1_position) );
	background2->Draw( math::TranslateMatrix(location + background2_position) );
}

math::ivec2 Mode3_background::GetSize()
{
	return background1->GetSize();
}