#include "Application.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#define FOREACHMODULES(fn) foreachModules([&](std::shared_ptr<IModule> module)fn);

void Application::run() {
	ImGui::SFML::Init(*window);

	FOREACHMODULES({ module->resourceInitialization();});

	sf::Clock deltaClock;
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			ImGui::SFML::ProcessEvent(event);
			FOREACHMODULES({ module->event(event); });
		}

		auto delta = deltaClock.restart();

		ImGui::SFML::Update(*window, delta);

		FOREACHMODULES({ module->update(window.get(), delta.asSeconds()); });

		window->clear();

		FOREACHMODULES({ module->frame(window.get()); });
		ImGui::SFML::Render();

		window->display();
	}

	ImGui::SFML::Shutdown();
}

