//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "Game.hpp"
#include "MainScreen.hpp"

typedef unsigned short ushort;

ushort myWidth, myHeight;

int main()
{
    // Show or hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, 0);

    srand(time(NULL));
    
    // myWidth = sf::VideoMode::getDesktopMode().width;
    // myHeight = sf::VideoMode::getDesktopMode().height;

    ushort screenWidth = sf::VideoMode::getDesktopMode().width * 0.5;
    ushort screenHeight = sf::VideoMode::getDesktopMode().height * 0.5;

    myWidth = screenWidth;
    myHeight = screenHeight;

    Game myGame(screenWidth, screenHeight);
    myGame.changeScreen(new MainScreen(&myGame));
    myGame.gameLoop();

}