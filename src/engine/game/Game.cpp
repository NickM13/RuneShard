#include "engine\game\Game.h"

#include "engine\gfx\font\Font.h"

#include "engine\sfx\Sound.h"

#include <functional>
#include <iostream>

bool Game::init()
{
	m_engineState = GAME;

	LTexture::init();
	Font::getInstance().loadFont("UI", "res\\segoeui.ttf", 10);
	Sound::getInstance().init();

	m_world = new WorldIsland();
	m_world->generate(Vector2<Sint32>(32, 32));

	return true;
}

void Game::resize()
{

}

void Game::setEngineState(EngineState p_state)
{
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

void Game::input()
{
	Vector2<Sint32> _mouseMoved = Globals::getInstance().m_mousePos - m_mouseBuffer;
	m_mouseBuffer = Globals::getInstance().m_mousePos;
	Globals::getInstance().m_guiMousePos = Globals::getInstance().m_guiMousePos + _mouseMoved;

	if(Globals::getInstance().m_guiMousePos.x < Globals::getInstance().m_screenSize.x / -2)
		Globals::getInstance().m_guiMousePos.x = Globals::getInstance().m_screenSize.x / -2;
	if(Globals::getInstance().m_guiMousePos.y < Globals::getInstance().m_screenSize.y / -2)
		Globals::getInstance().m_guiMousePos.y = Globals::getInstance().m_screenSize.y / -2;

	if(Globals::getInstance().m_guiMousePos.x > Globals::getInstance().m_screenSize.x / 2)
		Globals::getInstance().m_guiMousePos.x = Globals::getInstance().m_screenSize.x / 2;
	if(Globals::getInstance().m_guiMousePos.y > Globals::getInstance().m_screenSize.y / 2)
		Globals::getInstance().m_guiMousePos.y = Globals::getInstance().m_screenSize.y / 2;

	if(Globals::getInstance().m_keyStates[GLFW_KEY_ESCAPE] == 1)
	{
		if(m_engineState == GAME)
		{
			if(PauseScreen::getInstance().isPaused())
			{
				PauseScreen::getInstance().setScreen(0);
			}
			else
			{
				PauseScreen::getInstance().setScreen(1);
				Globals::getInstance().m_guiMousePos = {};
			}
		}
	}

	switch(m_engineState)
	{
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

void Game::update()
{
	m_deltaUpdate = min(0.5f, GLfloat(glfwGetTime() - m_lastUpdate));
	m_lastUpdate = GLfloat(glfwGetTime());

	Globals::getInstance().m_deltaTime = m_deltaUpdate;

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
}

void Game::render3d()
{
	switch(m_engineState)
	{
	case MENU:

		break;
	case GAME:
		m_world->render();
		break;
	}
}
void Game::renderMouse()
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor3f(1, 1, 1);
		glTranslatef(GLfloat(Globals::getInstance().m_guiMousePos.x), GLfloat(Globals::getInstance().m_guiMousePos.y), 0);
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
void Game::render2d()
{
	switch(m_engineState)
	{
	case MENU:

		break;
	case GAME:
		Font::getInstance().setAlignment(Alignment::ALIGN_LEFT);
		Font::getInstance().print(std::string("X: ") + Util::numToString(m_world->getPlayer()->getCenter().x, 2), -Globals::getInstance().m_screenSize.x / 2 + 5, -Globals::getInstance().m_screenSize.y / 2 + 10);
		Font::getInstance().print(std::string("Y: ") + Util::numToString(m_world->getPlayer()->getCenter().y, 2), -Globals::getInstance().m_screenSize.x / 2 + 5, -Globals::getInstance().m_screenSize.y / 2 + 30);
		Font::getInstance().print(std::string("Z: ") + Util::numToString(m_world->getPlayer()->getCenter().z, 2), -Globals::getInstance().m_screenSize.x / 2 + 5, -Globals::getInstance().m_screenSize.y / 2 + 50);
		if(PauseScreen::getInstance().isPaused())
		{
			PauseScreen::getInstance().render();
			renderMouse();
		}
		break;
	}
}

void Game::close()
{
	switch(m_engineState)
	{
	case MENU:

		break;
	case GAME:

		break;
	}

	Sound::getInstance().close();
}
