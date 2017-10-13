#pragma once

#include "Screen.h"

class PauseScreen : public Singleton<PauseScreen>
{
public:
	PauseScreen();

	bool isPaused();
	Uint16 getScreen();
	Screen getScreen(Uint16 p_guid);

	void setScreen(Uint16 p_screen);
	void setScreen(std::string p_screen);

	void input();
	void update(GLfloat p_updateTime);
	void render();
private:
	std::vector<Screen*> m_screens;
	Uint16 m_currScreen;
	Panel m_background;
};
