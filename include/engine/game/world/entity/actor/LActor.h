#pragma once
#include "Actor.h"
#include "adventurer\Adventurer.h"
#include "adventurer\mage\Mage.h"
#include "adventurer\warrior\Warrior.h"

// Library class for actors (not entity)
class LActor {
private:
	static std::map<std::string, Actor*> m_actorMap;
public:
	static void loadDatabase();
	// Add actor to actor library
	static void addActor(std::string p_actorName, Actor* p_actor);
	static bool contains(std::string p_actorName);
	// Returns new instance of actor
	static Actor* getActor(std::string p_actorName);
};
