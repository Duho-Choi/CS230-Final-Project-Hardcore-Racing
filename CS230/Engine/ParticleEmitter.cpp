/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.cpp
Project: CS230
Author: Duho Choi
Creation date: 5/29/2022
-----------------------------------------------------------------*/

#include "ParticleEmitter.h"
#include "Engine.h"
#include "GameObjectManager.h"

CS230::ParticleEmitter::ParticleEmitter(double lifetime)
	: particleIndexToUse(0), lifetime(lifetime)
{
}
CS230::ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}
void CS230::ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(particleData);
}
void CS230::ParticleEmitter::Emit(int number, math::vec2 position, math::vec2 emitterVelocity, math::vec2 emitVector, double spread)
{
	for (int i = 0; i < number; i++)
	{
		if (particleMemoryPool[particleIndexToUse]->IsAlive() == true) {
			Engine::GetLogger().LogError("Overwriting alive particle");
		}

		double angle{ 0 };
		if (spread != 0) {
			angle = ((rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread / 2;
		} else {
			angle = 0;
		}

		math::vec2 velocity = math::RotateMatrix(angle) * emitVector * 
			((rand() % 1024) / 2048.0f + 0.5f) + emitterVelocity;

		particleMemoryPool[particleIndexToUse]->Revive(position, emitterVelocity + velocity, lifetime);
		particleIndexToUse++;
		if (particleIndexToUse >= static_cast<int>(particleMemoryPool.size()))
			particleIndexToUse = 0;
	}
}

CS230::ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile)
	: GameObject({ 0, 0 }), life(0)
{
	AddGOComponent(new CS230::Sprite(spriteFile, this));
}
void CS230::ParticleEmitter::Particle::Revive(math::vec2 position_, math::vec2 velocity_, double life_)
{
	life = life_;
	SetPosition(position_);
	SetVelocity(velocity_);
	GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
}
void CS230::ParticleEmitter::Particle::Update(double dt)
{
	if (this->IsAlive() == true)
	{
		life -= dt;
		GameObject::Update(dt);
	}
}
void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if (this->IsAlive() == true)
		GameObject::Draw(matrix);
}
