#pragma once
#include "engine\utils\variable\datatype\Macros.h"
#include <vector>

// Global class for Key events
class GKey
{
public:
	struct KeyPress {
		Sint32 m_keyCode;
		Sint32 m_scanCode;
		Sint32 m_action;
		Sint32 m_mods;
	};
private:
	enum Event {
		KEY_PRESS = 1,
		KEY_HOLD = 2,
		KEY_RELEASE = 4
	};
	static const Sint16 m_keyCount = 1024;
	static const Sint16 m_specCount = 1024;
	static Sint8 m_keyStates[m_keyCount];
	static Sint8 m_specStates[m_specCount];
	static std::vector<KeyPress> m_keyEvents;

	static void pressKey(Sint32 p_keyCode);
	static void releaseKey(Sint32 p_keyCode);
public:
	static void init();
	static void update();
	static void keyEvent(Sint32 p_keyCode, Sint32 p_scanCode, Sint32 p_action, Sint32 p_mods);
	static bool keyPressed(Sint32 p_keyCode) { return (m_keyStates[p_keyCode] & KEY_PRESS); }
	static bool keyDown(Sint32 p_keyCode) { return (m_keyStates[p_keyCode] & KEY_HOLD); }
	static bool keyReleased(Sint32 p_keyCode) { return (m_keyStates[p_keyCode] & KEY_RELEASE); }
	static std::vector<KeyPress> getKeyEvents() { return m_keyEvents; }

	static void keyBreakpoint(Sint32 p_key);
};
