#pragma once

#include "engine\utils\Utilities.h"
#include "_Component.h"
#include "..\font\Font.h"
#include "engine\sfx\Sound.h"

class CButton : public Component
{
public:
	CButton(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme, function p_func = 0);
	CButton(std::string p_compName, std::string p_title, Texture p_buttonTex, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme, function p_func = 0);
	void input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos);
	void update(GLfloat p_deltaUpdate);
	void render();

	void setState(Sint8 p_selected);

	Sint8 isSelected(); // 0 = not selected, 1 = JUST pressed, 2 = is held, 3 = JUST released
	bool isHovered() {return m_hover;};
	void setHover(bool p_state) {m_hover = p_state;};
private:
	Texture m_buttonTex;

	bool m_hover;
	bool m_stuck;

	Source m_soundClick;
	Source m_soundHover;
};

class CButtonToggle : public Component
{
public:
	CButtonToggle(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme, Sint8 p_state = 0, function p_func = 0);
	CButtonToggle(std::string p_compName, Texture p_buttonTex, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme, Sint8 p_state = 0, function p_func = 0);
	CButtonToggle(std::string p_compName, Texture p_activeTex, Texture p_inactiveTex, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme, Sint8 p_state = 0, function p_func = 0);

	void input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos);
	void update(GLfloat p_deltaUpdate);
	void render();
private:
	Texture m_buttonTex[2];
	Sint8 m_texType;

	bool m_hover;

	Source m_soundClick;
	Source m_soundHover;
};


class CButtonRadio : public Component
{
public:
	CButtonRadio(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme);

	void addButton(CButtonToggle* p_button);

	void input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos);
	void update(GLfloat p_deltaUpdate);
	void render();

	void setSelectedButton(Uint16 p_selectedButton);
	Uint16 getSelectedButton();
	Uint16 getPrevSelectedButton();
private:
	Uint16 m_selectedButton, m_prevSelectedButton;

	std::vector<CButtonToggle*> m_buttonList;
};
