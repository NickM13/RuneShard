#include "engine\game\menu\PauseScreen.h"
#include "engine\game\menu\ingame\PSMain.h"

PSMain::PSMain()
{
	m_name = "Main";
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Resume", {0, -40}, {256, 32}, 1, []() { PauseScreen::getInstance().setScreen(0); }), ALIGN_CENTER);
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Options", {0, 0}, {256, 32}, 1, []() { PauseScreen::getInstance().setScreen("Options"); }), ALIGN_CENTER);
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Erixit Game", {0, 40}, {256, 32}, 1, []() { Globals::getInstance().m_exitting = 2; }), ALIGN_CENTER);
}
