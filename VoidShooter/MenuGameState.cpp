#include "MenuGameState.hpp"

#include "Game.hpp"
#include "ShooterGameState.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "Scripts.hpp"

void MenuGameState::onRender(sf::RenderWindow* window) {
	ImGui::SetNextWindowSize(ImVec2{ (float)window->getSize().x, (float)window->getSize().y });
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::Begin("##WINDOW");

	static sf::String str;

	if (ImGui::Button("Hello!")) {
		str += "Test String!\n";
	}

	ImGui::SameLine();

	if (ImGui::Button("To Game")) {
		G::GameMod->changeGameState<ShooterGameState>(ShooterGameType::Singleplayer);
	}

	ImGui::SameLine();

	if (ImGui::Button("Lua files")) {
		G::Scripts->runDirectory(std::filesystem::current_path());
	}

	ImGui::TextWrapped(str.toAnsiString().c_str());

	ImGui::End();
}

void MenuGameState::onUpdate(float delta) {

}

void MenuGameState::onEvent(const sf::Event& event) {

}
