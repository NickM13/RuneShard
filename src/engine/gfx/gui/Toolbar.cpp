#include "engine\gfx\gui\Toolbar.h"


CToolbar::CToolbar(std::string p_compName, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme)
{
	m_compName = p_compName;
	m_pos = p_pos;
	m_size = p_size;
	m_colorTheme = m_colorThemes[p_colorTheme];
	m_panelMain = new Panel("", "", {0, 0}, p_size, 0, true, LTexture::loadImage("gui\\BarUnderline.png"), COMPONENT_TEXTURE_STYLE_SCALE);
	m_panelSub = new Panel("", "", {0, 0}, {0, 0}, 0, true, LTexture::loadImage("gui\\BarDrop.png"), COMPONENT_TEXTURE_STYLE_SCALE);

	m_slideCounter = 0;
}

//Directory splits with '/' or '\' 
void CToolbar::addButton(std::string p_dir, std::string p_buttonName, function p_func)
{
	Uint16 i = 0, j = 0;
	std::vector<std::string> _splitDir;
	if(p_dir != "")
	{
		while(i < p_dir.length())
		{
			if(p_dir[i] == '/' || p_dir[i] == '\\')
			{
				_splitDir.push_back(p_dir.substr(j, i));
				j = i + 1;
			}
			i++;
		}
		if(p_dir[p_dir.length() - 1] != '/' && p_dir[p_dir.length() - 1] != '\\')
			_splitDir.push_back(p_dir.substr(j, i));
	}

	SubList* _subList = &m_buttonsMain;
	for(i = 0; i < _splitDir.size(); i++)
		_subList = _subList->find(_splitDir[i]);
	_subList->addButton(p_buttonName, p_func);
}

