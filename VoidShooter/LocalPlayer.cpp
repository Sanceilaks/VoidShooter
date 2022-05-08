#include "LocalPlayer.hpp"

#define SPEED 200 

void LocalPlayer::render(sf::RenderWindow* window) {
	sf::CircleShape body;
	body.setPosition(position);
	body.setFillColor(sf::Color::Red);
	body.setRadius(24);

	sf::Text renderName;
	renderName.setString(name);
	renderName.setFont(G::FontMgr->StandardFont);
	renderName.setCharacterSize(14);
	renderName.setPosition(position - sf::Vector2f{0, body.getRadius() / 2.f + 14.f});

	window->draw(body);
	window->draw(renderName);
}

void LocalPlayer::update(float delta) {
	sf::Vector2f velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y += SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= SPEED;

	position += velocity * delta;
}

LocalPlayer::~LocalPlayer() = default;
