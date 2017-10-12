#pragma once

#include "engine\gfx\font\Font.h"
#include "engine\utils\Globals.h"
#include "engine\utils\OpenGL.h"
#include "engine\utils\Singleton.h"
#include "engine\utils\variable\datatype\Rectangle.h"
#include "engine\utils\variable\manager\TextureManager.h"
#include "engine\gfx\LTexture.h"

#include "engine\gfx\gui\Button.h"
#include "engine\gfx\gui\Container.h"
#include "engine\gfx\gui\Panel.h"
#include "engine\gfx\gui\Text.h"

#include "menu\PauseScreen.h"

#include "world\World.h"
#include "world\type\WorldDungeon.h"
#include "world\type\WorldIsland.h"

#include <vector>

class Game : public Singleton<Game>
{
public:
	enum EngineState
	{
		MENU = 0,
		GAME = 1
	} m_engineState;

	~Game() {Font::getInstance().clean();};
	bool init();
	void resize();

	void setEngineState(EngineState p_state);

	void input();
	void update();
	void renderMouse();
	void render3d();
	void render2d();

	void close();
private:
	struct Stamp
	{
		Vector2<Sint32> m_size;
		Uint16 **m_ground, **m_world, **m_entity, **m_sky;

		Stamp(Vector2<Sint32> p_size = {}, Uint16** p_ground = 0, Uint16** p_world = 0, Uint16** p_entity = 0, Uint16** p_sky = 0) :
			m_size(p_size),
			m_ground(p_ground),
			m_world(p_world),
			m_entity(p_entity),
			m_sky(p_sky) {}
	};

	GLfloat m_lastUpdate, m_deltaUpdate;
	Vector2<Sint32> m_mouseBuffer;

	World* m_world;
};
