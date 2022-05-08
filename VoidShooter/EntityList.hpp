#pragma once

#include "Application.hpp"
#include "FontManager.hpp"

#include <SFML/System.hpp>

class EntityList;

class IEntity {
protected:
	int index = -1;

public:
	virtual ~IEntity() = default;

	virtual void render(sf::RenderWindow* window) {}
	virtual void update(float delta) {}

	void setId(const int id) {
		this->index = id;
	}

	virtual int getId() const {
		return index;
	}
};

class EntityList {
	INIT_MODULE(EntityList)
	std::vector<std::shared_ptr<IEntity>> entities;
public:
	explicit EntityList() {}

	auto& getEntities() { return entities; }

	template<typename T> std::shared_ptr<T> getEntity(const int id) {
		return entities.at(id);
	}

	auto& addEntity(const std::shared_ptr<IEntity>& ent) {
		auto e = entities.emplace_back(ent);
		ent->setId(entities.size() - 1);
		return e;
	}

	void render(sf::RenderWindow* window) {
		#ifdef _DEBUG
		sf::Text text(std::format("Total entities: {}", entities.size()), G::FontMgr->StandardFont);
		text.setPosition(0, 0);
		text.setCharacterSize(12);
		window->draw(text);
		#endif

		std::ranges::for_each(entities, [&](std::shared_ptr<IEntity> e) {
			e->render(window);
		});
	}

	void update(float delta) {
		std::ranges::for_each(entities, [&](std::shared_ptr<IEntity> e) {
			e->update(delta);
		});
	}
};