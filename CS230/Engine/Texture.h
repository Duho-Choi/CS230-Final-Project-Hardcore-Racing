/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Purpose: Wrapper class for doodle::Image
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include <doodle/image.hpp>    //doodle::Image
#include "Vec2.h"
#include "TransformMatrix.h"

namespace CS230 {
    class Texture {
        friend class TextureManager;
        friend class SpriteFont;
    public:
        Texture() {}
        unsigned int GetPixel(math::ivec2 texel);
        void Draw(math::TransformMatrix displayMatrix);
        void Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize);
        math::ivec2 GetSize();
    private:        
        Texture(doodle::Image&& doodleImage);
        Texture(const std::filesystem::path& filePath);
        doodle::Image image;
    };
}