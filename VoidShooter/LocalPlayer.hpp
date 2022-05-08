#pragma once

#include "Player.hpp"

class LocalPlayer: public Player {
public:
	

	void render(sf::RenderWindow* window) override;
	void update(float delta) override;
	~LocalPlayer() override;
};