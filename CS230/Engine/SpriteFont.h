/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpriteFont.h
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "Texture.h"
#include "Vec2.h"
#include "Rect.h"

namespace CS230 {
	class SpriteFont {
	public:
		SpriteFont(const std::filesystem::path& fileName);
		Texture DrawTextToTexture(std::string text, unsigned int color, bool drawShadow);
	private:
		void SetupCharRects();
		math::irect2& GetCharRect(char c);
		math::ivec2 MeasureText(std::string text);
		void DrawChar(math::TransformMatrix& matrix, char c);

		Texture texture;
		static constexpr int numOfChars = 'z' - ' ' + 1;
		math::irect2 charTexels[numOfChars];
	};
}