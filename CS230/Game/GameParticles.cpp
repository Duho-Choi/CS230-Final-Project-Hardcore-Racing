/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.cpp
Project: CS230
Author: Duho Choi
Creation date: 6/1/2022
-----------------------------------------------------------------*/

#include "GameParticles.h"

SmokeEmitter::SmokeEmitter()
	: ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new SmokeParticle("assets/smoke.spt"));
	}
}
HitEmitter::HitEmitter()
	: ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new HitParticle("assets/hit.spt"));
	}
}
MeteorBitEmitter::MeteorBitEmitter()
	: ParticleEmitter(1.5)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new MeteorBit("assets/MeteorBit.spt"));
	}
}
DustEmitter::DustEmitter()
	: ParticleEmitter(0.4)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new Dust("Assets/Mode3/Dust.spt"));
	}
}