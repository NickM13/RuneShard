#include "engine\utils\global\event\GKey.h"

Sint8 GKey::m_keyStates[GKey::m_keyCount];
Sint8 GKey::m_specStates[GKey::m_specCount];
std::vector<GKey::KeyPress> GKey::m_keyEvents;

void GKey::init() {
	for(Uint16 i = 0; i < m_keyCount; i++)
		m_keyStates[i] = 0;
	for(Uint16 i = 0; i < m_specCount; i++)
		m_specStates[i] = 0;
}
void GKey::update() {
	for(KeyPress keyPress : m_keyEvents) {
		switch(keyPress.m_action) {
		case 0: m_keyStates[keyPress.m_keyCode] = 0; break;
		case 1: m_keyStates[keyPress.m_keyCode] = KEY_HOLD; break;
		default: break;
		}
	}
	m_keyEvents.clear();
}
void GKey::keyEvent(Sint32 p_keyCode, Sint32 p_scanCode, Sint32 p_action, Sint32 p_mods) {
	switch(p_action) {
	case 0: releaseKey(p_keyCode); break;
	case 1: pressKey(p_keyCode); break;
	default: break;
	}
	m_keyEvents.push_back({p_keyCode, p_scanCode, p_action, p_mods});
}
void GKey::pressKey(Sint32 p_keyCode) {
	m_keyStates[p_keyCode] = KEY_PRESS + KEY_HOLD;
}
void GKey::releaseKey(Sint32 p_keyCode) {
	m_keyStates[p_keyCode] = KEY_RELEASE;
}
