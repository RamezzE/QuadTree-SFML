#include "../hpp/Common.hpp"

#include <cmath>


namespace Collision
{
    bool CircleShapeCollision(const sf::CircleShape &A, const sf::CircleShape &B)
    {
        const float distance = sqrt(pow(A.getGlobalBounds().left - B.getGlobalBounds().left, 2) + pow(A.getGlobalBounds().top - B.getGlobalBounds().top, 2));
        return distance < A.getRadius() + B.getRadius();
    }

    bool ParticleCollision(const Particle &A, const Particle &B)
    {
        return CircleShapeCollision(A.getShape(), B.getShape());
    }

}
