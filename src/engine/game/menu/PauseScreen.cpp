#include "engine\game\menu\PauseScreen.h"

#include "engine\game\menu\ingame\PSMain.h"
#include "engine\game\menu\ingame\PSOptions.h"

PauseScreen::PauseScreen()
{
	m_background = Panel("PANEL_BACKGROUND", "", GScreen::m_screenSize / -2, GScreen::m_screenSize, Component::Theme::PRIMARY, Component::Border::BORDER_ALL);

	m_screens.push_back(new Screen("None"));
	m_screens.push_back(new PSMain());
	m_screens.push_back(new PSOptions());
}

bool PauseScreen::isPaused()
{
	return (m_currScreen != 0);
}
Uint16 PauseScreen::getScreen()
{
	return m_currScreen;
}
Screen PauseScreen::getScreen(Uint16 p_guid)
{
	return *m_screens[p_guid];
}

void PauseScreen::setScreen(Uint16 p_screen)
{
	m_currScreen = p_screen;
}
void PauseScreen::setScreen(std::string p_screen)
{
	for(Uint16 i = 0; i < m_screens.size(); i++)
	{
		if(m_screens[i]->getName() == p_screen)
		{
			m_currScreen = i;
			return;
		}
	}
}

void PauseScreen::input()
{
	if(m_currScreen != 0)
		m_screens[m_currScreen]->input();
}
void PauseScreen::update(GLfloat p_updateTime)
{
	if(m_currScreen != 0)
		m_screens[m_currScreen]->update(p_updateTime);
}
void PauseScreen::render()
{
	if(m_currScreen != 0)
	{
		m_background.render();

		m_screens[m_currScreen]->render();
	}
}
