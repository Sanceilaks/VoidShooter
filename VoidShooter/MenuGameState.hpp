#pragma once

#include "GameState.hpp"

class MenuGameState : public IGameState {
public:
	INITGAMESTATE(MenuGameState);
	
	MenuGameState() = default;

	void onRender(sf::RenderWindow* window) override;
	void onUpdate(float delta) override;
	void onEvent(const sf::Event& event) override;
};
