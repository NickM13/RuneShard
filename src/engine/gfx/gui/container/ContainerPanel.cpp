#include "engine\gfx\gui\container\ContainerPanel.h"

ContainerPanel::ContainerPanel(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Theme p_colorTheme, Sint8 p_borderFlags, bool p_visible)
	: Container(p_compName, p_pos, p_size, p_visible)
{
	m_title = p_title;
	m_colorTheme = m_colorThemes[p_colorTheme];
	m_border = p_borderFlags;
	m_visible = p_visible;

	m_scroll = {0, 0};
	m_minScroll = m_maxScroll = {0, 0};

	m_draggable = false; //currently disabled
	m_scrollX = m_scrollY = false;
	m_panel = new Panel(p_compName.append("_PANEL"), p_title, p_pos, p_size, p_colorTheme, p_borderFlags);
}

Component* ContainerPanel::addComponent(Component* p_component, Anchor p_posAnchor, Anchor p_sizeAnchor)
{
	Component* _comp = Container::addComponent(p_component, p_posAnchor, p_sizeAnchor);

	m_minScroll.x = min(m_minScroll.x, m_contentArea.x1);
	m_minScroll.y = min(m_minScroll.y, m_contentArea.y1);

	m_maxScroll.x = max(m_maxScroll.x, m_contentArea.x2 - m_size.x);
	m_maxScroll.y = max(m_maxScroll.y, m_contentArea.y2 - m_size.y);

	m_scroll = m_minScroll;

	if((m_minScroll.y != m_maxScroll.y) != m_scrollY)
		setScrollY(!m_scrollY);

	return _comp;
}

ContainerPanel::~ContainerPanel() {
	delete m_panel;
	for(std::pair<std::string, Comp> c : m_componentMap) {
		delete c.second.m_component;
	}
	m_componentMap.clear();
}

void ContainerPanel::calcSize(Vector2<Sint32> p_offset)
{
	if(p_offset.getLength() == 0)
		m_minScroll = m_maxScroll = Vector2<Sint32>();
	m_contentArea = Vector4<Sint32>();
	for (std::pair<std::string, Comp> comp : m_componentMap) {
		Comp _comp = comp.second;
		Component* _component = _comp.m_component;
		switch (_comp.m_posAnchor)
		{
		case CENTER:
		case TOP:
		case BOTTOM:
			_component->setPosition(_component->getPosition() + Vector2<Sint32>(p_offset.x / 2, 0));
			break;
		case RIGHT:
		case TOP_RIGHT:
		case BOTTOM_RIGHT:
			_component->setPosition(_component->getPosition() + Vector2<Sint32>(p_offset.x, 0));
			break;
		default:
			break;
		}
		if(_component->isVisible())
			m_contentArea = Vector4<Sint32>(min(_component->getRealPosition().x, m_contentArea.x1), min(_component->getRealPosition().y, m_contentArea.y1), max(_component->getRealPosition().x + _component->getRealSize().x, m_contentArea.x2), max(_component->getRealPosition().y + _component->getRealSize().y + 8, m_contentArea.y2));
	}

	m_minScroll.x = min(m_minScroll.x, m_contentArea.x1);
	m_minScroll.y = min(m_minScroll.y, m_contentArea.y1);

	m_maxScroll.x = max(m_maxScroll.x, m_contentArea.x2 - m_size.x);
	m_maxScroll.y = max(m_maxScroll.y, m_contentArea.y2 - m_size.y + 4);

	if((m_minScroll.y != m_maxScroll.y) != m_scrollY)
		setScrollY(!m_scrollY);
}
void ContainerPanel::resize() {
	Container::resize();
	m_panel->setPosition(m_pos);
	m_panel->setSize(m_size);
}
//TODO: Set whether scroll bar across bottom exists
void ContainerPanel::setScrollX(bool p_state)
{

}
//Set whether scroll bar across right exists
void ContainerPanel::setScrollY(bool p_state)
{
	if(p_state != m_scrollY)
	{
		m_scrollY = p_state;
		if(p_state)
			m_size.x -= 10;
		else
			m_size.x += 10;
		calcSize({p_state ? -10 : 10, 0});
	}
}

