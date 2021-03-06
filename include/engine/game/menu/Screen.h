#pragma once

#include "engine\utils\Singleton.h"
#include "engine\gfx\LGui.h"

class Screen
{
public:
	Screen(std::string p_name = "") { m_name = p_name; };
	~Screen() {};

	void addComponent(Component* p_comp, Anchor p_posAnchor, Anchor p_sizeAnchor)
	{
		m_gui.addComponent(p_comp, p_posAnchor, p_sizeAnchor);
	}

	std::string getName()
	{
		return m_name;
	}

	virtual void input()
	{
		m_gui.input();
	}

	virtual void update(GLfloat p_updateTime)
	{
		m_gui.update(p_updateTime);
	}

	virtual void render()
	{
		m_gui.render();
	}

protected:
	std::string m_name;
	Container m_gui;
};
