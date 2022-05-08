#pragma once

#include "Application.hpp"

class FontManager;

namespace G {
	inline FontManager* FontMgr = nullptr;
}

class FontManager final : public IModule {
	INIT_MODULE(FontManager);
public:
	sf::Font StandardFont;

	explicit FontManager(Application* app)
		: IModule(app) {
		G::FontMgr = this;
	}

	void resourceInitialization() override {
		StandardFont.loadFromFile(R"(C:\Windows\Fonts\arial.ttf)");
	}
};