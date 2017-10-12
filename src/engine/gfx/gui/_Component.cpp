#include "engine\gfx\gui\_Component.h"
#include "engine\utils\variable\manager\TextureManager.h"

Component::Component()
{
	//						   BACK							FORE						ACTIVE						TEXT
	m_colorThemes.push_back({Color(0.5f, 0.5f, 0.5f, 1),			Color(0.8f, 0.8f, 0.8f, 1),				Color(0.95f, 0.95f, 0.95f, 1),				Color(0.05f, 0.05f, 0.05f, 1)});			// 0
	m_colorThemes.push_back({Color(0.25f, 0.25f, 0.25f, 255),		Color(0.6f, 0.6f, 0.6f, 255),			Color(0.5f, 0.5f, 0.5f, 1),					Color(0.05f, 0.05f, 0.05f, 1)});			// 1
	m_colorThemes.push_back({Color(0.75f, 0.75f, 0.75f, 0.5f),		Color(0.05f, 0.05f, 0.05f, 0.5f),		Color(0.075f, 0.075f, 0.075f, 0.5f),		Color(0.95f, 0.95f, 0.95f, 0.5f)});			// 2
}

Component::Component(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Sint8 p_colorTheme)
{
	m_compName = p_compName;
	m_title = p_title;
	m_pos = p_pos;
	m_size = p_size;

	m_colorTheme = m_colorThemes[p_colorTheme];
}
Component* Component::addComponent(Component* p_comp, Sint8 p_align)
{
	return 0;
}
Component* Component::findComponent(std::string p_compName)
{
	return 0;
}
std::string Component::getItem(Uint16 p_index)
{
	return "";
}
Texture Component::getItemTexture(Uint16 p_index)
{
	return Texture();
}
Uint16 Component::getItemTexId(Uint16 p_index)
{
	return 0;
}
Component* Component::addItem(std::string p_item)
{
	return this;
}
Component* Component::addItem(std::string p_item, Texture p_texture, Uint16 p_texId)
{
	return this;
}
void Component::setItem(Uint16 p_index, std::string p_item)
{

}
void Component::setItemTexId(Uint16 p_index, Uint16 p_texId)
{

}
void Component::setItemTexture(Uint16 p_index, Texture p_texture)
{
	
}
void Component::removeItem(Uint16 p_index)
{
	
}
Uint16 Component::getItemCount()
{
	return 0;
}
Component* Component::setFunction(function p_func)
{
	m_function = p_func;
	return this;
}
void Component::setSelectedItem(Uint16 p_selectedItem)
{

}
Uint8 Component::isUpdated()
{
	return 0;
}
Sint16 Component::getSelectedItem()
{
	return 0;
}
Sint16 Component::getPrevSelectedItem()
{
	return 0;
}
std::string Component::getName()
{
	return m_compName;
}
std::string Component::getTitle()
{
	return m_title;
}

void Component::setTooltip(std::string p_tooltip)
{
	m_tooltip = p_tooltip;
}
void Component::addTooltip()
{
	if(!Globals::getInstance().m_mouseMoved || m_tooltipTime > 1)
	{
		m_tooltipCounted = true;
		m_tooltipTime += Globals::getInstance().m_deltaTime;
		if(m_tooltipTime > 0.5f)
			Globals::getInstance().m_tooltip = m_tooltip;
	}
}
void Component::resetTooltip()
{
	if(!m_tooltipCounted)
		m_tooltipTime = 0;
	m_tooltipCounted = false;
}

void Component::setTitle(std::string p_title)
{
	m_title = p_title;
}
void Component::setPosition(Vector2<Sint32> p_pos)
{
	m_pos = p_pos;
}
void Component::setSize(Vector2<Sint32> p_size)
{
	m_size = p_size;
}

Vector2<Sint32> Component::getPosition()
{
	return m_pos;
}
Vector2<Sint32> Component::getSize()
{
	return m_size;
}
Vector2<Sint32> Component::getRealPosition()
{
	return m_pos;
}
Vector2<Sint32> Component::getRealSize()
{
	return m_size;
}

