#include "MainScreen.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

MainScreen::MainScreen(Game *game)
{
    this->game = game;
    init();
}

void MainScreen::init()
{
    boundary = sf::FloatRect(0, 0, game->width, game->height);

    ushort objectNum = 200; // range 100 kda fps

    treeCapacity = objectNum / 100;
    if (treeCapacity < 4)
        treeCapacity = 4;

    quadTree.setData(boundary, treeCapacity);
    sf::CircleShape *circlePtr;
    for (ushort i = 0; i < objectNum; i++)
    {
        circlePtr = new sf::CircleShape(10.f);
        circlePtr->setPosition((rand() % (int)boundary.width), ((rand() % (int)boundary.height)));
        myObjects.push_back(circlePtr);
    }
    
    mouseRect.setSize(sf::Vector2f(game->height / 3.f, game->height / 3.f));
    mouseRect.setFillColor(sf::Color::Transparent);
    mouseRect.setOutlineThickness(2);
    mouseRect.setOutlineColor(sf::Color::Yellow);
    sf::FloatRect temp = mouseRect.getGlobalBounds();
    mouseRect.setOrigin(temp.left + temp.width / 2, temp.top + temp.height / 2);
}

void MainScreen::handleInput()
{
    sf::Event event;

    while (game->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            game->window->close();
        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                for (int i = 0; i < myObjects.size(); i++)
                    myObjects[i]->setPosition((rand() % (int)boundary.width), ((rand() % (int)boundary.height)));
                break;

            case sf::Mouse::Right:
                for (int i = myObjects.size() - 1; i >= 0; i--)
                {
                    if (myObjects[i]->getGlobalBounds().contains(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y))
                    {
                        delete myObjects[i];
                        myObjects.erase(myObjects.begin() + i);
                        break;
                    }
                }
                break;
            }
        }
    }
}

void MainScreen::update(const float dt)
{
    // reconstructing the tree every frame

    quadTree.reset();

    for (ushort i = 0; i < myObjects.size(); i++)
    {
        myObjects[i]->setFillColor(sf::Color::Green);
        quadTree.insert(myObjects[i]);
    }

    // checking every single object for collision
    for (ushort i = 0; i < myObjects.size(); i++)
    {
        quadTree.query(myObjects[i]->getGlobalBounds(), myCollisions);
        for (ushort j = 0; j < myCollisions.size(); j++)
        {
            if (Collision::CircleShapeCollision(*myObjects[i], *myCollisions[j]))
            {
                // changing the color of the colliding objects
                myObjects[i]->setFillColor(sf::Color::Red);
                // myCollisions[j]->setFillColor(sf::Color::Red);
                break;
            }
        }
        myCollisions.clear();
    }

    mouseRect.setPosition(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y);

    quadTree.query(mouseRect.getGlobalBounds(), myCollisions);
    for (ushort i = 0; i < myCollisions.size(); i++)
        myCollisions[i]->setFillColor(sf::Color::Yellow);

    myCollisions.clear();

    moveObjects(80, dt);
}

void MainScreen::draw()
{
    for (ushort i = 0; i < myObjects.size(); i++)
        game->window->draw(*myObjects[i]);

    game->window->draw(mouseRect);
}

void MainScreen::moveObjects(float speed, const float dt)
{
    // Objects move randomly
    for (ushort i = 0; i < myObjects.size(); i++)
        myObjects[i]->move(speed * (rand() % 3 - 1) * dt, speed * (rand() % 3 - 1) * dt);
}