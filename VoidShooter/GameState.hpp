#pragma once

#include <SFML/Graphics.hpp>

#define INITGAMESTATE(name) \
	public: \
		sf::String getName() override { return #name; } \

class Game;

class IGameState {
public:
	virtual sf::String getName() = 0;
	virtual void onRender(sf::RenderWindow* window) = 0;
	virtual void onUpdate(float delta) = 0;
	virtual void onEvent(const sf::Event& event) = 0;
};