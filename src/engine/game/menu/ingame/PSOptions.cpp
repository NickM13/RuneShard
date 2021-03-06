#include "engine\game\menu\PauseScreen.h"
#include "engine\game\menu\ingame\PSOptions.h"

PSOptions::PSOptions()
{
	m_name = "Options";
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Nothing", {0, -20}, {256, 32}, CButton::RenderStyle::ALL), Anchor::CENTER);
	m_gui.addComponent(new CButton("BUTTON_RESUME", "Back", {0, 20}, {256, 32}, CButton::RenderStyle::ALL, []() { PauseScreen::getInstance().setScreen("Main"); }), Anchor::CENTER);
}
