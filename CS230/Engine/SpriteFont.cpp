/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpriteFont.cpp
Project: CS230
Author: Kevin Wright
Co-Author : Duho Choi
Creation date: 4/30/2022
-----------------------------------------------------------------*/

#include "doodle/drawing.hpp"	//set_tint_color

#include "Engine.h"
#include "SpriteFont.h"
#include "TransformMatrix.h"

CS230::SpriteFont::SpriteFont(const std::filesystem::path& fileName) : texture(fileName) {
	unsigned int white = 0xFFFFFFFF;

	// The top left pixel MUST be white (0xFFFFFFFF)
	unsigned int color = texture.GetPixel({ 0, 0 });
	if (color != white) {
		Engine::GetLogger().LogError("Sprite font " + fileName.string() + " not setup correctly");
		return;
	}

	// Build our rects
	SetupCharRects();
}

void CS230::SpriteFont::SetupCharRects() {
	unsigned int testColor = texture.GetPixel({ 0, 0 });
	unsigned int nextColor;

	int height = texture.GetSize().y;

	int xPos = 1;
	for (int index = 0; index < numOfChars; index++) {
		// Todo: count the number of pixels until the nextColor is not the same as the testColor
		int width{ 0 }; 
		nextColor = texture.GetPixel({ xPos, 0 });
		while (testColor == nextColor)
		{
			width++;
			xPos++;
			nextColor = texture.GetPixel({ xPos, 0 });
		}

		// Test color becomes our next color, so this we be the color we are using to count
		testColor = nextColor;

		// Todo: Set the bottomLeft and topRight for each of our rectangles
		// When you have width of the letter you should be able to easily calculate 
		// the bottomLeft / topRight texel coordinates for that letter.
		charTexels[index].point2 = { xPos, 1 };
		charTexels[index].point1 = { xPos - width, height };
	}
}

math::irect2& CS230::SpriteFont::GetCharRect(char c) {
	if (c >= ' ' && c <= 'z') {
		return charTexels[c - ' '];
	}
	else {
		Engine::GetLogger().LogError("character '" + std::to_string(c) + "' not found in spriteFont");
		return charTexels[0];
	}
}

math::ivec2 CS230::SpriteFont::MeasureText(std::string text) {
	math::ivec2 size = { 0,0 };
	// Todo: For each character use it's charTexel information to find the width/height of the string
	for (char c : text) {
		size.x += GetCharRect(c).Size().x;
	}
	size.y = GetCharRect(' ').Size().y;
	return size;
}

CS230::Texture CS230::SpriteFont::DrawTextToTexture(std::string text, unsigned int color, bool drawShadow) {

	math::ivec2 textSize = MeasureText(text);
	if (drawShadow == true) {
		textSize += math::ivec2{ 3, 3 };
	}
	// this starts our rendering to the texture
	doodle::begin_drawing_to_image(textSize.x, textSize.y, true);

	math::TransformMatrix matrix;
	if (drawShadow == true) {
		// draw in black using the shadow position
		doodle::set_tint_color(doodle::HexColor(0x000000FF));
		for (char c : text) {
			DrawChar(matrix, c);
		}
		matrix = math::TranslateMatrix(math::ivec2{ 3,3 });
	}

	// draw in color using the updated position
	doodle::set_tint_color(doodle::HexColor(color));
	for (char c : text) {
		DrawChar(matrix, c);
	}
	// Reset the tint color incase it changed
	doodle::set_tint_color(doodle::HexColor(0xFFFFFFFF));
	return CS230::Texture(doodle::end_drawing_to_image());
}

void CS230::SpriteFont::DrawChar(math::TransformMatrix& matrix, char c) {
	math::irect2& displayRect = GetCharRect(c);
	math::ivec2 topLeftTexel = { displayRect.point1.x, displayRect.point2.y };
	if (c != ' ') {
		texture.Draw(matrix, topLeftTexel, displayRect.Size());
	}
	matrix *= math::TranslateMatrix(math::ivec2{ displayRect.Size().x, 0 });
}