#pragma once

#include <vector>
#include "SFML/Graphics.hpp"

#include "GameState.hpp"

typedef unsigned short ushort;

class Game {
public:
	Game(float width, float height);
	~Game();

	void changeScreen(GameState* state);
	void previousScreen();

	void gameLoop();

	sf::RenderWindow* window;

    float width, height;
	float height_;

private:
	std::vector<GameState*> states;
	GameState* CurrentState() const;
	
	void pushState(GameState* state);
	void popState();

	
};