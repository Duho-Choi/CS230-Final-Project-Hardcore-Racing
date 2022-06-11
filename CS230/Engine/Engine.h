/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.h
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Duho Choi
Creation date: 3/22/2022
-----------------------------------------------------------------*/
#pragma once
#pragma once

#include <chrono>   
#include "GameStateManager.h"
#include "Input.h"
#include "Window.h"
#include "Logger.h"
#include "TextureManager.h"
#include "SpriteFont.h"

class Engine {
public:
    static Engine& Instance() { static Engine instance; return instance; }
    static CS230::Logger& GetLogger() { return Instance().logger; };
    static CS230::Input& GetInput() { return Instance().input; }
    static CS230::Window& GetWindow() { return Instance().window; }
    static CS230::GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
    static CS230::TextureManager& GetTextureManager() { return Instance().textureManager; }   
    static CS230::SpriteFont& GetSpriteFont(int index) { return Instance().fonts[index]; }

    void Init(std::string windowName);
    void Shutdown();
    void Update();
    bool HasGameEnded();
    void AddSpriteFont(const std::filesystem::path& fileName); 
    
    template<typename T>
    static T* GetGSComponent() { return GetGameStateManager().GetGSComponent<T>(); }

private:
    Engine();
    ~Engine();

    std::chrono::system_clock::time_point lastTick;
    std::chrono::system_clock::time_point fpsCalcTime;
    int frameCount;

    CS230::Logger logger;
    CS230::GameStateManager gameStateManager;
    CS230::Input input;
    CS230::Window window;
    CS230::TextureManager textureManager;    
    std::vector<CS230::SpriteFont> fonts;

    int seed{ 0 };

    static constexpr double Target_FPS = 60.0;
    static constexpr int FPS_IntervalSec = 5;
    static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
};