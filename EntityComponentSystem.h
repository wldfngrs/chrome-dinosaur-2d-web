#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <bitset>
#include <array>

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;

inline ComponentID getUniqueComponentID() {
	static ComponentID lastID{ 0u };
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID{ getUniqueComponentID() };
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* mEntity = nullptr;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity {
	EntityManager& mEntityManager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> mComponents;

	ComponentArray mComponentArray;
	ComponentBitset mComponentBitset;

public:
	int mEntityIndex = 0;

	Entity(EntityManager& mManager) : mEntityManager(mManager) {}
	
	void update() {
		for (auto& c : mComponents) c->update();
	}

	void draw() {
		for (auto& c : mComponents) c->draw();
	}

	bool isActive() const { return active; }
	bool isInactive() const { return !active; }
	void wakeUp() { active = true; }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const {
		return mComponentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... margs) {
		assert(!hasComponent<T>());

		T* c(new T(std::forward<TArgs>(margs)...));
		c->mEntity = this;
		std::unique_ptr<Component> uPtr{ c };
		mComponents.emplace_back(std::move(uPtr));

		mComponentArray[getComponentTypeID<T>()] = c;
		mComponentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const {
		assert(hasComponent<T>());
		auto ptr(mComponentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class EntityManager {
	std::vector<std::unique_ptr<Entity>> mEntities;

public:
	void update() {
		for (auto& e : mEntities) e->update();
	}

	void draw() {
		for (auto& e : mEntities) e->draw();
	}

	void refresh() {
		mEntities.erase(std::remove_if(std::begin(mEntities), std::end(mEntities), 
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
		std::end(mEntities));
	}

	Entity& addEntity() {
		static int index = 0;
		Entity* a = new Entity(*this);
		a->mEntityIndex = index++;
		std::unique_ptr<Entity> uPtr{ a };
		mEntities.emplace_back(std::move(uPtr));
		return *a;
	}

	std::vector<std::unique_ptr<Entity>>& getEntities() {
		return mEntities;
	}
};