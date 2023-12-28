#include "../hpp/MainScreen.hpp"
#include "../hpp/Common.hpp"

#include <iomanip>
#include <SFML/Graphics.hpp>

extern sf::Color defaultColor, collisionColor, mouseRectColor;
extern bool showQuadTree, showMouseRect;
extern float particleSpeed;

static sf::Vector2f button5Position;

MainScreen::MainScreen(Game* game) {
    this->game = game;

    pause = brushMode = pressed = false;
    boundary = sf::FloatRect(0, 0, game->width * 0.6, game->height);

    treeNodeCapacity = 4, objectNum = 800, radius = 2.0;

    quadTree.setData(boundary, treeNodeCapacity);

    font = new sf::Font();
    font->loadFromFile("assets\\fonts\\soupofjustice.ttf");

    initializeObjects();

    mouseRect.setSize(sf::Vector2f(game->height / 3.f, game->height / 3.f));
    mouseRect.setFillColor(sf::Color::Transparent);
    mouseRect.setOutlineThickness(2);
    mouseRect.setOutlineColor(mouseRectColor);
    const sf::FloatRect temp = mouseRect.getGlobalBounds();
    mouseRect.setOrigin(temp.left + temp.width / 2, temp.top + temp.height / 2);

    fpsLabel.setFont(*font);

    for (int i = 0; i < 4; i++) {
        textboxes.emplace_back(*font);
        textboxes[i].setBorder(2, sf::Color::White, sf::Color::Black, sf::Color::White);
        textboxes[i].allowNumberOnly();
        textboxes[i].setBackgroundColor(sf::Color(100, 100, 100, 100));

        labels.emplace_back();
        labels[i].setFont(*font);

        switch (i) {
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
            default:
                labels[i].setString("Label");
                break;
        }
    }

    for (int i = 0; i < 6; i++)
        buttons.emplace_back(*font);


    buttons[0].setOnAction([&]() {
        for (auto& textbox: textboxes)
            if (textbox.empty() || textbox.getString() == "0" || textbox.getString() == "0.")
                return;

        bool noChange = true;

        if (std::stof(textboxes[1].getString()) != radius) {
            radius = std::stof(textboxes[1].getString());
            noChange = false;
        }

        if (std::stof(textboxes[2].getString()) != particleSpeed) {
            particleSpeed = std::stof(textboxes[2].getString());
            noChange = false;
        }

        if (std::stoi(textboxes[3].getString()) != treeNodeCapacity) {
            quadTree.setData(boundary, std::stoi(textboxes[3].getString()));
            noChange = false;
        }

        if (std::stoi(textboxes[0].getString()) != objectNum) {
            objectNum = std::stoi(textboxes[0].getString());
            noChange = false;
        }

        if (!noChange)
            initializeObjects();
    });

    buttons[1].setOnAction([&]() {
        pause = !pause;
        buttons[1].setString(pause ? "Resume" : "Pause");
        buttons[1].setBackgroundColor(pause ? sf::Color(100, 100, 100, 150) : sf::Color::Black);
    });

    buttons[2].setOnAction([&]() {
        showMouseRect = !showMouseRect;
        buttons[2].setString(showMouseRect ? "Hide Mouse Query" : "Show Mouse Query");
        buttons[2].setBackgroundColor(showMouseRect ? sf::Color(100, 100, 100, 150) : sf::Color::Black);
    });

    buttons[3].setOnAction([&]() {
        showQuadTree = !showQuadTree;
        buttons[3].setString(showQuadTree ? "Hide QuadTree" : "Show QuadTree");
        buttons[3].setBackgroundColor(showQuadTree ? sf::Color(100, 100, 100, 150) : sf::Color::Black);
    });

    buttons[4].setOnAction([&]() {
        for (auto& myObject: myObjects)
            myObject.setPosition(sf::Vector2f((rand() % static_cast<int>(boundary.width)),
                                              ((rand() % static_cast<int>(boundary.height)))));
    });

    buttons[5].setOnAction([&]() {
        brushMode = !brushMode;
        buttons[5].setString(brushMode ? "Cancel Brush Mode" : "Brush Mode");
        buttons[5].setPosition((brushMode
                                    ? sf::Vector2f(button5Position.x - buttons[5].getGlobalBounds().width / 6,
                                                   button5Position.y)
                                    : button5Position));
        buttons[5].setBackgroundColor(brushMode ? sf::Color(100, 100, 100, 150) : sf::Color::Black);
    });

    init();
    init();
}

