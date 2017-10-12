#include "engine\gfx\gui\Slider.h"


CSlider::CSlider(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Sint32 p_length, Sint32 p_maxValue, Sint32 p_numValue, Sint8 p_colorTheme)
{
	m_compName = p_compName;
	m_title = p_title;
	m_pos = p_pos;
	m_length = p_length;
	m_maxValue = p_maxValue;
	m_numValue = p_numValue;
	m_size = {p_length, m_height};
	m_colorTheme = m_colorThemes[p_colorTheme];
};

void CSlider::setMaxValue(Sint16 p_value)
{
	m_maxValue = p_value;
	if(m_numValue > m_maxValue)
		m_numValue = m_maxValue;
}

void CSlider::setValue(Sint32 p_value)
{
	if(m_numValue != p_value)
	{
		if(p_value < 0)
			m_numValue = 0;
		else if(p_value > m_maxValue)
			m_numValue = m_maxValue;
		else
			m_numValue = p_value;
		callFunction();
	}
}

void CSlider::addValue(Sint16 p_value)
{
	m_numValue += p_value;
}

void CSlider::input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos)
{
	if(((p_interactFlags & 1) == 0) || m_held)
	{
		switch(p_mouseStates[0])
		{
		case 0:
			break;
		case 1:
			if(p_mousePos.x >= m_pos.x - 6 && p_mousePos.x < m_pos.x + m_length + 6 &&
			   p_mousePos.y >= m_pos.y - m_height / 2 && p_mousePos.y < m_pos.y + m_height / 2)
			{
				m_held = true;
			}
			break;
		case 2:
			if(m_held)
			{
				m_slideValue = p_mousePos.x - m_pos.x;
				setValue(Sint32(round((m_slideValue / GLfloat(m_length)) * (m_maxValue))));
			}
			break;
		case 3:
			m_held = false;
			break;
		default:

			break;
		}
		if(((p_interactFlags & 1) == 0) && (m_held || (p_mousePos.x >= m_pos.x - 6 && p_mousePos.x < m_pos.x + m_length + 6 &&
													   p_mousePos.y >= m_pos.y - m_height / 2 && p_mousePos.y < m_pos.y + m_height / 2)))
		{
			addTooltip();
			p_interactFlags += 1;
		}
	}
}
void CSlider::update(Vector2<Sint32> p_pos)
{

}
void CSlider::render()
{
	m_slideValue = Sint32((m_numValue / GLfloat(m_maxValue)) * m_length);
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(GLfloat(m_pos.x), GLfloat(m_pos.y), 0);
		glBegin(GL_QUADS);
		{
			//Outline
			m_colorTheme.m_back.useColor();
			glVertex2f(-8, -GLfloat(m_height / 2) - 1);
			glVertex2f(GLfloat(m_length + 8), -GLfloat(m_height / 2) - 1);
			glVertex2f(GLfloat(m_length + 8), GLfloat(m_height / 2) + 1);
			glVertex2f(-8, GLfloat(m_height / 2) + 1);

			//Background
			m_colorTheme.m_fore.useColor();
			glVertex2f(-7, -GLfloat(m_height / 2));
			glVertex2f(GLfloat(m_slideValue), -GLfloat(m_height / 2));
			glVertex2f(GLfloat(m_slideValue), GLfloat(m_height / 2));
			glVertex2f(-7, GLfloat(m_height / 2));

			m_colorTheme.m_fore.useColor(1, 1, 1, 0.5f);
			glVertex2f(-7, -GLfloat(m_height / 2));
			glVertex2f(GLfloat(m_length + 7), -GLfloat(m_height / 2));
			glVertex2f(GLfloat(m_length + 7), GLfloat(m_height / 2));
			glVertex2f(-7, GLfloat(m_height / 2));

			//Slider
			m_colorTheme.m_back.useColor();
			glVertex2f(GLfloat(m_slideValue - 6), -GLfloat(m_height / 2 - 1));
			glVertex2f(GLfloat(m_slideValue + 6), -GLfloat(m_height / 2 - 1));
			glVertex2f(GLfloat(m_slideValue + 6), GLfloat(m_height / 2 - 1));
			glVertex2f(GLfloat(m_slideValue - 6), GLfloat(m_height / 2 - 1));
		}
		glEnd();
	}
	glPopMatrix();

	m_colorTheme.m_text.useColor();
	Font::getInstance().setAlignment(ALIGN_CENTER);
	Font::getInstance().print(m_title, Sint32(m_pos.x + m_length / 2), Sint32(m_pos.y - m_height));
	glColor3f(1, 1, 1);
	Font::getInstance().setAlignment(ALIGN_CENTER);
	Font::getInstance().print(Util::numToString(m_numValue, 16), Sint32(m_pos.x + m_length / 2), Sint32(m_pos.y));
}

Sint32 CSlider::getMaxValue()
{
	return m_maxValue;
}
Sint32 CSlider::getLength()
{
	return m_length;
}