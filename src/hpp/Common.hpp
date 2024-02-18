#pragma once
#include <SFML/Graphics.hpp>

#include "Particle.hpp"

namespace Collision
{
    bool CircleShapeCollision(const sf::CircleShape &A, const sf::CircleShape &B);
    bool ParticleCollision(const Particle &A, const Particle &B);
}