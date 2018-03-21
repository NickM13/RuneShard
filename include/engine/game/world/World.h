#pragma once

#include "data\WorldData.h"

#include "engine\utils\variable\datatype\Color.h"
#include "engine\utils\Singleton.h"

#include "entity\actor\LActor.h"
#include "entity\world\WorldEntity.h"
#include "entity\particle\Particle.h"
#include "camera\Camera.h"

#include "engine\gfx\LTexture.h"

#include <vector>
#include <iostream>

class World
{
protected:
	bool m_initialized = false;
	Camera* m_camera;
	Texture* m_skyTexture;
	WorldData m_worldData;
	GLfloat** m_heightMap;
public:
	World();
	// World size in chunks.  Chunk size is 16
	void init(Vector2<Sint32> p_worldSize);
	virtual void generate(Vector2<Sint32> p_worldSize);
	void clear();
	~World();

	void setVoxel(Vector3<Sint32> p_pos, Uint32 p_voxel);
	Voxel getVoxel(Vector3<Sint32> p_pos);
	Uint16 getVoxelId(Vector3<Sint32> p_pos);
	void addChunk(Vector2<Sint32> p_chunk);

	Actor* addActor(Actor* p_actor);

	void input(Vector2<Sint32> p_mousePos);
	void update(GLfloat p_deltaUpdate);
	void render3d();
	void renderSkyBox();
	void render2d();

	void save(std::string p_worldName);
	void load(std::string p_worldName);

	Vector3<GLfloat> getHeightPoint(Vector2<Sint32> p_pos) { return Vector3<GLfloat>(p_pos.x, round(m_heightMap[p_pos.x][p_pos.y]), p_pos.y); };

	Actor* getPlayer() { return m_camera->getActor(); }
	Camera* getCamera() { return m_camera; }
};
