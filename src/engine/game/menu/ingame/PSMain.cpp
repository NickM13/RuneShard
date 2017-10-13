#include "engine\game\menu\PauseScreen.h"
#include "engine\game\menu\ingame\PSMain.h"

PSMain::PSMain()
{
	m_name = "Main";
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Resume", {0, -40}, {256, 32}, CButton::RenderStyle::ALL, []() { PauseScreen::getInstance().setScreen(0); }), Anchor::CENTER);
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Options", {0, 0}, {256, 32}, CButton::RenderStyle::ALL, []() { PauseScreen::getInstance().setScreen("Options"); }), Anchor::CENTER);
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Erixit Game", {0, 40}, {256, 32}, CButton::RenderStyle::ALL, []() { GScreen::m_exitting = 2; }), Anchor::CENTER);
}