void MainScreen::init() {
    float marginRight = game->width / 100;

    if (marginRight < 10)
        marginRight = 10;
    else if (marginRight > 20)
        marginRight = 20;

    float characterSize = game->width / 30;
    if (characterSize < 25)
        characterSize = 25;
    else if (characterSize > 50)
        characterSize = 50;

    float textBoxWidth = game->width / 10;
    if (textBoxWidth < 50)
        textBoxWidth = 50;
    else if (textBoxWidth > 100)
        textBoxWidth = 100;

    for (int i = 0; i < 4; i++) {
        textboxes[i].setTextFormat(sf::Color::White, characterSize);
        textboxes[i].setSize(sf::Vector2f(textBoxWidth, characterSize));
        textboxes[i].setPosition(sf::Vector2f(game->width - textBoxWidth - marginRight, game->height * 0.075 * i));

        labels[i].setCharacterSize(characterSize);
        labels[i].setFillColor(sf::Color::White);
        labels[i].setPosition(sf::Vector2f(
            textboxes[i].getGlobalBounds().left - labels[i].getGlobalBounds().width,
            game->height * 0.075 * i));
    }


    textboxes[0].setString(std::to_string(objectNum));
    textboxes[0].setTextLimit(5);

    textboxes[1].setString(std::to_string(radius).substr(0, 3));
    textboxes[1].setTextLimit(2);

    textboxes[2].setString(std::to_string(particleSpeed).substr(0, 3));
    textboxes[2].setTextLimit(3);

    textboxes[3].setString(std::to_string(treeNodeCapacity));
    textboxes[3].setTextLimit(2);


    fpsLabel.setCharacterSize(characterSize);
    fpsLabel.setFillColor(sf::Color::White);
    fpsLabel.setPosition(0.025f * game->width, 0.025f * game->height);

    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].setBorder(sf::Color(100, 100, 100, 100), 2);
        buttons[i].setFont(*font);
        buttons[i].setCharacterSize(characterSize);
        buttons[i].setTextColor(sf::Color::White);
        buttons[i].setPosition(sf::Vector2f(
            game->width - marginRight - buttons[i].getGlobalBounds().width/2,
            game->height * 0.35 + (game->height * 0.1 * i+1)
            ));
    }

    button5Position = buttons[5].getPosition();

    buttons[0].setString("Apply");
    buttons[1].setString("Pause");
    buttons[2].setString("Show Mouse Query");
    buttons[3].setString("Show QuadTree");
    buttons[4].setString("Randomize");
    buttons[5].setString("Brush Mode");
}

void MainScreen::handleInput() {
    sf::Event event;

    while (game->window->pollEvent(event)) {
        for (auto& textbox: textboxes)
            textbox.handleInput(event);

        for (auto& button: buttons)
            button.handleInput(event);

        if (event.type == sf::Event::Closed)
            game->window->close();

        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left)
                pressed = true;
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left)
                pressed = false;
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
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
        } else if (event.type == sf::Event::Resized) {
            resize(event);
            return;
        }
    }
}

