#include <iostream>
#include <SFML/Graphics.hpp>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "Game.hpp"
#include "MainScreen.hpp"

typedef unsigned short ushort;

ushort myWidth, myHeight;

sf::Color defaultColor = sf::Color(150, 150, 150, 255);
sf::Color collisionColor = sf::Color(0, 200, 255, 255);
sf::Color mouseRectColor = sf::Color::Magenta;

sf::Color quadTreeColor = sf::Color::Yellow;
float particleSpeed = 100.f, radius = 3.f;

float borderWeight = 1.f;
bool showQuadTree = false, showMouseRect = false;

int main()
{
    // Show or hide console window if on windows
#if defined(_WIN32) || defined(_WIN64)
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, 0);
#endif

    srand(time(NULL));

    ushort screenWidth = sf::VideoMode::getDesktopMode().width * 0.5;
    ushort screenHeight = sf::VideoMode::getDesktopMode().height * 0.5;

    myWidth = screenWidth;
    myHeight = screenHeight;

    Game myGame(screenWidth, screenHeight);
    myGame.changeScreen(new MainScreen(&myGame));
    myGame.gameLoop();
}