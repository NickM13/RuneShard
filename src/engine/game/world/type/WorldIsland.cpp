#include "engine\game\world\type\WorldIsland.h"
#include "engine\utils\Perlin.h"

void WorldIsland::generate(Vector2<Sint32> p_worldSize)
{
	Perlin::initPerlin(1);

	init(p_worldSize);

	m_heightMap = new GLfloat*[m_worldData.m_worldSize.x * CHUNK_SIZE];
	for(Uint16 x = 0; x < m_worldData.m_worldSize.x * CHUNK_SIZE; x++)
	{
		m_heightMap[x] = new GLfloat[m_worldData.m_worldSize.z * CHUNK_SIZE];
		for(Uint16 y = 0; y < m_worldData.m_worldSize.z * CHUNK_SIZE; y++)
		{
			m_heightMap[x][y] = Perlin::perlinNoise(x / GLfloat(320), y / GLfloat(320), 1, 4, 32);
			if(m_heightMap[x][y] - (pow((2.f / (m_worldData.m_worldSize.x * CHUNK_SIZE)) * (x - (m_worldData.m_worldSize.x * CHUNK_SIZE) / 2), 2) + pow((2.f / (m_worldData.m_worldSize.z * CHUNK_SIZE)) * (y - (m_worldData.m_worldSize.z * CHUNK_SIZE) / 2), 2)) < 0)
				m_heightMap[x][y] = -1;
			else
				m_heightMap[x][y] = m_heightMap[x][y] * 8;
		}
	}

	Uint32 grass = MVoxel::getVoxelId(Voxel(1, MColor::getColorId(Color(0.62f, 0.87f, 0))));
	for(Uint16 x = 0; x < m_worldData.m_worldSize.x * CHUNK_SIZE; x++)
		for(Uint16 z = 0; z < m_worldData.m_worldSize.z * CHUNK_SIZE; z++)
			for(Uint16 y = 0; y < round(m_heightMap[x][z]) + 1; y++)
				setVoxel({x, y, z}, grass);
}
