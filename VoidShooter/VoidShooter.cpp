#include "Application.hpp"
#include "EntityList.hpp"
#include "Game.hpp"
#include "Scripts.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

int main() {
	set_default_logger(spdlog::stdout_color_mt("console"));

	Application app("VoidShooter");
	app.registerModule(std::make_shared<ScriptSystem>(&app)).
		registerModule(std::make_shared<FontManager>(&app)).
		registerModule(std::make_shared<Game>(&app)).
		run();
}