#pragma once

#include "EntityList.hpp"

class Player : public IEntity {
protected:
	sf::String name;
	sf::Vector2f position;
public:
	Player() = default;

	void setName(const sf::String& n) { name = n; }
	sf::String getName() const { return name; }
};