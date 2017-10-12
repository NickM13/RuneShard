#pragma once

#define PANEL_ALIGN_NONE				0
#define PANEL_ALIGN_CENTER				1
#define PANEL_ALIGN_LEFT				2
#define PANEL_ALIGN_RIGHT				3
#define PANEL_ALIGN_TOP					4
#define PANEL_ALIGN_BOTTOM				5
#define PANEL_ALIGN_TOP_LEFT			6
#define PANEL_ALIGN_TOP_RIGHT			7
#define PANEL_ALIGN_BOTTOM_LEFT			8
#define PANEL_ALIGN_BOTTOM_RIGHT		9

#include "_Component.h"
#include "..\font\Font.h"

#include "engine\utils\Globals.h"
#include <algorithm>


class Container : public Component
{
protected:
	struct Comp
	{
		Sint8 m_alignment;
		Component* m_component;
		Comp(Sint8 p_align, Component* p_comp) : m_alignment(p_align), m_component(p_comp)
		{}
	};
	std::vector<Comp> m_componentList;
	Vector4<Sint32> m_contentArea;
public:
	Container() {};
	Container(std::string p_compName, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, bool p_visible);

	virtual Component* addComponent(Component* p_component, Sint8 p_alignment = PANEL_ALIGN_NONE);
	Component* findComponent(std::string p_compName);

	void setVisible(bool p_visible);

	Vector2<Sint32> getRealPosition();
	Vector2<Sint32> getRealSize();

	void updateSize();

	void input();
	void input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos);
	void update(GLfloat p_updateTime);
	void render();
};
