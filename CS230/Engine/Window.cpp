/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/13/2022
-----------------------------------------------------------------*/
#include <doodle/window.hpp>
#include <doodle/drawing.hpp>     // set_frame_of_reference, clear_background
#include "Engine.h"			// GetWindow
#include "Window.h"

void CS230::Window::Init(std::string windowName) {
    doodle::create_window(windowName, 1440, 810);
    doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginBottomLeft);
}
void CS230::Window::Update() {
    doodle::update_window();
}
void CS230::Window::Resize(int newWidth, int newHeight){
    windowSize.x = newWidth;
    windowSize.y = newHeight;
}
math::ivec2 CS230::Window::GetSize() {
    return windowSize;
}
void CS230::Window::Clear(unsigned int color) {
    doodle::clear_background(doodle::HexColor{ color });
}
void on_window_resized(int new_width, int new_height) {
    Engine::GetLogger().LogEvent("Window Resized");
    Engine::GetWindow().Resize(new_width, new_height);
}