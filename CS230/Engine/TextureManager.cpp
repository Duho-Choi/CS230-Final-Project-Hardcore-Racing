/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/29/2021
-----------------------------------------------------------------*/
#include "TextureManager.h"
#include "Texture.h"
#include "Engine.h"		//GetLogger

//namespace CS230 {
//    class Texture;
//
//    class TextureManager {
//    public:
//        Texture* Load(const std::filesystem::path& filePath);
//        void Unload();
//
//    private:
//        std::map<std::filesystem::path, Texture*> pathToTexture;
//    };
//}
CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath)
{
	if (pathToTexture.find(filePath) == pathToTexture.end())
	{
		pathToTexture.insert({ filePath, new Texture(filePath) });
	}
	return pathToTexture[filePath];
}
void CS230::TextureManager::Unload()
{
	Engine::GetLogger().LogEvent("Clear Textures");
	for (std::map<std::filesystem::path, Texture*>::iterator i = pathToTexture.begin(); 
		i != pathToTexture.end();)
	{
		delete i->second;
		i = pathToTexture.erase(i);
	}
	pathToTexture.clear();
}
