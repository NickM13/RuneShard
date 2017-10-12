#pragma once

#define GRAVITY 4

#include "data\WorldData.h"

#include "engine\utils\variable\datatype\Color.h"
#include "engine\utils\Singleton.h"

#include "entity\EntityManager.h"
#include "entity\world\WorldEntity.h"
#include "entity\particle\Particle.h"

#include "engine\gfx\LTexture.h"

#include <vector>
#include <iostream>

class World
{
public:
	World() {};
	World(Vector2<Sint32> p_worldSize) { generate(p_worldSize); }
	// World size in chunks.  Chunk size is 16
	void init(Vector2<Sint32> p_worldSize);
	virtual void generate(Vector2<Sint32> p_worldSize);
	~World();

	void setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel);
	Voxel getVoxel(Vector3<Sint32> p_pos);
	Uint16 getVoxelId(Vector3<Sint32> p_pos);

	void addChunk(Vector2<Sint32> p_chunk);

	Entity* addEntity(Entity* p_entity);
	void addWorldEntity(Vector2<Sint32> p_pos, VoxelModel* p_model);

	void input(Vector2<Sint32> p_mousePos);
	void update(GLfloat p_deltaUpdate);
	void render();
	void renderSkyBox();

	void save(std::string p_worldName);
	void load(std::string p_worldName);

	Vector3<GLfloat> getHeightPoint(Vector2<Sint32> p_pos) { return Vector3<GLfloat>(p_pos.x, round(m_heightMap[p_pos.x][p_pos.y]), p_pos.y); };

	Entity* getPlayer() { return m_player; }
protected:
	bool m_initialized = false;
	MEntity m_entities;
	Entity* m_player;

	Texture m_skyTexture;

	WorldData m_worldData;

	Vector3<GLfloat> m_camPos;
	Vector3<GLfloat> m_camRot;

	GLfloat** m_heightMap;
};
