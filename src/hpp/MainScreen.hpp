#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Game.hpp"
#include "QuadTree.hpp"
#include "TextBox.hpp"
#include "Particle.hpp"
#include "Button.hpp"

class MainScreen : public GameState
{
public:
    explicit MainScreen(Game *game);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;

private:
    Game *game;

    QuadTree<Particle> quadTree;
    sf::FloatRect boundary;
    ushort treeNodeCapacity;

    std::vector<Particle> myObjects;
    std::vector<Particle *> myCollisions;

    sf::RectangleShape mouseRect;

    bool pause, brushMode, pressed;

    sf::Font* font;

    ushort objectNum;

    float radius;
    
    std::vector<TextBox> textboxes;
    std::vector<sf::Text> labels;
    sf::Text fpsLabel;

    sf::Clock fpsTimer;

    std::vector<Button> buttons;

    void init();

    void initializeObjects();

    void moveObjects(float dt);

    void brush();

    void resize(const sf::Event &event);
};
