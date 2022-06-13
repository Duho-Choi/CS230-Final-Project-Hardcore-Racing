/*--------------------------------------------------------------
Copyright(C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3_background.h
Project: CS230
Author: Minsu Kim
Creation date: 6/13/2022
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\Texture.h"
#include "..\Engine\Component.h"


class Mode3_background : public CS230::Component {
public:
	Mode3_background(const std::filesystem::path& filePath);
	void Update(math::vec2 cameraVector);
	void Draw(math::vec2 location);

	math::ivec2 GetSize();
private:
	CS230::Texture* background1;
	CS230::Texture* background2;

	math::vec2 background1_position;
	math::vec2 background2_position;
};