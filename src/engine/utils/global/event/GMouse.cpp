#include "engine\utils\global\event\GMouse.h"
#include "engine\utils\OpenGL.h"

Vector2<Sint32> GMouse::m_mousePos = {};
Vector2<Sint32> GMouse::m_mousePosGui = {};
bool GMouse::m_mouseMoved = false;
Sint8 GMouse::m_mouseStates[32];
float GMouse::m_mouseDelay[32];
Sint8 GMouse::m_mouseScroll = 0;

void GMouse::init() {
	for(Sint8 i = 0; i < m_mouseCount; i++) {
		m_mouseStates[i] = 0;
		m_mouseDelay[i] = 0;
	}
	m_mouseScroll = 0;
	m_mouseMoved = false;
}
void GMouse::update() {
	for(Sint8 i = 0; i < m_mouseCount; i++) {
		if(mousePressed(i)) {
			m_mouseStates[i] = MOUSE_HOLD;
		}
		else if(mouseReleased(i)) {
			m_mouseStates[i] = 0;
		}
	}
	m_mouseScroll = 0;
	m_mouseMoved = false;
}
void GMouse::mouseEvent(int p_button, int p_state) {
	switch(p_state) {
	case 0: releaseMouse(p_button); break;
	case 1: pressMouse(p_button); break;
	default: break;
	}
}
void GMouse::setMousePos(Vector2<Sint32> p_mousePos) {
	if(!(m_mousePos == p_mousePos)) {
		m_mousePos = p_mousePos;
		m_mouseMoved = true;
	}
}
void GMouse::addMousePos(Vector2<Sint32> p_mousePos) {
	m_mousePos = m_mousePos + p_mousePos;
	m_mouseMoved = true;
}
void GMouse::setMousePosGui(Vector2<Sint32> p_mousePos) {
	m_mousePosGui = p_mousePos;
}
void GMouse::addMousePosGui(Vector2<Sint32> p_mousePos) {
	m_mousePosGui = m_mousePosGui + p_mousePos;
}
void GMouse::pressMouse(Sint8 p_mouseCode) {
	m_mouseStates[p_mouseCode] = MOUSE_PRESS + MOUSE_HOLD;
	if(m_mouseDelay[p_mouseCode] < glfwGetTime() - 0.5f)
		m_mouseStates[p_mouseCode] += MOUSE_DOUBLECLICK;
	m_mouseDelay[p_mouseCode] = (float) glfwGetTime();
}
void GMouse::releaseMouse(Sint8 p_mouseCode) {
	m_mouseStates[p_mouseCode] = 4;
}
void GMouse::addScroll(Sint8 p_scroll) {
	m_mouseScroll += p_scroll;
}
