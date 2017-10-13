#pragma once
#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector2.h"

// Global class for Mouse events
class GMouse
{
private:
	enum Event {
		MOUSE_HOLD = 1,			// Mouse held down
		MOUSE_PRESS = 2,		// Mouse just pressed
		MOUSE_RELEASE = 4,		// Mouse just released
		MOUSE_DOUBLECLICK = 8
	};
	static const Sint8 m_mouseCount = 32;
	static Vector2<Sint32> m_mousePos;
	static Vector2<Sint32> m_mousePosGui;
	static Sint8 m_mouseStates[m_mouseCount];
	static float m_mouseDelay[m_mouseCount];
	static Sint8 m_mouseScroll;
	static bool m_mouseMoved;

	static void pressMouse(Sint8 p_mouseCode);
	static void releaseMouse(Sint8 p_mouseCode);
public:
	static void init();
	static void update();
	static void addMousePos(Vector2<Sint32> p_mousePos);
	static void setMousePos(Vector2<Sint32> p_mousePos);
	static void addMousePosGui(Vector2<Sint32> p_mousePos);
	static void setMousePosGui(Vector2<Sint32> p_mousePos);
	static void mouseEvent(int p_button, int p_state);
	static void addScroll(Sint8 p_scroll);
	static Vector2<Sint32> getMousePos() { return m_mousePos; }
	static Vector2<Sint32> getMousePosGui() { return m_mousePosGui; }
	static bool mouseMoved() { return m_mouseMoved; }
	static bool mousePressed(Sint8 p_mouseCode) { return (m_mouseStates[p_mouseCode] & MOUSE_PRESS); }
	static bool mouseDown(Sint8 p_mouseCode) { return (m_mouseStates[p_mouseCode] & MOUSE_HOLD); }
	static bool mouseReleased(Sint8 p_mouseCode) { return (m_mouseStates[p_mouseCode] & MOUSE_RELEASE); }
	static bool mouseDoubleclicked(Sint8 p_mouseCode) { return (m_mouseStates[p_mouseCode] & MOUSE_DOUBLECLICK); }
	static Sint8 getScroll() { return m_mouseScroll; }
};
