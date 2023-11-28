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

    pause = brushMode = pressed = false;
    boundary = sf::FloatRect(0, 0, game->width, game->height);

    treeNodeCapacity = 4, objectNum = 800, radius = 2.0;

    quadTree.setData(boundary, treeNodeCapacity);

    font = new sf::Font();
    font->loadFromFile("assets\\fonts\\soupofjustice.ttf");

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
    for (int i = 0; i < 4; i++)
    {
        textboxes.push_back(TextBox(*font));
        temp = textboxes[i].getGlobalBounds();
        textboxes[i].setOrigin(sf::Vector2f(temp.left + temp.width, temp.top));
        textboxes[i].setPosition(sf::Vector2f(game->width, i * temp.height * 1.5));
        textboxes[i].setTextFormat(sf::Color::White, characterSize);
        textboxes[i].setSize(sf::Vector2f(100, characterSize));
        textboxes[i].setBorder(2, sf::Color::White, sf::Color::Black, sf::Color::Magenta);
        textboxes[i].allowNumberOnly();

        labels.push_back(sf::Text());
        labels[i].setFont(*font);
        switch (i)
        {
        case 0:
            labels[i].setString("Object Num:  ");
            break;
        case 1:
            labels[i].setString("Radius:  ");
            break;
        case 2:
            labels[i].setString("Speed:  ");
            break;
        case 3:
            labels[i].setString("Node Capacity:  ");
            break;
        }

        labels[i].setCharacterSize(characterSize);
        labels[i].setFillColor(sf::Color::White);
        labels[i].setPosition(sf::Vector2f(game->width - textboxes[i].getGlobalBounds().width - labels[i].getGlobalBounds().width, i * temp.height * 1.5));
    }

    textboxes[0].setString(std::to_string(objectNum));
    textboxes[0].setTextLimit(5);

    textboxes[1].setString(std::to_string(radius).substr(0, 3));
    textboxes[1].setTextLimit(3);

    textboxes[2].setString(std::to_string(particleSpeed).substr(0, 3));
    textboxes[2].setTextLimit(3);

    textboxes[3].setString(std::to_string(treeNodeCapacity));
    textboxes[3].setTextLimit(2);

    for (int i = 0; i < 6; i++)
        buttons.push_back(Button(*font));

    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i].setFont(*font);
        buttons[i].setCharacterSize(characterSize);
        buttons[i].setBorder(sf::Color(100, 100, 100, 100), 2);
        buttons[i].setTextColor(sf::Color::White);
        buttons[i].setPosition(sf::Vector2f(game->width - buttons[i].getGlobalBounds().width, textboxes[textboxes.size() - 1].getPosition().y + textboxes[textboxes.size() - 1].getGlobalBounds().height * 1.85 * (i + 1)));
    }

    buttons[0].setPosition(sf::Vector2f(game->width - buttons[0].getGlobalBounds().width, textboxes[textboxes.size() - 1].getPosition().y + textboxes[textboxes.size() - 1].getGlobalBounds().height * 1.75));
    buttons[4].setPosition(sf::Vector2f(buttons[4].getPosition().x, buttons[4].getPosition().y - buttons[4].getGlobalBounds().height));
    buttons[5].setPosition(sf::Vector2f(buttons[5].getPosition().x, buttons[5].getPosition().y - buttons[5].getGlobalBounds().height));
    
    
    buttons[0].setString("Apply");
    buttons[0].setOnAction([&]()
                           {
        for (ushort i = 0; i < textboxes.size(); i++)
                if (textboxes[i].getString().length() == 0 || textboxes[i].getString() == "0")
                    return;

        objectNum = std::stoi(textboxes[0].getString());
        radius = std::stof(textboxes[1].getString());
        initializeObjects(); });

    buttons[1].setString("Pause");
    buttons[1].setOnAction([&]()
                           {
        pause = !pause;
        buttons[1].setString(pause ? "Resume" : "Pause"); });

    buttons[2].setString("        Show\nMouse Query");
    buttons[2].setOnAction([&]()
                           {
        showMouseRect = !showMouseRect;
        buttons[2].setString(showMouseRect ? "         Hide\nMouse Query" : "        Show\nMouse Query"); });

    buttons[3].setString("Show QuadTree");

    buttons[3].setOnAction([&]()
                           {
        showQuadTree = !showQuadTree;
        buttons[3].setString(showQuadTree ? "Hide QuadTree" : "Show QuadTree"); });

    buttons[4].setString("Randomize");

    buttons[4].setOnAction([&]()
                           {
        for (ushort i = 0; i < myObjects.size(); i++)
            myObjects[i].setPosition(sf::Vector2f((rand() % (int)boundary.width), ((rand() % (int)boundary.height)))); });

    buttons[5].setString("Brush Mode");
    buttons[5].setOnAction([&]()
                           {
        brushMode = !brushMode;
        buttons[5].setString(brushMode ? "Cancel Brush Mode" : "Brush Mode"); });
}

