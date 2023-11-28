#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "TextBox.hpp"
#include "Particle.hpp"
namespace Input
{
    bool isMouseOver(TextBox textbox, sf::RenderWindow *window);
    // bool isMouseOver(sf::Sprite sprite, sf::RenderWindow *window);
}

namespace Collision
{
    bool CircleShapeCollision(const sf::CircleShape &A, const sf::CircleShape &B);
    bool ParticleCollision(const Particle &A, const Particle &B);
}