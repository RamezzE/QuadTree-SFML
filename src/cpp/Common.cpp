#include "../hpp/Common.hpp"
namespace Input
{
    bool isMouseOver(TextBox textbox, sf::RenderWindow *window)
    {
        return textbox.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
    }

}

namespace Collision
{
    bool CircleShapeCollision(const sf::CircleShape &A, const sf::CircleShape &B)
    {
        float distance = sqrt(pow(A.getGlobalBounds().left - B.getGlobalBounds().left, 2) + pow(A.getGlobalBounds().top - B.getGlobalBounds().top, 2));
        return distance < A.getRadius() + B.getRadius();
    }

    bool ParticleCollision(const Particle &A, const Particle &B)
    {
        return CircleShapeCollision(A.getShape(), B.getShape());
    }

}