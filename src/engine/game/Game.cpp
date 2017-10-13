#include "engine\game\Game.h"

#include "engine\game\command\Command.h"
#include "engine\gfx\font\Font.h"
#include "engine\sfx\Sound.h"

#include "engine\utils\global\GGameState.h"

#include <functional>
#include <iostream>

Game::Game() {
	m_engineState = GAME;
	LTexture::init();
	Font::loadFont("UI", "res\\segoeui.ttf", 10);
	Sound::getInstance().init();
	m_world = new WorldIsland();
	m_world->generate(Vector2<Sint32>(4, 4));
	MChatCommand::addCommand("exit", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			GScreen::m_exitting = 2;
			return true;
		}
		return false;
	}, "exit", "Exits game"));
	MChatCommand::addCommand("outline", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 2) {
			if(p_args[1] == "true") {
				GGameState::m_modelOutline = true;
				MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Model outlines enabled");
				return true;
			}
			else if(p_args[1] == "false") {
				GGameState::m_modelOutline = false;
				MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Model outlines disabled");
				return true;
			}
		}
		return false;
	}, "outline <true/false>", "Turns on/off outlines"));
	MChatCommand::addCommand("tp", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 4) {
			Vector3<GLfloat> pos;
			try {
				pos.x = std::stof(p_args[1]);
				pos.y = std::stof(p_args[2]);
				pos.z = std::stof(p_args[3]);
			}
			catch(std::invalid_argument e) {
				return false;
			}
			m_world->getPlayer()->setPosition(pos);
			MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Player teleported");
			return true;
		}
		return false;
	}, "tp x y z", "Teleports you"));
	MChatCommand::addCommand("spawn", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			m_world->addActor(new Actor());
			return true;
		}
		else if(p_args.size() == 4) {
			Vector3<GLfloat> pos;
			try {
				pos.x = std::stof(p_args[1]);
				pos.y = std::stof(p_args[2]);
				pos.z = std::stof(p_args[3]);
			}
			catch(std::invalid_argument e) {
				return false;
			}
			m_world->getPlayer()->setPosition(pos);
			m_world->addActor(new Actor());
			MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Player teleported");
			return true;
		}
		return false;
	}, "**WIP**", "Create entity"));
	MChatCommand::addCommand("help", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			MChatCommand::help();
			return true;
		}
		return false;
	}, "help", "Displays all commands"));
	MKeyCommand::addCommand({'`', 0}, new KeyCommand([&]() {
		MConsole::setOpen(true);
	}));
	MKeyCommand::addCommand({GLFW_KEY_ESCAPE, 0}, new KeyCommand([&]() {
		GScreen::m_exitting = 2;
	}));
}
Game::~Game() {
	Sound::getInstance().close();
}

void Game::resize() {

}

void Game::setEngineState(EngineState p_state) {
	if(m_engineState != p_state)
	{
		m_engineState = p_state;
		switch(m_engineState)
		{
		case MENU:

			break;
		case GAME:

			break;
		}
	}
}

void Game::input() {
	Vector2<Sint32> _mouseMoved = GMouse::getMousePos() - m_mouseBuffer;
	Vector2<Sint32> _mouseGui = GMouse::getMousePosGui() + _mouseMoved;
	m_mouseBuffer = GMouse::getMousePos();
	if(_mouseGui.x < GScreen::m_screenSize.x / -2)
		_mouseGui.x = GScreen::m_screenSize.x / -2;
	if(_mouseGui.y < GScreen::m_screenSize.y / -2)
		_mouseGui.y = GScreen::m_screenSize.y / -2;
	if(_mouseGui.x > GScreen::m_screenSize.x / 2)
		_mouseGui.x = GScreen::m_screenSize.x / 2;
	if(_mouseGui.y > GScreen::m_screenSize.y / 2)
		_mouseGui.y = GScreen::m_screenSize.y / 2;
	GMouse::setMousePosGui(_mouseGui);
	if(!MConsole::isOpen()) {
		for(GKey::KeyPress keyPress : GKey::getKeyEvents()) {
			if(keyPress.m_action == 1) {
				MKeyCommand::checkCommand({keyPress.m_keyCode, keyPress.m_mods});
			}
		}
		switch(m_engineState) {
		case MENU:

			break;
		case GAME:
			if(!PauseScreen::getInstance().isPaused())
				m_world->input(_mouseMoved);
			else
				PauseScreen::getInstance().input();
			break;
		}
	}
	else MConsole::input();
}
void Game::update() {
	m_deltaUpdate = min(0.5f, GLfloat(glfwGetTime() - m_lastUpdate));
	m_lastUpdate = GLfloat(glfwGetTime());

	GScreen::m_deltaTime = m_deltaUpdate;

	switch(m_engineState)
	{
	case MENU:

		break;
	case GAME:
		if(!PauseScreen::getInstance().isPaused())
			m_world->update(m_deltaUpdate);
		else
			PauseScreen::getInstance().update(m_deltaUpdate);
		break;
	}
	MConsole::update();
}
void Game::render3d() {
	switch(m_engineState)
	{
	case MENU:

		break;
	case GAME:
		m_world->render();
		break;
	}
}
void Game::renderMouse() {
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor3f(1, 1, 1);
		glTranslatef(GLfloat(GMouse::getMousePosGui().x), GLfloat(GMouse::getMousePosGui().y), 0);
		glBegin(GL_QUADS);
		{
			glVertex2f(0, 0);
			glVertex2f(8, 0);
			glVertex2f(8, 8);
			glVertex2f(0, 8);
		}
		glEnd();
	}
	glPopMatrix();
}
void Game::render2d() {
	switch(m_engineState)
	{
	case MENU:

		break;
	case GAME:
		Font::setAlignment(Alignment::ALIGN_LEFT);
		Font::print(std::string("X: ") + Util::numToString(m_world->getPlayer()->getCenter().x, 2), -GScreen::m_screenSize.x / 2 + 5, -GScreen::m_screenSize.y / 2 + 10);
		Font::print(std::string("Y: ") + Util::numToString(m_world->getPlayer()->getCenter().y, 2), -GScreen::m_screenSize.x / 2 + 5, -GScreen::m_screenSize.y / 2 + 30);
		Font::print(std::string("Z: ") + Util::numToString(m_world->getPlayer()->getCenter().z, 2), -GScreen::m_screenSize.x / 2 + 5, -GScreen::m_screenSize.y / 2 + 50);
		if(PauseScreen::getInstance().isPaused()) {
			PauseScreen::getInstance().render();
		}
		if(PauseScreen::getInstance().isPaused() || MConsole::isOpen()) {
			renderMouse();
		}
		break;
	}
	MConsole::render();
}
