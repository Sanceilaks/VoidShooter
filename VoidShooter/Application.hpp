#pragma once

#include "Logging.hpp"
#include "Module.hpp"

#include <SFML/Graphics.hpp>
#include <utility>

class Application {
	sf::String applicationName;
	std::shared_ptr<sf::RenderWindow> window;
	std::vector<std::shared_ptr<IModule>> modules;

	void foreachModules(std::function<void(std::shared_ptr<IModule>)> callback) {
		std::ranges::for_each(modules, std::move(callback));
	}
public:
	explicit Application(const sf::String& appname) {
		window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), appname);
		applicationName = appname;
	}

	void run();
	auto getWindow() { return window; }

	auto& registerModule(std::shared_ptr<IModule> module) {
		modules.emplace_back(module);
		return *this;
	}

	template <typename T>
	std::shared_ptr<T> getModule(const sf::String& name) {
		foreachModules([&](std::shared_ptr<IModule> m) {
			if (m->getModuleName() == name)
				return m;
		});
		return 0;
	}
};