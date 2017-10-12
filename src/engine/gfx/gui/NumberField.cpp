#include "engine\gfx\gui\NumberField.h"


NumberField::NumberField(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Vector2<Sint32> p_numBounds, Sint32 p_numValue, Sint8 p_colorTheme)
{
	m_compName = p_compName;
	m_title = p_title;
	m_pos = p_pos;
	m_size = Vector2<Sint32>(p_size.x, Sint32(p_size.y * Font::getInstance().getSpacingHeight()));
	m_colorTheme = m_colorThemes[p_colorTheme];

	m_selected = 0;

	m_numValue = p_numValue;
	m_minNum = p_numBounds.x;
	m_maxNum = p_numBounds.y;
}

void NumberField::input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos)
{
	p_mousePos = p_mousePos - m_pos;
	if((p_interactFlags & 1) == 0 && p_mousePos.x >= 0 && p_mousePos.x < m_size.x
		&& p_mousePos.y >= 0 && p_mousePos.y < m_size.y)
	{
		addTooltip();
		if(p_mouseStates[0] == 1)
			m_selected = 1;
	}
	else if(p_mouseStates[0] == 1)
		m_selected = 0;
	if(((p_interactFlags & 2) == 0) && m_selected != 0)
	{
		p_interactFlags += 2;
		std::vector<Globals::keyPress> _keyEvents = Globals::getInstance().m_keyEvents;
		for(Uint16 i = 0; i < _keyEvents.size(); i++)
		{
			if(_keyEvents[i].m_action != 0)
			{
				if(_keyEvents[i].m_keyCode == GLFW_KEY_ENTER)
				{
					p_interactFlags -= 2;
				}
				else if(_keyEvents[i].m_keyCode == GLFW_KEY_ESCAPE)
				{
					m_selected = 0;
				}
				else if(_keyEvents[i].m_keyCode == GLFW_KEY_BACKSPACE)
				{
					m_numValue = Sint32(floor(m_numValue / 10.f));
					callFunction();
				}
				else if(_keyEvents[i].m_keyCode >= GLFW_KEY_0 && _keyEvents[i].m_keyCode <= GLFW_KEY_9)
				{
					if((_keyEvents[i].m_mods & 1) == 0)
					{
						m_numValue = m_numValue * 10 + (_keyEvents[i].m_keyCode - GLFW_KEY_0);
						if(m_numValue > m_maxNum)
							m_numValue = m_maxNum;
						if(m_numValue < m_minNum)
							m_numValue = m_minNum;
						callFunction();
					}
				}
				else if(_keyEvents[i].m_keyCode == GLFW_KEY_UP)
				{
					m_numValue += (_keyEvents[i].m_mods & 1) ? 5 : 1;
					if(m_numValue > m_maxNum)
						m_numValue = m_maxNum;
					if(m_numValue < m_minNum)
						m_numValue = m_minNum;
					callFunction();
				}
				else if(_keyEvents[i].m_keyCode == GLFW_KEY_DOWN)
				{
					m_numValue -= (_keyEvents[i].m_mods & 1) ? 5 : 1;
					if(m_numValue > m_maxNum)
						m_numValue = m_maxNum;
					if(m_numValue < m_minNum)
						m_numValue = m_minNum;
					callFunction();
				}
				//else if(_keyEvents[i].m_keyCode == GLFW_KEY_MINUS)
				//	m_numValue = -m_numValue;
			}
		}
	}

	if(((p_interactFlags & 1) == 0) &&
	   p_mousePos.x >= 0 && p_mousePos.x < m_size.x
	   && p_mousePos.y >= 0 && p_mousePos.y < m_size.y)
		p_interactFlags += 1;
}

void NumberField::update(GLfloat p_deltaUpdate)
{

}

void NumberField::render()
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(GLfloat(m_pos.x), GLfloat(m_pos.y), 0);
		glBegin(GL_QUADS);
		{
			m_colorTheme.m_back.useColor();
			glVertex2f(-1, -1);
			glVertex2f(GLfloat(m_size.x + 1), -1);
			glVertex2f(GLfloat(m_size.x + 1), GLfloat(m_size.y + 1));
			glVertex2f(-1, GLfloat(m_size.y + 1));

			if(m_selected) m_colorTheme.m_active.useColor();
			else m_colorTheme.m_fore.useColor();
			glVertex2f(0, 0);
			glVertex2f(GLfloat(m_size.x), 0);
			glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y));
			glVertex2f(0, GLfloat(m_size.y));
		}
		glEnd();
		m_colorTheme.m_text.useColor();
		Font::getInstance().setAlignment(ALIGN_RIGHT);
		Font::getInstance().print(m_title, -2, Sint32(0.5f * Font::getInstance().getSpacingHeight()));
		Font::getInstance().setAlignment(ALIGN_LEFT);
		Font::getInstance().print(Util::numToString(m_numValue), 2, Sint32(0.5f * Font::getInstance().getSpacingHeight()));
		if(m_selected != 0 && (fmod(glfwGetTime(), 0.5) < 0.25))
			Font::getInstance().print("|", Font::getInstance().getMessageWidth(Util::numToString(m_numValue)).x, Sint32(0.5f * Font::getInstance().getSpacingHeight()));
	}
	glPopMatrix();
}