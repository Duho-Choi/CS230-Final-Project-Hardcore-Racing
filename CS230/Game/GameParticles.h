/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.h
Project: CS230
Author: Kevin Wright
Creation date: 2/26/2021
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/ParticleEmitter.h"
#include "GameObjectTypes.h"

class SmokeEmitter : public CS230::ParticleEmitter {
public:
    SmokeEmitter();
private:
    class SmokeParticle : public CS230::ParticleEmitter::Particle {
    public:
        SmokeParticle(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Smoke Particle"; }
    };
    static constexpr int NumParticles = 20;
};

class HitEmitter : public CS230::ParticleEmitter {
public:
    HitEmitter();
private:
    class HitParticle : public CS230::ParticleEmitter::Particle {
    public:
        HitParticle(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Hit Particle"; }
    };
    static constexpr int NumParticles = 10;
};

class MeteorBitEmitter : public CS230::ParticleEmitter {
public:
    MeteorBitEmitter();
private:
    class MeteorBit : public CS230::ParticleEmitter::Particle {
    public:
        MeteorBit(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Meteor Bit Particle"; }
    };
    static constexpr int NumParticles = 150;
};

class DustEmitter : public CS230::ParticleEmitter {
public:
    DustEmitter();
private:
    class Dust : public CS230::ParticleEmitter::Particle {
    public:
        Dust(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Dirt Particle"; }
    };
    static constexpr int NumParticles = 200;
};