void CToolbar::input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos)
{
	Uint16 i = 0, j = 0;
	if((p_interactFlags & 1) == 0 && p_mouseStates[0] == 1)
	{
		m_slideCounter = 0;
		SubList* _subList = &m_buttonsMain;
		std::vector<std::string> _splitDir;
		if(m_selected != "")
		{
			while(i < m_selected.length())
			{
				if(m_selected[i] == '/' || m_selected[i] == '\\')
				{
					_splitDir.push_back(m_selected.substr(j, i));
					j = i + 1;
				}
				i++;
			}
			if(m_selected[m_selected.length() - 1] != '/' && m_selected[m_selected.length() - 1] != '\\')
				_splitDir.push_back(m_selected.substr(j, i));
		}

		for(Uint16 k = 0; k < _splitDir.size(); k++)
			_subList = _subList->find(_splitDir[k]);

		if(_splitDir.size() == 1 && m_currDir == m_selected)
			m_currDir = "";
		else if(_subList->getFunction() != 0)
		{
			m_currDir = "";
			_subList->callFunction();
			p_interactFlags += 1;
		}
		else
			m_currDir = m_selected;
	}
	m_selected = "";
	if((p_interactFlags & 1) == 0)
	{
		i = j = 0;
		std::vector<std::string> _splitDir;
		if(m_currDir != "")
		{
			while(i < m_currDir.length())
			{
				if(m_currDir[i] == '/' || m_currDir[i] == '\\')
				{
					_splitDir.push_back(m_currDir.substr(j, i));
					j = i + 1;
				}
				i++;
			}
			if(m_currDir[m_currDir.length() - 1] != '/' && m_currDir[m_currDir.length() - 1] != '\\')
				_splitDir.push_back(m_currDir.substr(j, i));
		}

		Sint16 w = 0;
		Sint32 _buttonWidth;
		Sint32 _subWidth;
		for(i = 0; i < m_buttonsMain.m_buttons.size(); i++)
		{
			_buttonWidth = Font::getInstance().getMessageWidth(m_buttonsMain.m_buttons[i].m_name).x;
			if(m_currDir != "" && _splitDir[0] == m_buttonsMain.m_buttons[i].m_name)
			{
				std::vector<std::string> _path;
				SubList* _subList = &m_buttonsMain;
				for(j = 0; j < _splitDir.size(); j++)
				{
					_path.push_back(_splitDir[j]);
					_subList = _subList->find(_splitDir[j]);
					_subWidth = _buttonWidth;
					for(Uint16 k = 0; k < _subList->m_buttons.size(); k++)
						_subWidth = max(_subWidth, Font::getInstance().getMessageWidth(_subList->m_buttons[k].m_name).x);
					for(Uint16 g = 0; g < _subList->m_buttons.size(); g++)
					{
						if(p_mousePos.x - w >= 0 && p_mousePos.x - w < _subWidth + 32 &&
							p_mousePos.y - m_size.y >= g * Font::getInstance().getSpacingHeight() && p_mousePos.y - m_size.y < (g + 1) * Font::getInstance().getSpacingHeight())
						{
							m_selected = "";
							for(Uint16 h = 0; h < _path.size(); h++)
								m_selected += (_path[h] + "\\");
							m_selected += _subList->m_buttons[g].m_name;
							p_interactFlags += 1;
							break;
						}	
					}
				}
			}
			if(p_mousePos.x - w >= 0 && p_mousePos.x - w < Sint32(_buttonWidth + 32) &&
				p_mousePos.y >= 0 && p_mousePos.y < m_size.y)
			{
				m_selected = m_buttonsMain.m_buttons[i].m_name;
				p_interactFlags += 1;
				break;
			}
			w += Sint16(_buttonWidth + 32);
		}
	}
	if((p_interactFlags & 1) == 0 &&
		p_mousePos.x > m_pos.x && p_mousePos.x < m_pos.x + m_size.x &&
		p_mousePos.y > m_pos.y && p_mousePos.y < m_pos.y + m_size.y)
		p_interactFlags += 1;
}
void CToolbar::update(GLfloat p_deltaUpdate)
{
	m_slideCounter += p_deltaUpdate * 16;
	if(m_slideCounter > 1)
		m_slideCounter = 1;
}
void CToolbar::render()
{
	std::vector<std::string> _splitDir, _splitSelect;
	if(m_currDir != "")
	{
		Uint16 i = 0, j = 0;
		while(i < m_currDir.length())
		{
			if(m_currDir[i] == '/' || m_currDir[i] == '\\')
			{
				_splitDir.push_back(m_currDir.substr(j, i));
				j = i + 1;
			}
			i++;
		}
		if(m_currDir[m_currDir.length() - 1] != '/' && m_currDir[m_currDir.length() - 1] != '\\')
			_splitDir.push_back(m_currDir.substr(j, i));
	}
	else
		_splitDir.push_back("");

	if(m_selected != "")
	{
		Uint16 i = 0, j = 0;
		while(i < m_selected.length())
		{
			if(m_selected[i] == '/' || m_selected[i] == '\\')
			{
				_splitSelect.push_back(m_selected.substr(j, i));
				j = i + 1;
			}
			i++;
		}
		if(m_selected[m_selected.length() - 1] != '/' && m_selected[m_selected.length() - 1] != '\\')
			_splitSelect.push_back(m_selected.substr(j, i));
	}
	else
		_splitSelect.push_back("");

	m_panelMain->renderFill();
	m_colorTheme.m_text.useColor();
	glPushMatrix();
	{
		std::string _buttonName;
		Sint32 _buttonWidth;
		Font::getInstance().setAlignment(ALIGN_LEFT);
		for(Uint16 i = 0; i < m_buttonsMain.m_buttons.size(); i++)
		{
			_buttonName = m_buttonsMain.m_buttons[i].m_name;
			_buttonWidth = Font::getInstance().getMessageWidth(_buttonName).x;
			if(_splitDir[0] == m_buttonsMain.m_buttons[i].m_name || m_selected == m_buttonsMain.m_buttons[i].m_name)
			{
				glColor4f(0, 0, 0, 0.25f);
				glBegin(GL_QUADS);
				{
					glVertex2f(0, 0);
					glVertex2f(GLfloat(_buttonWidth + 32), 0);
					glVertex2f(GLfloat(_buttonWidth + 32), GLfloat(m_size.y));
					glVertex2f(0, GLfloat(m_size.y));
				}
				glEnd();
			}
			m_colorTheme.m_text.useColor();
			Font::getInstance().print(m_buttonsMain.m_buttons[i].m_name, 8, (m_size.y) / 2);

			if(_splitDir[0] == m_buttonsMain.m_buttons[i].m_name)
			{
				SubList* _subList = &m_buttonsMain;
				std::string _subName;
				Sint32 _subWidth;
				for(Uint16 j = 0; j < _splitDir.size(); j++)
				{
					_subList = _subList->find(_splitDir[j]);
					_subName = _subList->m_name;
					_subWidth = _buttonWidth;
					for(Uint16 k = 0; k < _subList->m_buttons.size(); k++)
						_subWidth = max(_subWidth, Font::getInstance().getMessageWidth(_subList->m_buttons[k].m_name).x);
					if(_subList->m_buttons.size() > 0)
					{
						glPushMatrix();
						{
							glTranslatef(GLfloat(j * 92), GLfloat(m_size.y), 0);
							m_panelSub->setSize(Vector2<Sint32>(Sint32(_subWidth + 32), Sint32((_subList->m_buttons.size()) * Font::getInstance().getSpacingHeight())));
							if(j == _splitDir.size() - 1)
								glScalef(1, m_slideCounter, 1);
							m_panelSub->renderFill();

							m_colorTheme.m_text.useColor();
							for(Uint16 k = 0; k < _subList->m_buttons.size(); k++)
							{
								if((Uint16(_splitDir.size()) > j + 1 && _splitDir[j + 1] == _subList->m_buttons[k].m_name) || (Uint16(_splitSelect.size()) > j + 1 && _splitSelect[j + 1] == _subList->m_buttons[k].m_name))
								{
									glBindTexture(GL_TEXTURE_2D, 0);
									glColor4f(0, 0, 0, 0.2f);
									glBegin(GL_QUADS);
									{
										glVertex2f(0, GLfloat(k * Font::getInstance().getSpacingHeight()));
										glVertex2f(GLfloat(_subWidth + 32), GLfloat(k * Font::getInstance().getSpacingHeight()));
										glVertex2f(GLfloat(_subWidth + 32), GLfloat((k + 1) * Font::getInstance().getSpacingHeight()));
										glVertex2f(0, GLfloat((k + 1) * Font::getInstance().getSpacingHeight()));
									}
									glEnd();
									m_colorTheme.m_text.useColor();
								}
								Font::getInstance().print(_subList->m_buttons[k].m_name, 8, Sint32((k + 0.5f) * Font::getInstance().getSpacingHeight() - 1));
							}
						}
						glPopMatrix();
					}
				}
			}
			glTranslatef(GLfloat(_buttonWidth + 32), 0, 0);
		}
	}
	glPopMatrix();
}