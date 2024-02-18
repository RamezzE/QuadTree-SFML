#include "../hpp/Particle.hpp"

Particle::Particle(const float radius)
{
    shape.setPosition(0,0);
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::White);
    velocity = sf::Vector2f(0, 0);
}

void Particle::update(const float dt, const sf::FloatRect boundary)
{
    if (shape.getPosition().x - shape.getRadius() < boundary.left
        || shape.getPosition().x + shape.getRadius() > boundary.left + boundary.width)
        velocity.x *= -1;

    if (shape.getPosition().y - shape.getRadius() < boundary.top
        || shape.getPosition().y + shape.getRadius() > boundary.top + boundary.height)
        velocity.y *= -1;

    if (shape.getPosition().x - shape.getRadius() > boundary.left + boundary.width
        || shape.getPosition().x + shape.getRadius() < boundary.left)
        velocity.x *= -1;

    if (shape.getPosition().y - shape.getRadius() > boundary.top + boundary.height
        || shape.getPosition().y + shape.getRadius() < boundary.top)
        velocity.y *= -1;
    
    shape.move(velocity * dt);
}

void Particle::render(sf::RenderWindow *window) const {
    window->draw(shape);
}

void Particle::setPosition(const sf::Vector2f position)
{
    shape.setPosition(position);
}

void Particle::setVelocity(const sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Particle::setRadius(const float radius)
{
    shape.setRadius(radius);
}

void Particle::setColor(const sf::Color color)
{
    shape.setFillColor(color);
}

sf::Vector2f Particle::getPosition() const
{
    return shape.getPosition();
}

sf::Vector2f Particle::getVelocity() const
{
    return velocity;
}

float Particle::getRadius() const
{
    return shape.getRadius();
}

sf::Color Particle::getColor() const
{
    return shape.getFillColor();
}

sf::CircleShape Particle::getShape() const
{
    return shape;
}

sf::FloatRect Particle::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}

