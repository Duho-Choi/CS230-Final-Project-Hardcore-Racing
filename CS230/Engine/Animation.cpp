/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.h
Project: CS230
Author: Duho Choi
Creation date: 2/12/2021
-----------------------------------------------------------------*/
#include <fstream>
#include <filesystem>

#include "Animation.h"
#include "Engine.h"	//LogError

CS230::Animation::Animation() : Animation("Assets/none.anm") { }

CS230::Animation::Animation(const std::filesystem::path& fileName) : animSequenceIndex(0) {
	if (fileName.extension() != ".anm") {
		throw std::runtime_error("Bad Filetype.  " + fileName.generic_string() + " not a sprite info file (.anm)");
	}
	std::ifstream inFile(fileName);
	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + fileName.generic_string());
	}

	std::string label;
	while (inFile.eof() == false) {
		inFile >> label;
		if (label == "PlayFrame") {
			int frame;
			float targetTime;
			inFile >> frame;
			inFile >> targetTime;

			animation.push_back(new PlayFrame(frame, targetTime));
		}
		else if (label == "Loop") {
			int loopToFrame;
			inFile >> loopToFrame;
			animation.push_back(new Loop(loopToFrame));
		}
		else if (label == "End") {
			animation.push_back(new End());
		}
		else {
			Engine::GetLogger().LogError("Unknown command " + label + " in anm file " + fileName.generic_string());
		}
	}
	ResetAnimation();
}

CS230::Animation::~Animation() {
	for (CommandData* command : animation) {
		delete command;
	}
	animation.clear();
}

void CS230::Animation::Update(double dt) {
	currPlayFrameData->Update(dt);
	if (currPlayFrameData->IsFrameDone() == true) {
		currPlayFrameData->ResetTime();
		++animSequenceIndex;
		if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
			currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
		}
		else if (animation[animSequenceIndex]->GetType() == Command::Loop) {
			Loop* loopData = static_cast<Loop*>(animation[animSequenceIndex]);
			animSequenceIndex = loopData->GetLoopToIndex();
			if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
				currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
			}
			else {
				Engine::GetLogger().LogError("Loop does not go to PlayFrame");
				ResetAnimation();
			}
		}
		else if (animation[animSequenceIndex]->GetType() == Command::End) {
			isAnimationDone = true;
			return;
		}
	}
}

int CS230::Animation::GetDisplayFrame() {
	return currPlayFrameData->GetFrameNum();
}

void CS230::Animation::ResetAnimation() {
	animSequenceIndex = 0;
	currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
	isAnimationDone = false;
}

bool CS230::Animation::IsAnimationDone() {
	return isAnimationDone;
}

CS230::Animation::PlayFrame::PlayFrame(int frame, double duration)
	: frame(frame), targetTime(duration), timer(0) {}

void CS230::Animation::PlayFrame::Update(double dt)
{
	timer += dt;
}
bool CS230::Animation::PlayFrame::IsFrameDone()
{
	if (timer > targetTime)
		return true;
	else
		return false;
}
void CS230::Animation::PlayFrame::ResetTime()
{
	timer = 0;
}
int CS230::Animation::PlayFrame::GetFrameNum()
{
	return frame;
}

CS230::Animation::Loop::Loop(int loopToIndex)
	: loopToIndex(loopToIndex) {}

int CS230::Animation::Loop::GetLoopToIndex()
{
	return loopToIndex;
}