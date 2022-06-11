/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: Duho Choi
Creation date: 5/2/20212
-----------------------------------------------------------------*/
#include "MainMenu.h"
#include "../Engine/Engine.h"	// GetSpriteFont()
#include "Fonts.h"
#include "Screens.h"

MainMenu::MainMenu()
	: upKey(CS230::InputKey::Keyboard::Up), downKey(CS230::InputKey::Keyboard::Down), 
	selectKey(CS230::InputKey::Keyboard::Enter), selectedIndex(0) {}

//modeReload(CS230::InputKey::Keyboard::R), modeNext(CS230::InputKey::Keyboard::Enter) {}
void MainMenu::Load() {
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData) {
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Mode1);
	RenderOption(optionsData[selectedIndex], true);
}
void MainMenu::Update([[maybe_unused]] double dt)
{
	if (upKey.IsKeyReleased() == true) {
		selectedIndex--;
		if (selectedIndex < 0)
			selectedIndex = 0;
	}
	if (downKey.IsKeyReleased() == true) {
		selectedIndex++;
		if (selectedIndex >= 3)
			selectedIndex = 2;
	}
	if (selectKey.IsKeyReleased() == true) {

		if (selectedIndex == 2)
			Engine::GetGameStateManager().Shutdown();
		else
			Engine::GetGameStateManager().SetNextState(selectedIndex + 2);
	}

	for (int i = 0; i < static_cast<int>(MainMenu::Options::Count); i++)
	{
		if(selectedIndex == i)
			RenderOption(optionsData[i], true);
		else
			RenderOption(optionsData[i], false);
	}
}
void MainMenu::Unload()
{
	
}
void MainMenu::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	title.Draw(math::TranslateMatrix{ math::vec2{ Engine::GetWindow().GetSize().x * 0.5 - title.GetSize().x,
		Engine::GetWindow().GetSize().y * 0.7 - title.GetSize().y / 2} } * math::ScaleMatrix({ 2, 2 }));

	for (OptionData& option : optionsData)
	{
		option.texture.Draw(math::TranslateMatrix{
			math::vec2{option.positionPercent.x * Engine::GetWindow().GetSize().x - option.texture.GetSize().x / 2,
			option.positionPercent.y * Engine::GetWindow().GetSize().y - option.texture.GetSize().y / 2} });
	}
}

MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] = {
	{"Side Scroller", {0.5, 0.45}, {} },
	{"Space Shooter", {0.5, 0.35}, {} },
	{"Quit", {0.5, 0.25}, {} },
};

void MainMenu::RenderOption(OptionData& data, bool isHighlighted) {
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(
		data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}