void MainScreen::handleInput()
{
    sf::Event event;

    while (game->window->pollEvent(event))
    {
        for (int i = 0; i < textboxes.size(); i++)
            textboxes[i].handleInput(event);

        for (int i = 0; i < buttons.size(); i++)
            buttons[i].handleInput(event);

        if (event.type == sf::Event::Closed)
            game->window->close();

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                pressed = true;
        }

        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                pressed = false;
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
                buttons[0].getOnAction()();
                break;
            }
        }
    }
}

void MainScreen::update(const float dt)
{
    for (int i = 0; i < buttons.size(); i++)
        buttons[i].update(game->window);

    for (ushort i = 0; i < textboxes.size(); i++)
        textboxes[i].update(game->window);

    // reconstructing the tree every frame
    quadTree.reset();

    if (brushMode && pressed)
        brush();

    // inserting all the objects into the tree every frame
    for (ushort i = 0; i < myObjects.size(); i++)
    {
        myObjects[i].setColor(defaultColor);
        quadTree.insert(&myObjects[i]);
    }

    for (ushort i = 0; i < myObjects.size(); i++)
    {
        // already queried the object for collisions
        if (myObjects[i].getColor() == collisionColor)
            continue;

        // query the quadtree for each object's global bounds and store the results in myCollisions
        quadTree.query(myObjects[i].getGlobalBounds(), myCollisions);

        for (ushort j = 0; j < myCollisions.size(); j++)
            if (Collision::ParticleCollision(myObjects[i], *myCollisions[j]))
            {
                // changing the color of the colliding objects
                myObjects[i].setColor(collisionColor);
                myCollisions[j]->setColor(collisionColor);
            }

        myCollisions.clear();
    }

    if (showMouseRect)
    {
        mouseRect.setPosition(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y);

        // query the quadtree for the mouseRect's global bounds
        quadTree.query(mouseRect.getGlobalBounds(), myCollisions);

        for (ushort i = 0; i < myCollisions.size(); i++)
            myCollisions[i]->setColor(mouseRectColor);

        myCollisions.clear();
    }

    if (!pause)
        moveObjects(particleSpeed, dt);

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
}

void MainScreen::draw()
{
    if (showQuadTree)
        quadTree.draw(game->window);

    for (ushort i = 0; i < myObjects.size() - 1; i++)
        myObjects[i].render(game->window);

    if (showMouseRect)
        game->window->draw(mouseRect);

    for (int i = 0; i < textboxes.size(); i++)
    {
        game->window->draw(labels[i]);
        textboxes[i].draw(game->window);
    }

    for (int i = 0; i < buttons.size(); i++)
        buttons[i].render(game->window);
}

void MainScreen::moveObjects(float speed, const float dt)
{
    // Objects move randomly
    sf::Vector2f velocity = sf::Vector2f(0, 0);

    for (ushort i = 0; i < myObjects.size(); i++)
    {
        velocity.x = (rand() % (int)speed - (speed) / 2);
        velocity.y = (rand() % (int)speed - (speed) / 2);
        myObjects[i].setVelocity(velocity);
        myObjects[i].update(dt, boundary);
    }
}

void MainScreen::initializeObjects()
{
    myObjects.clear();
    Particle circle(radius);
    for (ushort i = 0; i < objectNum; i++)
    {
        circle.setPosition(sf::Vector2f((rand() % (int)boundary.width), ((rand() % (int)boundary.height))));
        myObjects.push_back(circle);
    }
}

void MainScreen::brush()
{
    Particle circle(radius);
    circle.setPosition(sf::Vector2f(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y));
    myObjects.push_back(circle);
    textboxes[0].setString(std::to_string(objectNum));
}