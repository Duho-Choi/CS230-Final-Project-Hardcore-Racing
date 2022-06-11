/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: Wrapper class for doodle::Image
Project: CS230
Author: Duho Choi
Creation date: 4/3/2021
-----------------------------------------------------------------*/
#include <doodle/drawing.hpp>	//draw_image
#include "Texture.h"
#include "TransformMatrix.h"

CS230::Texture::Texture(const std::filesystem::path& filePath)
	: image(doodle::Image{ filePath }) {}

CS230::Texture::Texture(doodle::Image&& doodleImage) {
    image = std::move(doodleImage);
}

void CS230::Texture::Draw(math::TransformMatrix displayMatrix) {
    doodle::push_settings();
    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
    doodle::draw_image(image, 0, 0);
    doodle::pop_settings();
}
void CS230::Texture::Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize) {
    doodle::push_settings();
    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
    doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
    doodle::pop_settings();
}
math::ivec2 CS230::Texture::GetSize() { return { image.GetWidth(), image.GetHeight() }; }

unsigned int CS230::Texture::GetPixel(math::ivec2 texel) {
    int index = texel.y * GetSize().x + texel.x;
    return (static_cast<int>(image[index].red)) << 24 |
        (static_cast<int>(image[index].green)) << 16 |
        (static_cast<int>(image[index].blue)) << 8 |
        (static_cast<int>(image[index].alpha));
}