void ContainerPanel::input(Sint8& p_interactFlags, Vector2<Sint32> p_mousePos)
{
	p_mousePos = p_mousePos - m_pos;
	if(p_mousePos.x >= 0 && p_mousePos.x <= m_size.x + (m_scrollY ? 10 : 0) && 
		p_mousePos.y >= 0 && p_mousePos.y <= m_size.y)
		Container::input(p_interactFlags, p_mousePos);
	else
	{
		bool _1 = (p_interactFlags & EVENT_MOUSEOVER), _4 = (p_interactFlags & EVENT_MOUSESCROLL);
		if(_1)
			p_interactFlags -= EVENT_MOUSEOVER;
		if(_4)
			p_interactFlags -= EVENT_MOUSESCROLL;
		Container::input(p_interactFlags, p_mousePos);
		if(_1)
			p_interactFlags += EVENT_MOUSEOVER;
		if(_4)
			p_interactFlags += EVENT_MOUSESCROLL;
	}

	m_moveToFront = (m_lHeld != 0);

	// Scroll window
	if((p_interactFlags & EVENT_MOUSESCROLL) &&
		p_mousePos.x >= 0 && p_mousePos.x <= m_size.x + 10 &&
		p_mousePos.y >= 0 && p_mousePos.y <= m_size.y) {
		m_scroll.y -= GMouse::getScroll() * 8;
		p_interactFlags -= EVENT_MOUSESCROLL;
	}
	if(m_rHeld != 0) {
		if(m_minScroll.x != 0 || m_maxScroll.x != 0)
			m_scroll.x += p_mousePos.x - m_mousePos.x;
		if(m_minScroll.y != 0 || m_maxScroll.y != 0)
			m_scroll.y += p_mousePos.y - m_mousePos.y;
	}

	if(m_scroll.x < m_minScroll.x)
		m_scroll.x = m_minScroll.x;
	if(m_scroll.y < m_minScroll.y)
		m_scroll.y = m_minScroll.y;

	if(m_scroll.x > m_maxScroll.x)
		m_scroll.x = m_maxScroll.x;
	if(m_scroll.y > m_maxScroll.y)
		m_scroll.y = m_maxScroll.y;

	if((p_interactFlags & EVENT_MOUSEOVER) &&
		p_mousePos.x >= 0 && p_mousePos.x <= m_size.x &&
		p_mousePos.y >= 0 && p_mousePos.y <= m_size.y)
		p_interactFlags -= EVENT_MOUSEOVER;

	// Drag window -- disabled
	if(((p_interactFlags & EVENT_MOUSEOVER) || m_lHeld) && m_draggable) {
		if(m_lHeld != 0)
			m_pos = m_pos + (p_mousePos - m_mousePos);
		if(p_mousePos.x >= 0 && p_mousePos.x <= m_size.x && 
			p_mousePos.y >= 0 && p_mousePos.y <= m_size.y) {
			if(GMouse::mousePressed(GLFW_MOUSE_BUTTON_LEFT))
				m_lHeld = 2;
			else if(!GMouse::mouseDown(GLFW_MOUSE_BUTTON_LEFT)) {
				m_lHeld = 0;
				if(m_pos.x < 0)
					m_pos.x = 0;
				else if(m_pos.x > Sint32(GScreen::m_screenSize.x - m_size.x))
					m_pos.x = Sint32(GScreen::m_screenSize.x - m_size.x);
				if(m_pos.y > 0)
					m_pos.y = 0;
				else if(m_pos.y < -Sint32(GScreen::m_screenSize.y - m_size.y) + 24)
					m_pos.y = -Sint32(GScreen::m_screenSize.y - m_size.y) + 24;
			}
		}
		else if(!GMouse::mouseDown(GLFW_MOUSE_BUTTON_LEFT)) {
			m_lHeld = 0;
			if(m_pos.x < 0)
				m_pos.x = 0;
			else if(m_pos.x > Sint32(GScreen::m_screenSize.x - m_size.x))
				m_pos.x = Sint32(GScreen::m_screenSize.x - m_size.x);
			if(m_pos.y > 0)
				m_pos.y = 0;
			else if(m_pos.y < -Sint32(GScreen::m_screenSize.x - m_size.x) + 24)
				m_pos.y = -Sint32(GScreen::m_screenSize.x - m_size.x) + 24;
		}
	}
	if(m_scrollY && 
		p_mousePos.x >= m_size.x && p_mousePos.x <= m_size.x + 10 && 
		p_mousePos.y >= 0 && p_mousePos.y <= m_size.y) {
		if(m_scrollY) {
			if(GMouse::mousePressed(GLFW_MOUSE_BUTTON_LEFT))
				m_rHeld = 2;
			else if(!GMouse::mouseDown(GLFW_MOUSE_BUTTON_LEFT))
				m_rHeld = 0;
		}
		if((p_interactFlags & EVENT_MOUSEOVER))
			p_interactFlags -= EVENT_MOUSEOVER;
	}
	else {
		if(!GMouse::mouseDown(GLFW_MOUSE_BUTTON_LEFT))
			m_rHeld = 0;
		else
			if(m_rHeld && (p_interactFlags & EVENT_MOUSEOVER))
				p_interactFlags -= EVENT_MOUSEOVER;
	}
	m_mousePos = p_mousePos;
}
void ContainerPanel::update(GLfloat p_updateTime) {
	Container::update(p_updateTime);
}
void ContainerPanel::render() {
	if(m_visible) {
		m_panel->render();
		MScissor::push(Rect(GLfloat(m_pos.x + 1), GLfloat(m_pos.y), GLfloat(m_size.x - 2), GLfloat(m_size.y - 1)));
		glPushMatrix();
		{
			glTranslatef(-GLfloat(m_scroll.x), -GLfloat(m_scroll.y), 0);
			Container::render();
		}
		glPopMatrix();
		MScissor::pop();
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			Vector2<Sint32> _scrollDist = m_maxScroll - m_minScroll;
			glTranslatef(GLfloat(m_pos.x), GLfloat(m_pos.y), 0);
			if(m_scrollX)
			{
				m_colorTheme.m_border.useColor();
				glBegin(GL_QUADS);
				{
					glVertex2f(0, GLfloat(m_size.y));
					glVertex2f(0, GLfloat(m_size.y + 10));
					glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y + 10));
					glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y));
				}
				glEnd();
				m_colorTheme.m_primary.useColor();
			}
			if(m_scrollY) {
				m_colorTheme.m_border.useColor();
				glBegin(GL_QUADS);
				{
					glVertex2f(GLfloat(m_size.x), 0);
					glVertex2f(GLfloat(m_size.x + 10), 0);
					glVertex2f(GLfloat(m_size.x + 10), GLfloat(m_size.y));
					glVertex2f(GLfloat(m_size.x), GLfloat(m_size.y));
				}
				glEnd();
				m_colorTheme.m_primary.useColor();
				glBegin(GL_QUADS);
				{
					//((m_size.y / GLfloat(_scrollDist.y + m_size.y)) * m_size.y) - 1
					glVertex2f(GLfloat(m_size.x + 1), (GLfloat(m_scroll.y - m_minScroll.y) / _scrollDist.y) * (m_size.y * _scrollDist.y) / (m_size.y + _scrollDist.y) + 1);
					glVertex2f(GLfloat(m_size.x + 9), (GLfloat(m_scroll.y - m_minScroll.y) / _scrollDist.y) * (m_size.y * _scrollDist.y) / (m_size.y + _scrollDist.y) + 1);
					glVertex2f(GLfloat(m_size.x + 9), (GLfloat(m_scroll.y - m_minScroll.y) / _scrollDist.y) * (m_size.y * _scrollDist.y) / (m_size.y + _scrollDist.y) + ((m_size.y * m_size.y) / (m_size.y + _scrollDist.y)) - 1);
					glVertex2f(GLfloat(m_size.x + 1), (GLfloat(m_scroll.y - m_minScroll.y) / _scrollDist.y) * (m_size.y * _scrollDist.y) / (m_size.y + _scrollDist.y) + ((m_size.y * m_size.y) / (m_size.y + _scrollDist.y)) - 1);
				}
				glEnd();
			}
		}
		glPopMatrix();
	}
}