#include "engine\game\world\data\Chunk.h"
#include "engine\utils\variable\manager\ColorManager.h"
#include "engine\utils\global\GGameState.h"

Chunk::Chunk() {
	Uint16 noVoxel = MVoxel::getVoxelId(Voxel(0, MColor::getColorId(Color())));
	m_voxelData = new Uint16**[CHUNK_SIZE + 2];
	m_faceData = new Sint8**[CHUNK_SIZE + 2];
	for(Uint16 x = 0; x < CHUNK_SIZE + 2; x++) {
		m_voxelData[x] = new Uint16*[CHUNK_SIZE + 2];
		m_faceData[x] = new Sint8*[CHUNK_SIZE + 2];
		for(Uint16 y = 0; y < CHUNK_SIZE + 2; y++) {
			m_voxelData[x][y] = new Uint16[CHUNK_SIZE + 2];
			m_faceData[x][y] = new Sint8[CHUNK_SIZE + 2];
			for(Uint16 z = 0; z < CHUNK_SIZE + 2; z++) {
				m_voxelData[x][y][z] = noVoxel;
				m_faceData[x][y][z] = FACE_ALL;
			}
		}
	}
	m_mesh = new VoxelMesh();
}
Chunk::~Chunk() {
	for(Uint16 x = 0; x < CHUNK_SIZE + 2; x++) {
		for(Uint16 y = 0; y < CHUNK_SIZE + 2; y++) {
			delete[] m_voxelData[x][y];
			delete[] m_faceData[x][y];
		}
		delete[] m_voxelData[x];
		delete[] m_faceData[x];
	}
	delete[] m_voxelData;
	delete[] m_faceData;

	delete m_mesh;
}
void Chunk::setVoxel(Vector3<Sint32> p_pos, Uint32 p_voxel) {
	Vector3<Sint32> _pos = p_pos + 1;
	Voxel _voxel = MVoxel::getVoxel(p_voxel);
	if(_voxel.interactionType != MVoxel::getVoxel(m_voxelData[_pos.x][_pos.y][_pos.z]).interactionType) {
		//set face data of surrounding voxels
		if(p_pos.x < CHUNK_SIZE) {
			if(_voxel.interactionType != 0 && (m_faceData[_pos.x + 1][_pos.y][_pos.z] & FACE_NORTH))
				m_faceData[_pos.x + 1][_pos.y][_pos.z] -= FACE_NORTH;
			else if(_voxel.interactionType == 0 && !(m_faceData[_pos.x + 1][_pos.y][_pos.z] & FACE_NORTH))
				m_faceData[_pos.x + 1][_pos.y][_pos.z] += FACE_NORTH;
		}
		if(p_pos.x >= 0) {
			if(_voxel.interactionType != 0 && (m_faceData[_pos.x - 1][_pos.y][_pos.z] & FACE_SOUTH))
				m_faceData[_pos.x - 1][_pos.y][_pos.z] -= FACE_SOUTH;
			else if(_voxel.interactionType == 0 && !(m_faceData[_pos.x - 1][_pos.y][_pos.z] & FACE_SOUTH))
				m_faceData[_pos.x - 1][_pos.y][_pos.z] += FACE_SOUTH;
		}
		if(p_pos.z < CHUNK_SIZE) {
			if(_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y][_pos.z + 1] & FACE_WEST))
				m_faceData[_pos.x][_pos.y][_pos.z + 1] -= FACE_WEST;
			else if(_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y][_pos.z + 1] & FACE_WEST))
				m_faceData[_pos.x][_pos.y][_pos.z + 1] += FACE_WEST;
		}
		if(p_pos.z >= 0) {
			if(_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y][_pos.z - 1] & FACE_EAST))
				m_faceData[_pos.x][_pos.y][_pos.z - 1] -= FACE_EAST;
			else if(_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y][_pos.z - 1] & FACE_EAST))
				m_faceData[_pos.x][_pos.y][_pos.z - 1] += FACE_EAST;
		}
		if(p_pos.y < CHUNK_SIZE) {
			if(_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y + 1][_pos.z] & FACE_BOTTOM))
				m_faceData[_pos.x][_pos.y + 1][_pos.z] -= FACE_BOTTOM;
			else if(_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y + 1][_pos.z] & FACE_BOTTOM))
				m_faceData[_pos.x][_pos.y + 1][_pos.z] += FACE_BOTTOM;
		}
		if(p_pos.y >= 0) {
			if(_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y - 1][_pos.z] & FACE_TOP))
				m_faceData[_pos.x][_pos.y - 1][_pos.z] -= FACE_TOP;
			else if(_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y - 1][_pos.z] & FACE_TOP))
				m_faceData[_pos.x][_pos.y - 1][_pos.z] += FACE_TOP;
		}
	}
	m_voxelData[_pos.x][_pos.y][_pos.z] = p_voxel;
	m_needsRasterize = true;
}
Voxel Chunk::getVoxel(Vector3<Sint32> p_pos) const {
	p_pos = p_pos + 1;
	return MVoxel::getVoxel(m_voxelData[p_pos.x][p_pos.y][p_pos.z]);
}
Uint16 Chunk::getVoxelId(Vector3<Sint32> p_pos) const {
	p_pos = p_pos + 1;
	return m_voxelData[p_pos.x][p_pos.y][p_pos.z];
}

void Chunk::update() {

}
void Chunk::render() {
	if(m_needsRasterize) {
		rasterize();
		m_needsRasterize = false;
	}
	m_mesh->renderMesh();
	if(GGameState::m_outline) {
		glBegin(GL_LINES);
		{
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(CHUNK_SIZE, 0, 0);

			glColor3f(0, 0.75f, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, CHUNK_SIZE, 0);

			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, CHUNK_SIZE);
		}
		glEnd();
	}
}

void Chunk::rasterize() {
	m_mesh->createMesh(m_voxelData, m_faceData, Vector3<Sint32>(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE));
}
