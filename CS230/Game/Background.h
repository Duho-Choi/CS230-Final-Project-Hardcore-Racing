/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.h
Project: CS230
Author: Duho Choi
Creation date: 4/3/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h"
#include "..\Engine\Component.h"

namespace CS230 {
    class Camera;
}

class Background : public CS230::Component {
public:
    void Add(const std::filesystem::path& texturePath, int level);
    void Unload();
    void Draw(const CS230::Camera& camera);
    math::ivec2 Size();
private:
    struct ParallaxInfo {
        CS230::Texture* texturePtr;
        int level;
    };
    std::vector<ParallaxInfo> backgrounds;
};