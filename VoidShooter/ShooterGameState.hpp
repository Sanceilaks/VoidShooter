#include "GameState.hpp"

#include "LocalPlayer.hpp"
#include "EntityList.hpp"

enum class ShooterGameType {
	None,
	Singleplayer,
	Multiplayer
};

class ShooterGameState : public IGameState {
	ShooterGameType gameType = ShooterGameType::None;

	std::shared_ptr<LocalPlayer> localPlayer;
	std::shared_ptr<EntityList> entityList;
public:
	INITGAMESTATE(ShooterGameState);

	explicit ShooterGameState(const ShooterGameType type);

	ShooterGameState() = default;
	
	bool isSingleplayer() const { return gameType == ShooterGameType::Singleplayer; }
	bool isMultiplayer() const { return gameType == ShooterGameType::Multiplayer; }

	ShooterGameType getGameType() const { return gameType; }
	void setGameType(const ShooterGameType type) { if (gameType == ShooterGameType::None) gameType = type; }

	auto getLocalPlayer()  { return localPlayer; }
	auto getEntityList()  { return entityList; }
public:
	void onRender(sf::RenderWindow* window) override;
	void onUpdate(float delta) override;
	void onEvent(const sf::Event& event) override;
};