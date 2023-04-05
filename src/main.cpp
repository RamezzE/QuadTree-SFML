//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "Game.hpp"
#include "MainScreen.hpp"

typedef unsigned short ushort;

ushort myWidth, myHeight;

sf::Color defaultColor = sf::Color::Cyan; 
sf::Color collisionColor = sf::Color::Magenta;

sf::Color quadTreeColor = sf::Color::Red;
float particleSpeed = 100.f, radius = 5.f;

float borderWeight = 0.5f;
bool showQuadTree = false;

int main()
{
    // Show or hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, 0);

    srand(time(NULL));

    ushort screenWidth = sf::VideoMode::getDesktopMode().width * 0.5;
    ushort screenHeight = sf::VideoMode::getDesktopMode().height * 0.5;

    myWidth = screenWidth;
    myHeight = screenHeight;

    Game myGame(screenWidth, screenHeight);
    myGame.changeScreen(new MainScreen(&myGame));
    myGame.gameLoop();

}