void Component::setState(Sint8 p_selected)
{
	m_selected = p_selected;
}

void Component::setVisible(bool p_visible)
{
	m_visible = p_visible;
}
bool Component::isVisible()
{
	return m_visible;
}

void Component::input()
{
	
}
void Component::input(Sint8& p_interactFlags, Sint8* p_keyStates, Sint8* p_mouseStates, Vector2<Sint32> p_mousePos)
{

}
void Component::update(GLfloat p_deltaUpdate)
{

}
void Component::renderBack()
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(GLfloat(m_pos.x), GLfloat(m_pos.y), 0);
		m_colorTheme.m_back.useColor();
		glBegin(GL_LINES);
		{
			glVertex2f(-GLfloat(m_borderThickness), -GLfloat(m_borderThickness) + 1);
			glVertex2f(GLfloat(m_size.x + m_borderThickness), -GLfloat(m_borderThickness) + 1);

			glVertex2f(GLfloat(m_size.x + m_borderThickness), -GLfloat(m_borderThickness));
			glVertex2f(GLfloat(m_size.x + m_borderThickness), GLfloat(m_size.y + m_borderThickness));

			glVertex2f(GLfloat(m_size.x + m_borderThickness), GLfloat(m_size.y + m_borderThickness));
			glVertex2f(-GLfloat(m_borderThickness), GLfloat(m_size.y + m_borderThickness));

			glVertex2f(-GLfloat(m_borderThickness) + 1, GLfloat(m_size.y + m_borderThickness));
			glVertex2f(-GLfloat(m_borderThickness) + 1, -GLfloat(m_borderThickness));
		}
		glEnd();
	}
	glPopMatrix();
}
void Component::renderFill(bool p_setColor)
{
	glPushMatrix();
	{
		glTranslatef(GLfloat(m_pos.x), GLfloat(m_pos.y), 0);
		if(p_setColor)
		{
			if(isSelected())
				m_colorTheme.m_active.useColor();
			else
				m_colorTheme.m_fore.useColor();
		}
		if(m_texture != -1)
			glBindTexture(GL_TEXTURE_2D, MTexture::getInstance().getUnit(m_texture).getId());

		glBegin(GL_QUADS);
		{
			if(m_texture != -1)
			{
				Vector2<Sint32> _texSize;
				if(m_textureStyle == COMPONENT_TEXTURE_STYLE_NONE)
				{
					glTexCoord2f(0, 0);
					glVertex2f(0, 0);
					glTexCoord2f(1, 0);
					glVertex2f(GLfloat(m_size.x), 0);
					glTexCoord2f(1, 1);
					glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y));
					glTexCoord2f(0, 1);
					glVertex2f(0, GLfloat(m_size.y));
				}
				else if(m_textureStyle == COMPONENT_TEXTURE_STYLE_WRAP)
				{
					_texSize = MTexture::getInstance().getUnit(m_texture).getSize();
					glTexCoord2f(0, 0);
					glVertex2f(0, 0);
					glTexCoord2f(GLfloat(m_size.x) / _texSize.x, 0);
					glVertex2f(GLfloat(m_size.x), 0);
					glTexCoord2f(GLfloat(m_size.x) / _texSize.x, GLfloat(m_size.y) / _texSize.y);
					glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y));
					glTexCoord2f(0, GLfloat(m_size.y) / _texSize.y);
					glVertex2f(0, GLfloat(m_size.y));
				}
				else if(m_textureStyle == COMPONENT_TEXTURE_STYLE_SCALE)
				{
					_texSize = MTexture::getInstance().getUnit(m_texture).getSize();
					// Top Left corner
					glTexCoord2f(0, 1);
					glVertex2f(0, 0);
					glTexCoord2f(0.25f, 1);
					glVertex2f(_texSize.x / 4.f, 0);
					glTexCoord2f(0.25f, 0.75f);
					glVertex2f(_texSize.x / 4.f, _texSize.y / 4.f);
					glTexCoord2f(0, 0.75f);
					glVertex2f(0, _texSize.y / 4.f);


					// Top Right corner
					glTexCoord2f(0.75f, 1);
					glVertex2f(GLfloat(m_size.x) - _texSize.x / 4.f, 0);
					glTexCoord2f(1, 1);
					glVertex2f(GLfloat(m_size.x), 0);
					glTexCoord2f(1, 0.75f);
					glVertex2f(GLfloat(m_size.x), _texSize.y / 4.f);
					glTexCoord2f(0.75f, 0.75f);
					glVertex2f(GLfloat(m_size.x) - _texSize.x / 4.f, _texSize.y / 4.f);


					// Bottom Left corner
					glTexCoord2f(0, 0.25f);
					glVertex2f(0, GLfloat(m_size.y) - _texSize.y / 4.f);
					glTexCoord2f(0.25f, 0.25f);
					glVertex2f(_texSize.x / 4.f, GLfloat(m_size.y) - _texSize.y / 4.f);
					glTexCoord2f(0.25f, 0);
					glVertex2f(_texSize.x / 4.f, GLfloat(m_size.y));
					glTexCoord2f(0, 0);
					glVertex2f(0, GLfloat(m_size.y));


					// Bottom Right corner
					glTexCoord2f(0.75f, 0.25f);
					glVertex2f(GLfloat(m_size.x) - _texSize.x / 4.f, GLfloat(m_size.y) - _texSize.y / 4.f);
					glTexCoord2f(1, 0.25f);
					glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y) - _texSize.y / 4.f);
					glTexCoord2f(1, 0);
					glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y));
					glTexCoord2f(0.75f, 0);
					glVertex2f(GLfloat(m_size.x) - _texSize.x / 4.f, GLfloat(m_size.y));



					GLfloat _width = floor((GLfloat(m_size.x) - _texSize.x / 2.f) / (_texSize.x / 2.f));
					GLfloat _widthF = ((GLfloat(m_size.x) - _texSize.x / 2.f) / (_texSize.x / 2.f));

					// Top and Bottom side
					for(Uint16 i = 0; i < _width; i++)
					{
						glTexCoord2f(0.25f, 1);
						glVertex2f(_texSize.x / 4.f + (i * _texSize.x / 2.f), 0);
						glTexCoord2f(0.75f, 1);
						glVertex2f(_texSize.x / 4.f + ((i + 1) * _texSize.x / 2.f), 0);
						glTexCoord2f(0.75f, 0.75f);
						glVertex2f(_texSize.x / 4.f + ((i + 1) * _texSize.x / 2.f), _texSize.y / 4.f);
						glTexCoord2f(0.25f, 0.75f);
						glVertex2f(_texSize.x / 4.f + (i * _texSize.x / 2.f), _texSize.y / 4.f);


						glTexCoord2f(0.25f, 0.25f);
						glVertex2f(_texSize.x / 4.f + (i * _texSize.x / 2.f), GLfloat(m_size.y) - _texSize.y / 4.f);
						glTexCoord2f(0.75f, 0.25f);
						glVertex2f(_texSize.x / 4.f + ((i + 1) * _texSize.x / 2.f), GLfloat(m_size.y) - _texSize.y / 4.f);
						glTexCoord2f(0.75f, 0);
						glVertex2f(_texSize.x / 4.f + ((i + 1) * _texSize.x / 2.f), GLfloat(m_size.y));
						glTexCoord2f(0.25f, 0);
						glVertex2f(_texSize.x / 4.f + (i * _texSize.x / 2.f), GLfloat(m_size.y));
					}

					glTexCoord2f(0.25f, 1);
					glVertex2f(_texSize.x / 4.f + (_width * _texSize.x / 2.f), 0);
					glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 1);
					glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.x / 2.f), 0);
					glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 0.75f);
					glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.x / 2.f), _texSize.y / 4.f);
					glTexCoord2f(0.25f, 0.75f);
					glVertex2f(_texSize.x / 4.f + (_width * _texSize.x / 2.f), _texSize.y / 4.f);


					glTexCoord2f(0.25f, 0.25f);
					glVertex2f(_texSize.x / 4.f + (_width * _texSize.x / 2.f), GLfloat(m_size.y) - _texSize.y / 4.f);
					glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 0.25f);
					glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.x / 2.f), GLfloat(m_size.y) - _texSize.y / 4.f);
					glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 0);
					glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.x / 2.f), GLfloat(m_size.y));
					glTexCoord2f(0.25f, 0);
					glVertex2f(_texSize.x / 4.f + (_width * _texSize.x / 2.f), GLfloat(m_size.y));





					GLfloat _height = floor((GLfloat(m_size.y) - _texSize.y / 2.f) / (_texSize.y / 2.f));
					GLfloat _heightF = ((GLfloat(m_size.y) - _texSize.y / 2.f) / (_texSize.y / 2.f));

					// Left and Right side
					for(Uint16 i = 0; i < _height; i++)
					{
						glTexCoord2f(0, 0.75f);
						glVertex2f(0, _texSize.y / 4.f + (i * _texSize.y / 2.f));
						glTexCoord2f(0, 0.25f);
						glVertex2f(0, (_texSize.y / 4.f + ((i + 1) * _texSize.y / 2.f)));
						glTexCoord2f(0.25f, 0.25f);
						glVertex2f(_texSize.x / 4.f, (_texSize.y / 4.f + ((i + 1) * _texSize.y / 2.f)));
						glTexCoord2f(0.25f, 0.75f);
						glVertex2f(_texSize.x / 4.f, _texSize.y / 4.f + (i * _texSize.y / 2.f));


						glTexCoord2f(0.75f, 0.75f);
						glVertex2f(GLfloat(m_size.x) - _texSize.y / 4.f, _texSize.y / 4.f + (i * _texSize.y / 2.f));
						glTexCoord2f(0.75f, 0.25f);
						glVertex2f(GLfloat(m_size.x) - _texSize.y / 4.f, _texSize.y / 4.f + ((i + 1) * _texSize.y / 2.f));
						glTexCoord2f(1, 0.25f);
						glVertex2f(GLfloat(m_size.x), _texSize.y / 4.f + ((i + 1) * _texSize.y / 2.f));
						glTexCoord2f(1, 0.75f);
						glVertex2f(GLfloat(m_size.x), _texSize.y / 4.f + (i * _texSize.y / 2.f));
					}

					glTexCoord2f(0, 0.75f);
					glVertex2f(0, _texSize.y / 4.f + (_height * _texSize.y / 2.f));
					glTexCoord2f(0, 0.75f - 0.5f * (_heightF - _height));
					glVertex2f(0, _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
					glTexCoord2f(0.25f, 0.75f - 0.5f * (_heightF - _height));
					glVertex2f(_texSize.x / 4.f, _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
					glTexCoord2f(0.25f, 0.75f);
					glVertex2f(_texSize.x / 4.f, _texSize.y / 4.f + (_height * _texSize.y / 2.f));


					glTexCoord2f(0.75f, 0.75f);
					glVertex2f(GLfloat(m_size.x) - _texSize.x / 4.f, _texSize.y / 4.f + (_height * _texSize.y / 2.f));
					glTexCoord2f(0.75f, 0.75f - 0.5f * (_heightF - _height));
					glVertex2f(GLfloat(m_size.x) - _texSize.x / 4.f, _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
					glTexCoord2f(1, 0.75f - 0.5f * (_heightF - _height));
					glVertex2f(GLfloat(m_size.x), _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
					glTexCoord2f(1, 0.75f);
					glVertex2f(GLfloat(m_size.x), _texSize.y / 4.f + (_height * _texSize.y / 2.f));


					// Center
					for(Uint16 x = 0; x < _width; x++)
					{
						for(Uint16 y = 0; y < _height; y++)
						{
							glTexCoord2f(0.25f, 0.75f);
							glVertex2f(_texSize.x / 4.f + (x * _texSize.x / 2.f), _texSize.y / 4.f + (y * _texSize.y / 2.f));
							glTexCoord2f(0.75f, 0.75f);
							glVertex2f(_texSize.x / 4.f + ((x + 1) * _texSize.x / 2.f), _texSize.y / 4.f + (y * _texSize.y / 2.f));
							glTexCoord2f(0.75f, 0.25f);
							glVertex2f(_texSize.x / 4.f + ((x + 1) * _texSize.x / 2.f), _texSize.y / 4.f + ((y + 1) * _texSize.y / 2.f));
							glTexCoord2f(0.25f, 0.25f);
							glVertex2f(_texSize.x / 4.f + (x * _texSize.x / 2.f), _texSize.y / 4.f + ((y + 1) * _texSize.y / 2.f));

						}
					}

					for(Uint16 x = 0; x < _width; x++)
					{
						glTexCoord2f(0.25f, 0.75f);
						glVertex2f(_texSize.x / 4.f + (x * _texSize.x / 2.f), _texSize.y / 4.f + (_height * _texSize.y / 2.f));
						glTexCoord2f(0.75f, 0.75f);
						glVertex2f(_texSize.x / 4.f + ((x + 1) * _texSize.x / 2.f), _texSize.y / 4.f + (_height * _texSize.y / 2.f));
						glTexCoord2f(0.75f, 0.75f - 0.5f * (_heightF - _height));
						glVertex2f(_texSize.x / 4.f + ((x + 1) * _texSize.x / 2.f), _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
						glTexCoord2f(0.25f, 0.75f - 0.5f * (_heightF - _height));
						glVertex2f(_texSize.x / 4.f + (x * _texSize.x / 2.f), _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
					}

					for(Uint16 y = 0; y < _height; y++)
					{
						glTexCoord2f(0.25f, 0.75f);
						glVertex2f(_texSize.x / 4.f + (_width * _texSize.y / 2.f), _texSize.y / 4.f + (y * _texSize.y / 2.f));
						glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 0.75f);
						glVertex2f(_texSize.x / 4.f + (_width * _texSize.y / 2.f), _texSize.y / 4.f + ((y + 1) * _texSize.y / 2.f));
						glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 0.25f);
						glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.y / 2.f), _texSize.y / 4.f + ((y + 1) * _texSize.y / 2.f));
						glTexCoord2f(0.25f, 0.25f);
						glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.y / 2.f), _texSize.y / 4.f + (y * _texSize.y / 2.f));
					}

					glTexCoord2f(0.25f, 0.75f);
					glVertex2f(_texSize.x / 4.f + (_width * _texSize.x / 2.f), _texSize.y / 4.f + (_height * _texSize.y / 2.f));
					glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 0.75f);
					glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.x / 2.f), _texSize.y / 4.f + (_height * _texSize.y / 2.f));
					glTexCoord2f(0.25f + 0.5f * (_widthF - _width), 0.75f - 0.5f * (_heightF - _height));
					glVertex2f(_texSize.x / 4.f + ((_width + (_widthF - _width)) * _texSize.x / 2.f), _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
					glTexCoord2f(0.25f, 0.75f - 0.5f * (_heightF - _height));
					glVertex2f(_texSize.x / 4.f + (_width * _texSize.x / 2.f), _texSize.y / 4.f + ((_height + (_heightF - _height)) * _texSize.y / 2.f));
				}
			}
			else
			{
				glVertex2f(0, 0);
				glVertex2f(GLfloat(GLfloat(m_size.x)), 0);
				glVertex2f(GLfloat(GLfloat(m_size.x)), GLfloat(GLfloat(m_size.y)));
				glVertex2f(0, GLfloat(GLfloat(m_size.y)));
			}
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glPopMatrix();
}
void Component::render()
{
	renderBack();
	renderFill();
}
Sint8 Component::isSelected()
{
	return m_selected;
}

void Component::setValue(Sint32 p_value)
{
	m_numValue = p_value;
}
Sint32& Component::getValue()
{
	return m_numValue;
}
Sint8 Component::getPriorityLayer()
{
	return m_priority + m_moveToFront;
}
void Component::setPriorityLayer(Sint8 p_priority)
{
	m_priority = p_priority;
}
