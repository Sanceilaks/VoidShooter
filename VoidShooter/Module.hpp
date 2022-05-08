#pragma once

#include "Logging.hpp"
#include <SFML/Graphics.hpp>

#ifdef _DEBUG
#define DEFAULT_MODULE_FN(fnname) { \
	 static std::once_flag f; \
	 std::call_once(f, [&]() {LOG_WARNING("Module function {}::{} without defenition was called", (std::string)this->getModuleName(), #fnname); }); \
}
#else
#define DEFAULT_MODULE_FN(fnname) {}
#endif

#define INIT_MODULE(modulename) private: \
public: \
	virtual sf::String getModuleName() { \
		return #modulename; \
	} \
private:

class Application;

class IModule {
public:
	Application* App;

	virtual ~IModule() = default;
	explicit IModule(Application* app) : App(app) {}

	virtual sf::String getModuleName() = 0;

	virtual void frame(sf::RenderWindow* window) DEFAULT_MODULE_FN(Frame)
	virtual void update(sf::RenderWindow* window, float delta) DEFAULT_MODULE_FN(Update)
	virtual void event(const sf::Event& event) DEFAULT_MODULE_FN(Event)
	virtual void resourceInitialization() DEFAULT_MODULE_FN(ResuourceInitialization)
};