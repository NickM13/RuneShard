#include "engine\gfx\gui\button\ButtonRadio.h"

CButtonRadio::CButtonRadio(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_buttonSize, Vector2<Sint32> p_buttonStep, Uint16* p_selectedButton)
	: Component(p_compName, p_title, p_pos, {}, ACTION)
{
	m_buttonSize = p_buttonSize;
	m_buttonStep = p_buttonStep;
	m_selectedButton = p_selectedButton;
}
CButtonRadio::~CButtonRadio() {
	for(CButtonToggle* button : m_buttonList)
		delete button;
	m_buttonList.clear();
}

Component* CButtonRadio::addButton(Texture p_tex)
{
	CButtonToggle *_button = new CButtonToggle("", p_tex, m_buttonStep * m_buttonList.size(), m_buttonSize);
	_button->setBorder(0);
	m_buttonList.push_back(_button);
	if(m_buttonList.size() > *m_selectedButton)
		m_buttonList[*m_selectedButton]->setState(1);
	callPressFunction();
	return _button;
}

void CButtonRadio::input(Sint8& p_interactFlags, Vector2<Sint32> p_mousePos)
{
	p_mousePos = p_mousePos - m_pos;
	if(p_interactFlags & EVENT_MOUSEOVER)
	{
		for(Uint16 i = 0; i < m_buttonList.size(); i++)
		{
			if(m_buttonList[i] != 0) {
				m_buttonList[i]->input(p_interactFlags, p_mousePos);
				if(*m_buttonList[i]->getValue() != 0)
				{
					*m_selectedButton = i;
					callPressFunction();
					return;
				}
			}
		}
	}
}
void CButtonRadio::update(GLfloat p_deltaUpdate)
{
	m_buttonList[m_prevSelectedButton]->setState(0);
	m_buttonList[*m_selectedButton]->setState(1);
	if(m_prevSelectedButton != *m_selectedButton)
	{
		callPressFunction();
		m_prevSelectedButton = *m_selectedButton;
	}
}
void CButtonRadio::render()
{
	glPushMatrix();
	{
		glTranslatef(GLfloat(m_pos.x), GLfloat(m_pos.y), 0);
		for(Uint16 i = 0; i < m_buttonList.size(); i++)
			m_buttonList[i]->render();
	}
	glPopMatrix();
}

void CButtonRadio::setSelectedButton(Uint16 p_selectedButton)
{
	m_prevSelectedButton = *m_selectedButton;
	*m_selectedButton = p_selectedButton;
	callPressFunction();
}
