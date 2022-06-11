/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/22/2022
-----------------------------------------------------------------*/
#pragma once
#include "Sprite.h"
#include "Engine.h"		// GetLogger()
#include "TransformMatrix.h"
#include "Texture.h"
#include "Animation.h"
#include "Collision.h"
#include "GameObject.h"

//CS230::Sprite::Sprite()
//	: currAnim(0), texturePtr(nullptr) {}

CS230::Sprite::Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object)
	: currAnim(0), texturePtr(nullptr)
{
	Load(spriteInfoFile, object);
}

void CS230::Sprite::Load(const std::filesystem::path& spriteInfoFile, GameObject* object) {
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	} 

	std::string text;
	inFile >> text;
	texturePtr = Engine::GetTextureManager().Load(text);
	frameSize = texturePtr->GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames") {
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++) {
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else if (text == "Anim") {
			inFile >> text;
			animations.push_back(new Animation(text));
		} 
		else if (text == "CollisionRect") {
            math::irect2 rect;
            inFile >> rect.point1.x >> rect.point1.y >> rect.point2.x >> rect.point2.y;
            if (object == nullptr) {
                Engine::GetLogger().LogError("Trying to add collision to a nullobject");
            } else {
                object->AddGOComponent(new RectCollision(rect, object));
            }
        } 
		else if (text == "CollisionCircle") {
            double radius;
            inFile >> radius;
            if (object == nullptr) {
                Engine::GetLogger().LogError("Trying to add collision to a nullobject");
            } else {
                object->AddGOComponent(new CircleCollision(radius, object));
            }
        }
		else {
			Engine::GetLogger().LogError("Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
}

math::ivec2 CS230::Sprite::GetHotSpot(int index)
{
	if (index < 0 || index >= static_cast<int>(hotSpotList.size()))
	{
		Engine::GetLogger().LogError("Invalid index in hotSpotList" + std::to_string(index));
		return math::ivec2{ 0, 0 };
	}
	else
		return hotSpotList.at(index);
}

math::ivec2 CS230::Sprite::GetFrameSize() const
{
	return frameSize;
}

math::ivec2 CS230::Sprite::GetFrameTexel(int frameNum) const
{
	if (frameNum < 0 || frameNum > static_cast<int>(frameTexel.size()))
	{
		Engine::GetLogger().LogError("Invalid frame texel index" + std::to_string(frameNum));
		return math::ivec2{ 0, 0 };
	}
	else
		return frameTexel.at(frameNum);
}

int CS230::Sprite::GetCurrentAnim() const
{
	return currAnim;
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix)
{
	texturePtr->Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)), GetFrameTexel(animations[currAnim]->GetDisplayFrame()), GetFrameSize());
}

void CS230::Sprite::PlayAnimation(int anim)
{
	if (anim < 0 || anim >= static_cast<int>(animations.size()))
	{
		Engine::GetLogger().LogError("Invalid animations index" + std::to_string(anim));
		currAnim = 0;
	}
	else
	{
		currAnim = anim;
		animations[currAnim]->ResetAnimation();
	}

}

void CS230::Sprite::Update(double dt) 
{
	animations[currAnim]->Update(dt);
}

bool CS230::Sprite::IsAnimationDone()
{
	return animations[currAnim]->IsAnimationDone();
}

CS230::Sprite::~Sprite() {
    for (Animation* anim : animations) {
        delete anim;
    }
    animations.clear();
}