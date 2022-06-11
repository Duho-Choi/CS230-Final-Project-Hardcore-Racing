/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Project: CS230
Author: Duho Choi
Creation date: 3/13/2021
-----------------------------------------------------------------*/
#pragma once
#include <filesystem> 
#include <string>
#include "Vec2.h"
#include "Component.h"

namespace CS230 {
    class Texture;
    class Animation;
}

namespace math {
    class TransformMatrix;
}

namespace CS230 {
    class GameObject;

    class Sprite : public Component {
    public:  
        Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
        ~Sprite();

        void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
        void Draw(math::TransformMatrix displayMatrix);
        void PlayAnimation(int anim);
        void Update(double dt) override;
        bool IsAnimationDone();
        math::ivec2 GetHotSpot(int index);        
        math::ivec2 GetFrameSize() const;
        int GetCurrentAnim() const;
    private:
        math::ivec2 GetFrameTexel(int frameNum) const;

        Texture* texturePtr;

        int currAnim;
        std::vector<Animation*> animations;

        math::ivec2 frameSize;
        std::vector<math::ivec2> frameTexel;
        std::vector<math::ivec2> hotSpotList;
    };
}