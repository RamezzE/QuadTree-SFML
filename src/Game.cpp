
#include <iostream>
#include "SFML/Graphics.hpp"

#include "Game.hpp"
#include "GameState.hpp"

Game::Game(ushort width, ushort height)
{
    this->width = width;
    this->height = height;

    window = new sf::RenderWindow(sf::VideoMode(width, height), "QuadTree Collisions", sf::Style::Titlebar | sf::Style::Close);

    // window->setFramerateLimit(60);
}

void Game::changeScreen(GameState *state)
{
    pushState(state);
}

void Game::previousScreen()
{
    popState();
}

void Game::pushState(GameState *state)
{
    states.push_back(state);
}

void Game::popState()
{
    delete states.back();
    states.pop_back();
}

Game::~Game()
{
    while (!states.empty())
        popState();
}

GameState *Game::CurrentState()
{
    if (states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::gameLoop()
{
    sf::Clock clk;
    float dt;
    while (window->isOpen())
    {
        dt = clk.restart().asSeconds();

        if (CurrentState() == nullptr)
            continue;

        CurrentState()->handleInput();

        CurrentState()->update(dt);

        window->clear();

        CurrentState()->draw();

        window->display();
    }
}
