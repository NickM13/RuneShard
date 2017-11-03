#include "engine\game\Game.h"

#include "engine\game\command\Command.h"
#include "engine\gfx\font\Font.h"
#include "engine\sfx\Sound.h"

#include "engine\utils\global\GGameState.h"
#include "engine\game\debug\DebugUI.h"

#include <functional>
#include <iostream>

Game::Game() {
	m_gui = new Container("", GScreen::m_screenSize / -2, GScreen::m_screenSize / 2, true);
	DebugUI::init();
	// Enable these for debugging purposes
	//m_gui->addComponent(DebugUI::getGraph1());
	//m_gui->addComponent(DebugUI::getGraph2());
	//m_gui->addComponent(DebugUI::getGraph3());
	m_gameState = GAME;
	LTexture::init();
	Font::loadFont("Console", "consolas.ttf", 10);
	Font::loadFont("UI", "segoeui.ttf", 10);
	m_vignette = MTexture::getTexture("gui\\Vignette.png");
	Sound::getInstance().init();
	m_world = new WorldIsland();
	m_world->generate(Vector2<Sint32>(4, 4));
	NetworkAdapter::init();
	MChatCommand::addCommand("exit", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			GScreen::m_exitting = 2;
			return true;
		}
		return false;
	}, "exit", "Exits game"));
	MChatCommand::addCommand("hello", new ChatCommand([&](std::vector<std::string> p_args) {
		MConsole::addLine(MConsole::ConsoleLine::MISUSE, "ERROR: PROGRAM MEMORY LEAK SPRUNG, PREPARE FOR EXTREME PC LAG AND POTENTIAL CRASHING.  ALSO, A VIRUS HAS BEEN INSTALLED.");
		return true;
	}, "hello", "Greet the console"));
	MChatCommand::addCommand("outline", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 2) {
			if(p_args[1] == "t" || p_args[1] == "true") {
				GGameState::m_outline = true;
				MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Outlines enabled");
				return true;
			}
			else if(p_args[1] == "f" || p_args[1] == "false") {
				GGameState::m_outline = false;
				MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Outlines disabled");
				return true;
			}
		}
		return false;
	}, "outline [t/f]", "Turns outlines on/off"));
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
	}, "tp [x] [y] [z]", "Teleports you"));
	MChatCommand::addCommand("roger", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			m_world->addActor(LActor::getActor("Roger")->setPosition(m_world->getCamera()->getPosition()));
			MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Roger doger'd");
			return true;
		}
		return false;
	}, "roger", "Creates a Roger on your location"));
	MChatCommand::addCommand("generate", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 3) {
			Vector2<Sint32> size;
			try {
				size.x = std::stof(p_args[1]);
				size.y = std::stof(p_args[2]);
			}
			catch(std::invalid_argument e) {
				return false;
			}
			m_world->generate(size);
			MConsole::addLine(MConsole::ConsoleLine::NORMAL, "New world created");
			return true;
		}
		return false;
	}, "generate [width] [height]", "Generate a new map"));
	MChatCommand::addCommand("actorlist", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			std::vector<Actor*> _list = MActor::getActorList();
			MConsole::addLine(MConsole::ConsoleLine::NORMAL, "Num of actors: " + Util::numToString(_list.size()));
			Uint16 i = 0;
			for(Actor* actor : _list) {
				MConsole::addLine(MConsole::ConsoleLine::NORMAL, Util::numToString(i) + ": " + actor->getName());
				i++;
			}
			return true;
		}
		return false;
	}, "actorlist", "Get a list of actors in the world"));
	MChatCommand::addCommand("connect", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			NetworkAdapter::connectIp("localhost");
			return true;
		}
		else if(p_args.size() == 2) {
			NetworkAdapter::connectIp(p_args[1]);
			return true;
		}
		else if(p_args.size() == 3) {
			NetworkAdapter::connectIp(p_args[1], p_args[2]);
			return true;
		}
		return false;
	}, "connect [ip]=localhost [port]=9234", "Connect to a server"));
	MChatCommand::addCommand("help", new ChatCommand([&](std::vector<std::string> p_args) {
		if(p_args.size() == 1) {
			MChatCommand::help();
			return true;
		}
		else if(p_args.size() == 2) {
			MChatCommand::help(p_args[1]);
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

void Game::setGameState(GameState p_state) {
	if(m_gameState != p_state)
	{
		m_gameState = p_state;
		switch(m_gameState)
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
		switch(m_gameState) {
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
	m_deltaUpdate = min(10.f/60, GLfloat(glfwGetTime() - m_lastUpdate));
	GScreen::m_deltaTime = m_deltaUpdate;

	switch(m_gameState)
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
	m_lastUpdate += m_deltaUpdate;
}
void Game::render3d() {
	switch(m_gameState)
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
	MConsole::render();
	Font::setFont("UI");
	m_gui->render();
	switch(m_gameState)
	{
	case MENU:

		break;
	case GAME:
		glColor3f(1, 1, 1);
		Font::setAlignment(Alignment::ALIGN_LEFT);
		//Font::print(std::string("X: ") + Util::numToString(m_world->getPlayer()->getCenter().x, 2), -GScreen::m_screenSize.x / 2 + 5, -GScreen::m_screenSize.y / 2 + 10);
		//Font::print(std::string("Y: ") + Util::numToString(m_world->getPlayer()->getCenter().y, 2), -GScreen::m_screenSize.x / 2 + 5, -GScreen::m_screenSize.y / 2 + 30);
		//Font::print(std::string("Z: ") + Util::numToString(m_world->getPlayer()->getCenter().z, 2), -GScreen::m_screenSize.x / 2 + 5, -GScreen::m_screenSize.y / 2 + 50);
		if(PauseScreen::getInstance().isPaused()) {
			PauseScreen::getInstance().render();
		}
		if(PauseScreen::getInstance().isPaused() || MConsole::isOpen()) {
			renderMouse();
		}
		break;
	}
	glBindTexture(GL_TEXTURE_2D, m_vignette->getId());
	glColor3f(1, 1, 1);
	glTranslatef(-GScreen::m_screenSize.x / 2, -GScreen::m_screenSize.y / 2, 0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0); glVertex2f(0, 0);
		glTexCoord2f(1, 0); glVertex2f(GScreen::m_screenSize.x, 0);
		glTexCoord2f(1, 1); glVertex2f(GScreen::m_screenSize.x, GScreen::m_screenSize.y);
		glTexCoord2f(0, 1); glVertex2f(0, GScreen::m_screenSize.y);
	}
	glEnd();
}