void MainScreen::update(const float dt) {
    if (fpsTimer.getElapsedTime().asSeconds() >= 1) {
        fpsTimer.restart();
        fpsLabel.setString("FPS: " + std::to_string((int) (1 / dt)));
    }

    for (auto& button: buttons)
        button.update(game->window);

    for (auto& textboxe: textboxes)
        textboxe.update(game->window);

    // reconstructing the tree every frame
    quadTree.reset();

    if (brushMode && pressed)
        brush();

    // inserting all the objects into the tree every frame
    for (auto& myObject: myObjects) {
        myObject.setColor(defaultColor);
        quadTree.insert(&myObject);
    }

    for (auto& myObject: myObjects) {
        // already queried the object for collisions
        if (myObject.getColor() == collisionColor)
            continue;

        // query the quadtree for each object's global bounds and store the results in myCollisions
        quadTree.query(myObject.getGlobalBounds(), myCollisions);

        for (const auto& myCollision: myCollisions)
            if (Collision::ParticleCollision(myObject, *myCollision)) {
                // changing the color of the colliding objects
                myObject.setColor(collisionColor);
                myCollision->setColor(collisionColor);
            }

        myCollisions.clear();
    }

    if (showMouseRect) {
        mouseRect.setPosition(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y);

        // query the quadtree for the mouseRect's global bounds
        quadTree.query(mouseRect.getGlobalBounds(), myCollisions);

        for (const auto& myCollision: myCollisions)
            myCollision->setColor(mouseRectColor);

        myCollisions.clear();
    }

    if (!pause)
        moveObjects(dt);
}

void MainScreen::draw() {
    if (showQuadTree)
        quadTree.draw(game->window);

    for (auto& myObject: myObjects)
        myObject.render(game->window);

    if (showMouseRect)
        game->window->draw(mouseRect);

    game->window->draw(fpsLabel);

    for (int i = 0; i < textboxes.size(); i++) {
        game->window->draw(labels[i]);
        textboxes[i].draw(game->window);
    }

    for (const auto& button: buttons)
        button.render(game->window);
}

void MainScreen::moveObjects(const float dt) {
    // Objects move randomly

    for (auto& myObject: myObjects)
        myObject.update(dt, boundary);
}

void MainScreen::initializeObjects() {
    myObjects.clear();
    Particle particle(radius);
    for (ushort i = 0; i < objectNum; i++) {
        particle.setPosition(sf::Vector2f((rand() % (int) boundary.width), ((rand() % (int) boundary.height))));
        particle.setVelocity(sf::Vector2f((rand() % (int) particleSpeed - (particleSpeed) / 2),
                                          (rand() % (int) particleSpeed - (particleSpeed) / 2)));
        myObjects.push_back(particle);
    }
}

void MainScreen::brush() {
    if (sf::Mouse::getPosition(*(game->window)).x > boundary.getPosition().x + boundary.getSize().x
        || sf::Mouse::getPosition(*(game->window)).x < boundary.getPosition().x
        || sf::Mouse::getPosition(*(game->window)).y > boundary.getPosition().y + boundary.getSize().y
        || sf::Mouse::getPosition(*(game->window)).y < boundary.getPosition().y)

        return;

    Particle particle(radius);

    particle.setPosition(sf::Vector2f(sf::Mouse::getPosition(*(game->window)).x,
                                      sf::Mouse::getPosition(*(game->window)).y));
    particle.setVelocity(sf::Vector2f((rand() % static_cast<int>(particleSpeed) - (particleSpeed) / 2),
                                      (rand() % static_cast<int>(particleSpeed) - (particleSpeed) / 2)));
    myObjects.push_back(particle);
    objectNum++;
    textboxes[0].setString(std::to_string(objectNum));
}

void MainScreen::resize(const sf::Event& event) {
    const sf::FloatRect visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
    game->window->setView(sf::View(visibleArea));

    game->width = event.size.width;
    game->height = event.size.height;
    boundary = sf::FloatRect(0, 0, game->width * 0.6, game->height);
    quadTree.setData(boundary, treeNodeCapacity);

    for (auto& myObject: myObjects) {
        if (myObject.getPosition().x > boundary.width)
            myObject.setPosition(sf::Vector2f(boundary.width, myObject.getPosition().y));

        if (myObject.getPosition().y > boundary.height)
            myObject.setPosition(sf::Vector2f(myObject.getPosition().x, boundary.height));
    }

    init();
}
