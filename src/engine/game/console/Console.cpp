#include "engine\game\console\Console.h"
#include "engine\gfx\font\Font.h"
#include "engine\game\command\Command.h"

std::vector<MConsole::ConsoleLine> MConsole::m_consoleLog;
std::string MConsole::m_inputLine;
bool MConsole::m_isOpen = false;

void MConsole::addLine(ConsoleLine::MessageType type, std::string p_message) {
	m_consoleLog.insert(m_consoleLog.begin(), {type, p_message});
}
void MConsole::setOpen(bool p_state) {
	m_isOpen = p_state;
}
bool MConsole::isOpen() {
	return m_isOpen;
}
void MConsole::input() {
	if(!m_isOpen) return;
	for(GKey::KeyPress keyPress : GKey::getKeyEvents()) {
		if(keyPress.m_action != 0) {
			if((keyPress.m_keyCode >= ' ' && keyPress.m_keyCode < '`')) {
				if(!(keyPress.m_mods & GLFW_MOD_SHIFT) && keyPress.m_keyCode >= GLFW_KEY_A && keyPress.m_keyCode <= GLFW_KEY_Z)
					m_inputLine += (char)(keyPress.m_keyCode - ('A' - 'a'));
				else
					m_inputLine += (char)keyPress.m_keyCode;
			}
			else if(keyPress.m_keyCode == GLFW_KEY_BACKSPACE) {
				if(m_inputLine.size() > 0)
					m_inputLine = m_inputLine.substr(0, m_inputLine.size() - 1);
			}
			else if(keyPress.m_keyCode == GLFW_KEY_ENTER) {
				addLine(ConsoleLine::NORMAL, "> " + m_inputLine);
				MChatCommand::checkCommand(m_inputLine);
				m_inputLine.clear();
			}
			else if(keyPress.m_keyCode == '`' || keyPress.m_keyCode == GLFW_KEY_ESCAPE) {
				setOpen(false);
			}
		}
	}
}
void MConsole::update() {
	if(!m_isOpen) return;

}
void MConsole::render() {
	if(!m_isOpen) return;
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	{
		glColor4f(0, 0, 0, 0.75f);
		glVertex2f(-GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2 - 20);
		glVertex2f(GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2 - 20);
		glVertex2f(GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2);
		glVertex2f(-GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2);
		glColor4f(0, 0, 0, 0.35f);
		glVertex2f(-GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2 - 24 - Font::getSpacingHeight() * m_consoleLog.size());
		glVertex2f(GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2 - 24 - Font::getSpacingHeight() * m_consoleLog.size());
		glVertex2f(GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2 - 24);
		glVertex2f(-GScreen::m_screenSize.x / 2, GScreen::m_screenSize.y / 2 - 24);
	}
	glEnd();
	glColor3f(1, 1, 1);
	Font::print(m_inputLine, 10, GScreen::m_screenSize.y - 10);
	for(Uint16 i = 0; i < min(m_consoleLog.size(), 20); i++) {
		switch(m_consoleLog[i].type) {
		case ConsoleLine::NORMAL:
			glColor3f(1, 1, 1);
			break;
		case ConsoleLine::WARNING:
			glColor3f(1, 1, 0);
			break;
		case ConsoleLine::MISUSE:
		default:
			glColor3f(1, 0.25f, 0.25f);
			break;
		}
		Font::print(m_consoleLog[i].message, 10, GScreen::m_screenSize.y - 34 - i * Font::getSpacingHeight());
	}
}
