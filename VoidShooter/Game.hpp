#pragma once

#include "Module.hpp"
#include "GameState.hpp"

class Game;

namespace G {
	inline Game* GameMod;
}

class Game final : public IModule {
	INIT_MODULE(Game);

	std::shared_ptr<IGameState> gameState;
public:
	explicit Game(Application* app) : IModule(app) {
		G::GameMod = this;
	}

	template <typename GS, typename ...Args> void changeGameState(Args... params) {
		gameState = std::make_shared<GS>(std::forward<Args>(params)...);
	}

	template <typename GameStateType> std::shared_ptr<GameStateType> getGameState() { return gameState; }

	~Game() override = default;

	void frame(sf::RenderWindow* window) override {
		gameState->onRender(window);
	}

	void update(sf::RenderWindow* window, float delta) override {
		gameState->onUpdate(delta);
	}

	void event(const sf::Event& event) override {
		gameState->onEvent(event);
	}
	void resourceInitialization() override;
};