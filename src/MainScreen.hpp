#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "Game.hpp"
#include "QuadTree.hpp"
#include "TextBox.hpp"
#include "Common.hpp"
#include "Particle.hpp"

class MainScreen : public GameState
{
public:
    MainScreen(Game *game);

    void handleInput();
    void update(const float dt);
    void draw();

private:
    Game *game;

    QuadTree<Particle> quadTree;
    sf::FloatRect boundary;
    ushort treeNodeCapacity;

    std::vector<Particle> myObjects;
    std::vector<Particle *> myCollisions;

    sf::RectangleShape mouseRect;

    bool pause;

    sf::Font* font;

    ushort objectNum;

    float radius;
    
    std::vector<TextBox> textboxes;
    std::vector<sf::Text> labels;

    void init();

    void initializeObjects();

    void moveObjects(float speed, const float dt);
};
