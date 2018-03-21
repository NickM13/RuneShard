#include "engine\game\world\entity\actor\LActor.h"

std::map<std::string, Actor*> LActor::m_actorMap;

void LActor::loadDatabase() {

}
Actor* LActor::addActor(std::string p_actorName, Actor* p_actor) {
	m_actorMap.insert({p_actorName, p_actor});
	return p_actor;
}
bool LActor::contains(std::string p_actorName) {
	return (m_actorMap.find(p_actorName) != m_actorMap.end());
}
Actor* LActor::getActor(std::string p_actorName) {
	if(contains(p_actorName))
		return new Actor(*m_actorMap[p_actorName]);
	return 0;
}
