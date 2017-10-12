#pragma once

#include "Entity.h"
#include "character\Character.h"
#include "engine\utils\variable\manager\Manager.h"

class MEntity
{
private:
	std::vector<Entity*> m_entityList;
public:
	void addEntity(Entity* p_entity)
	{
		m_entityList.push_back(p_entity);
	}
	void input()
	{
		for(Sint16 i = Sint16(m_entityList.size()) - 1; i >= 0; i--)
			m_entityList[i]->input();
	}
	void update(WorldData &p_world, GLfloat p_updateTime)
	{
		for(Sint16 i = Sint16(m_entityList.size()) - 1; i >= 0; i--)
			m_entityList[i]->update(p_world, p_updateTime);
	}
	void render()
	{
		for(Sint16 i = Sint16(m_entityList.size()) - 1; i >= 0; i--)
			m_entityList[i]->render();
	}
};
