#pragma once

#include "engine\gfx\font\Font.h"
#include "engine\utils\global\event\GKey.h"
#include "engine\utils\global\event\GMouse.h"
#include "engine\utils\global\GScreen.h"
#include "engine\utils\OpenGL.h"
#include "engine\utils\Singleton.h"
#include "engine\utils\Utilities.h"
#include "engine\utils\variable\datatype\Rectangle.h"
#include "engine\utils\variable\manager\TextureManager.h"
#include "engine\gfx\LTexture.h"

#include "console\Console.h"

#include "menu\PauseScreen.h"

#include "world\World.h"
#include "world\type\WorldDungeon.h"
#include "world\type\WorldIsland.h"

#include <vector>

class Game
{
protected:
	GLfloat m_lastUpdate, m_deltaUpdate;
	Vector2<Sint32> m_mouseBuffer;
	World* m_world;
	
public:
	enum EngineState {
		MENU = 0,
		GAME = 1
	} m_engineState;

	Game();
	~Game();
	void resize();

	void setEngineState(EngineState p_state);
	World* getWorld() { return m_world; }

	void input();
	void update();
	void renderMouse();
	void render3d();
	void render2d();
};
