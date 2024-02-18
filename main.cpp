#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/hpp/Game.hpp"
#include "src/hpp/MainScreen.hpp"

typedef unsigned short ushort;

ushort myWidth, myHeight;

sf::Color defaultColor = sf::Color(0, 255, 0, 255);
sf::Color collisionColor = sf::Color(255, 0, 0, 255);
sf::Color mouseRectColor = sf::Color::Magenta;

sf::Color quadTreeColor = sf::Color::White;
float particleSpeed = 100.f, radius = 3.f;

float borderWeight = 1.f;
bool showQuadTree = false, showMouseRect = false;

int main()
{
    srand(time(NULL));

    const ushort screenWidth = sf::VideoMode::getDesktopMode().width * 0.75f;
    const ushort screenHeight = sf::VideoMode::getDesktopMode().height* 0.75f;

    myWidth = screenWidth;
    myHeight = screenHeight;

    Game myGame(screenWidth, screenHeight);
    myGame.changeScreen(new MainScreen(&myGame));
    myGame.gameLoop();
}