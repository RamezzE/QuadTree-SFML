#include "../hpp/Particle.hpp"

Particle::Particle(float radius)
{
    shape.setPosition(0,0);
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::White);
    velocity = sf::Vector2f(0, 0);
}

void Particle::update(const float dt, sf::FloatRect boundary)
{
    if (shape.getPosition().x < boundary.left )
        velocity.x *= -1;

    if (shape.getPosition().y < boundary.top)
        velocity.y *= -1;

    if (shape.getPosition().x > boundary.left + boundary.width)
        velocity.x *= -1;

    if (shape.getPosition().y > boundary.top + boundary.height)
        velocity.y *= -1;
    
    shape.move(velocity * dt);
}

void Particle::render(sf::RenderWindow *window)
{
    window->draw(shape);
}

void Particle::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
}

void Particle::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Particle::setRadius(float radius)
{
    shape.setRadius(radius);
}

void Particle::setColor(sf::Color color)
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

