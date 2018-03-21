#pragma once
#include "engine\network\NetworkAdapter.h"

#include "engine\gfx\font\Font.h"
#include "engine\gfx\LTexture.h"
#include "engine\gfx\sprite\SpriteAnimation.h"

#include "engine\sfx\Sound.h"

#include "engine\utils\global\event\GKey.h"
#include "engine\utils\global\event\GMouse.h"
#include "engine\utils\global\GScreen.h"
#include "engine\utils\LOpenGL.h"
#include "engine\utils\Singleton.h"
#include "engine\utils\Utilities.h"
#include "engine\utils\variable\datatype\Rectangle.h"
#include "engine\utils\variable\manager\TextureManager.h"

#include "console\Console.h"

#include "menu\PauseScreen.h"

#include "world\World.h"
#include "world\type\WorldDungeon.h"
#include "world\type\WorldIsland.h"
#include "engine\gfx\gui\container\Container.h"

#include <vector>

class Game
{
protected:
	GLfloat m_lastUpdate, m_deltaUpdate;
	Vector2<Sint32> m_mouseBuffer;
	World* m_world;
	Container* m_gui;
	Texture *m_vignette;
	SpriteAnimation *m_cursor;
	Source* m_music;
public:
	enum GameState {
		MENU = 0,
		GAME = 1
	} m_gameState;

	Game();
	~Game();
	void resize();

	void setGameState(GameState p_state);
	World* getWorld() { return m_world; }

	void input();
	void update();
	void renderMouse();
	void render3d();
	void render2d();
};
