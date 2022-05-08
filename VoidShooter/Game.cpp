#include "Game.hpp"

#include "MenuGameState.hpp"

void Game::resourceInitialization() {
	changeGameState<MenuGameState>();
}
