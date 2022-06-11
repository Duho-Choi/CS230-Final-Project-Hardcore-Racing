/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.h
Project: CS230
Author: Kevin Wright
Creation date: 2/26/2021
-----------------------------------------------------------------*/

#pragma once
#include <filesystem>
#include <vector>
#include "..\Engine\GameObject.h"
#include "..\Engine\Component.h"


namespace math {
    struct vec2;
    class TransformMatrix;
}

namespace CS230 {
    class ParticleEmitter : public Component {
    protected:
        class Particle : public GameObject {
        public:
            Particle(const std::filesystem::path& spriteFile);
            void Revive(math::vec2 position_, math::vec2 velocity_, double life_);
            void Update(double dt) override;
            void Draw(math::TransformMatrix matrix) override;
            bool IsAlive() { return life > 0; }
        private:
            double life;
        };
    public:
        ParticleEmitter(double lifetime);
        virtual ~ParticleEmitter();
        void AddParticle(Particle* particleData);
        void Emit(int number, math::vec2 position, math::vec2 emitterVelocity, math::vec2 emitVector, double spread);
    private:
        std::vector<Particle*> particleMemoryPool;
        int particleIndexToUse;
        double lifetime;
    };
}