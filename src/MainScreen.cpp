#include "MainScreen.hpp"

#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>

extern sf::Color defaultColor, collisionColor, mouseRectColor;
extern bool showQuadTree, showMouseRect;
extern float particleSpeed;

MainScreen::MainScreen(Game *game)
{
    this->game = game;

    pause = false;
    boundary = sf::FloatRect(0, 0, game->width, game->height);

    treeNodeCapacity = 4, objectNum = 800, radius = 2.0;

    quadTree.setData(boundary, treeNodeCapacity);

    font = new sf::Font();
    font->loadFromFile("C:\\GitHub\\FlappyBird\\assets\\fonts\\soup_of_justice\\soupofjustice.ttf");

    init();
}

void MainScreen::init()
{

    initializeObjects();

    mouseRect.setSize(sf::Vector2f(game->height / 3.f, game->height / 3.f));
    mouseRect.setFillColor(sf::Color::Transparent);
    mouseRect.setOutlineThickness(2);
    mouseRect.setOutlineColor(mouseRectColor);
    sf::FloatRect temp = mouseRect.getGlobalBounds();
    mouseRect.setOrigin(temp.left + temp.width / 2, temp.top + temp.height / 2);

    ushort characterSize = 30;
    for (int i = 0; i < 2; i++)
    {
        textboxes.push_back(TextBox(*font));
        temp = textboxes[i].getGlobalBounds();
        textboxes[i].setOrigin(sf::Vector2f(temp.left + temp.width, temp.top));
        textboxes[i].setPosition(sf::Vector2f(game->width, i * temp.height));
        textboxes[i].setTextFormat(sf::Color::White, characterSize);
        textboxes[i].setSize(sf::Vector2f(100, characterSize));
        textboxes[i].setBorder(2, sf::Color::White, sf::Color::Black, sf::Color::Magenta);
        textboxes[i].allowNumberOnly();

        labels.push_back(sf::Text());
        labels[i].setFont(*font);
        labels[i].setString(i == 0 ? "Object Num: " : "Radius: ");

        labels[i].setCharacterSize(characterSize);
        labels[i].setFillColor(sf::Color::White);
        labels[i].setPosition(sf::Vector2f(game->width - textboxes[i].getGlobalBounds().width - labels[i].getGlobalBounds().width, i * temp.height));
    }
    textboxes[0].setString(std::to_string(objectNum));
    textboxes[0].setTextLimit(5);

    textboxes[1].setString(std::to_string(radius).substr(0, 3));
    textboxes[1].setTextLimit(3);
}

void MainScreen::handleInput()
{
    sf::Event event;

    while (game->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            game->window->close();

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            bool selected = false;

            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:

                for (int i = 0; i < textboxes.size(); i++)
                {
                    textboxes[i].handleInput(event);
                    if (textboxes[i].isSelected())
                        selected = true;
                }

                if (selected)
                    break;

                for (ushort i = 0; i < myObjects.size(); i++)
                    myObjects[i].setPosition((rand() % (int)boundary.width), ((rand() % (int)boundary.height)));

                break;

            case sf::Mouse::Right:
                showQuadTree = !showQuadTree;
                break;
            }
        }

        else if (event.type == sf::Event::TextEntered)
        {
            for (int i = 0; i < textboxes.size(); i++)
                textboxes[i].handleInput(event);
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Space:
                pause = !pause;
                break;

            case sf::Keyboard::M:
                showMouseRect = !showMouseRect;
                break;

            case sf::Keyboard::Return:

                for (ushort i = 0; i < textboxes.size(); i++)
                    if (textboxes[i].getString().length() == 0 || textboxes[i].getString() == "0")
                        return;

                objectNum = std::stoi(textboxes[0].getString());
                radius = std::stof(textboxes[1].getString());
                initializeObjects();

                break;
            }
        }
    }
}

void MainScreen::update(const float dt)
{
    for (ushort i = 0; i < textboxes.size(); i++)
        textboxes[i].update(game->window);

    // reconstructing the tree every frame
    quadTree.reset();

    // inserting all the objects into the tree every frame
    for (ushort i = 0; i < myObjects.size(); i++)
    {
        myObjects[i].setFillColor(defaultColor);
        quadTree.insert(&myObjects[i]);
    }

    for (ushort i = 0; i < myObjects.size(); i++)
    {
        // already queried the object for collisions
        if (myObjects[i].getFillColor() == collisionColor)
            continue;

        // query the quadtree for each object's global bounds and store the results in myCollisions
        quadTree.query(myObjects[i].getGlobalBounds(), myCollisions);

        for (ushort j = 0; j < myCollisions.size(); j++)
        {
            if (Collision::CircleShapeCollision(myObjects[i], *myCollisions[j]))
            {
                // changing the color of the colliding objects
                myObjects[i].setFillColor(collisionColor);
                myCollisions[j]->setFillColor(collisionColor);
            }
        }
        myCollisions.clear();
    }

    if (showMouseRect)
    {
        mouseRect.setPosition(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y);

        // query the quadtree for the mouseRect's global bounds
        quadTree.query(mouseRect.getGlobalBounds(), myCollisions);

        for (ushort i = 0; i < myCollisions.size(); i++)
            myCollisions[i]->setFillColor(mouseRectColor);

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

    if (showMouseRect)
        game->window->draw(mouseRect);

    for (int i = 0; i < textboxes.size(); i++)
    {
        game->window->draw(labels[i]);
        textboxes[i].draw(game->window);
    }
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

void MainScreen::initializeObjects()
{
    myObjects.clear();
    sf::CircleShape circle(radius);
    for (ushort i = 0; i < objectNum; i++)
    {
        circle.setPosition((rand() % (int)boundary.width), ((rand() % (int)boundary.height)));
        myObjects.push_back(circle);
    }
}