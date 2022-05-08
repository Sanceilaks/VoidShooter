#include "ShooterGameState.hpp"

ShooterGameState::ShooterGameState(const ShooterGameType type) {
	gameType = type;

	entityList = std::make_shared<EntityList>();

	localPlayer = std::make_shared<LocalPlayer>();
	entityList->addEntity(localPlayer);

	localPlayer->setName("voidptr_t");
}

void ShooterGameState::onRender(sf::RenderWindow* window) {
	entityList->render(window);
}

void ShooterGameState::onUpdate(float delta) {
	entityList->update(delta);
}

void ShooterGameState::onEvent(const sf::Event& event) {

}
