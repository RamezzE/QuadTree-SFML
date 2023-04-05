#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <cmath>

#include "Game.hpp"
#include "QuadTree.hpp"

class MainScreen : public GameState
{
public:
    MainScreen(Game *game);
    void init();

    void handleInput();
    void update(const float dt);
    void draw();

private:
    Game *game;

    QuadTree<sf::CircleShape> quadTree;
    sf::FloatRect boundary;
    ushort treeCapacity;

    std::vector<sf::CircleShape> myObjects;
    std::vector<sf::CircleShape*> myCollisions;

    sf::RectangleShape mouseRect;

    bool pause;

    void moveObjects(float speed, const float dt);
    
    bool CircleShapeCollision(const sf::CircleShape &A, const sf::CircleShape &B);
};
