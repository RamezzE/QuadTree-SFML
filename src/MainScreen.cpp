#include "MainScreen.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

extern sf::Color defaultColor, collisionColor;
extern bool showQuadTree;
extern float particleSpeed, radius;

MainScreen::MainScreen(Game *game)
{
    this->game = game;

    pause = false;
    init();
}

void MainScreen::init()
{
    boundary = sf::FloatRect(0, 0, game->width, game->height);

    ushort objectNum = 500;

    treeCapacity = 4;

    quadTree.setData(boundary, treeCapacity);

    sf::CircleShape circle(radius);
    for (ushort i = 0; i < objectNum; i++)
    {
        circle.setPosition((rand() % (int)boundary.width), ((rand() % (int)boundary.height)));
        myObjects.push_back(circle);
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
                    myObjects[i].setPosition((rand() % (int)boundary.width), ((rand() % (int)boundary.height)));

                break;

            case sf::Mouse::Right:
                showQuadTree = !showQuadTree;
                break;
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Space:
                pause = !pause;
                break;
            }
        }
    }
}

void MainScreen::update(const float dt)
{
    // reconstructing the tree every frame

    quadTree.reset();

    for (auto i = 0; i < myObjects.size(); i++)
    {
        myObjects[i].setFillColor(defaultColor);
        quadTree.insert(&myObjects[i]);
    }

    mouseRect.setPosition(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y);
    quadTree.query(mouseRect.getGlobalBounds(), myCollisions);

    for (auto i = 0; i < myCollisions.size(); i++)
        myCollisions[i]->setFillColor(sf::Color::Yellow);

    myCollisions.clear();

    for (ushort i = 0; i < myObjects.size(); i++)
    {
        if (myObjects[i].getFillColor() == sf::Color::Yellow)
            continue;

        quadTree.query(myObjects[i].getGlobalBounds(), myCollisions);

        for (ushort j = 0; j < myCollisions.size(); j++)
        {
            if (CircleShapeCollision(myObjects[i], *myCollisions[j]))
            {
                // changing the color of the colliding objects
                myObjects[i].setFillColor(collisionColor);
                // std::cout << sizeof(myCollisions[j]) << std::endl;
                // std::cout << sizeof(*myCollisions[j]) << std::endl;
                break;
            }
        }
        myCollisions.clear();
    }

    //// brute force approach

    // for (ushort i = 0; i < myObjects.size(); i++)
    //     myObjects[i].setFillColor(defaultColor);

    // for (ushort i = 0; i < myObjects.size(); i++)
    // {
    //     for (ushort j = i + 1; j < myObjects.size(); j++)
    //     {
    //         if (i == j)
    //             continue;
    //         if (!myObjects[i].getGlobalBounds().intersects(myObjects[j].getGlobalBounds()))
    //             continue;

    //         if (CircleShapeCollision(myObjects[i], myObjects[j]))
    //         {
    //             myObjects[i].setFillColor(collisionColor);
    //             myObjects[j].setFillColor(collisionColor);
    //         }
    //     }
    // }

    if (!pause)
        moveObjects(particleSpeed, dt);
}

void MainScreen::draw()
{
    if (showQuadTree)
        quadTree.draw(game->window);

    for (ushort i = 0; i < myObjects.size() - 1; i++)
        game->window->draw(myObjects[i]);

    game->window->draw(mouseRect);
}

void MainScreen::moveObjects(float speed, const float dt)
{
    // Objects move randomly
    sf::Vector2f velocity = sf::Vector2f(0, 0);

    for (ushort i = 0; i < myObjects.size(); i++)
    {
        velocity.x = (rand() % (int)speed - (speed) / 2);
        velocity.y = (rand() % (int)speed - (speed) / 2);
        myObjects[i].move(velocity * dt);
    }
}

bool MainScreen::CircleShapeCollision(const sf::CircleShape &A, const sf::CircleShape &B)
{
    // Calculate the distance between the centers of the circles
    float dx = A.getGlobalBounds().left - B.getGlobalBounds().left;
    float dy = A.getGlobalBounds().top - B.getGlobalBounds().top;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Compare the distance to the sum of the radii
    if (distance <= A.getRadius() + B.getRadius())
        return true;

    return false;
}