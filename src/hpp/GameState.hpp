#pragma once

class GameState {
public:
	virtual ~GameState() = default;

	virtual void draw() = 0;
	virtual void update(float dt) = 0;
	virtual void handleInput() = 0;
};
