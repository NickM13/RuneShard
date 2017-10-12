#include "engine\gfx\model\VoxelMatrix.h"

VoxelMatrix::VoxelMatrix(std::string p_name, Vector3<GLfloat> p_pos, Vector3<Sint16> p_size)
{
	m_name = p_name;
	m_size = p_size;
	m_pos = p_pos;

	Uint16 noVoxel = MVoxel::getInstance().getUnitID(Voxel(0, MColor::getInstance().getUnitID(Color())));

	m_voxelData = new Uint16**[m_size.x + 2];
	m_faceData = new Sint8**[m_size.x + 2];
	for(Uint16 x = 0; x < m_size.x + 2; x++)
	{
		m_voxelData[x] = new Uint16*[m_size.y + 2];
		m_faceData[x] = new Sint8*[m_size.y + 2];
		for(Uint16 y = 0; y < m_size.y + 2; y++)
		{
			m_voxelData[x][y] = new Uint16[m_size.z + 2];
			m_faceData[x][y] = new Sint8[m_size.z + 2];
			for(Uint16 z = 0; z < m_size.z + 2; z++)
			{
				m_voxelData[x][y][z] = noVoxel;
				m_faceData[x][y][z] = FACE_ALL;
			}
		}
	}
	m_mesh = new VoxelMesh();
}
VoxelMatrix::VoxelMatrix(VoxelMatrix& m)
{
	m_name = m.getName();
	m_size = m.getSize();
	m_pos = m.getPos();

	Uint16 noVoxel = MVoxel::getInstance().getUnitID(Voxel(0, MColor::getInstance().getUnitID(Color())));

	m_voxelData = new Uint16**[m_size.x + 2];
	m_faceData = new Sint8**[m_size.x + 2];
	for(Uint16 x = 0; x < m_size.x + 2; x++)
	{
		m_voxelData[x] = new Uint16*[m_size.y + 2];
		m_faceData[x] = new Sint8*[m_size.y + 2];
		for(Uint16 y = 0; y < m_size.y + 2; y++)
		{
			m_voxelData[x][y] = new Uint16[m_size.z + 2];
			m_faceData[x][y] = new Sint8[m_size.z + 2];
			for(Uint16 z = 0; z < m_size.z + 2; z++)
			{
				m_voxelData[x][y][z] = noVoxel;
				m_faceData[x][y][z] = FACE_ALL;
			}
		}
	}

	for(Uint16 x = 0; x < m_size.x; x++)
		for(Uint16 y = 0; y < m_size.y; y++)
			for(Uint16 z = 0; z < m_size.z; z++)
				setVoxel({x, y, z}, m.getVoxel({x, y, z}));

	m_mesh = new VoxelMesh();
}

VoxelMatrix::~VoxelMatrix()
{
	if(m_size.x > 0 && m_size.y > 0 && m_size.z > 0)
	{
		for(Uint16 x = 0; x < m_size.x + 2; x++)
		{
			for(Uint16 y = 0; y < m_size.y + 2; y++)
			{
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
}

void VoxelMatrix::operator=(VoxelMatrix& m)
{
	for(Uint16 x = 0; x < m_size.x + 2; x++)
	{
		for(Uint16 y = 0; y < m_size.y + 2; y++)
		{
			delete[] m_voxelData[x][y];
			delete[] m_faceData[x][y];
		}
		delete[] m_voxelData[x];
		delete[] m_faceData[x];
	}
	delete[] m_voxelData;
	delete[] m_faceData;

	delete m_mesh;



	m_name = m.getName();
	m_size = m.getSize();
	m_pos = m.getPos();

	Uint16 noVoxel = MVoxel::getInstance().getUnitID(Voxel(0, MColor::getInstance().getUnitID(Color())));

	m_voxelData = new Uint16**[m_size.x + 2];
	m_faceData = new Sint8**[m_size.x + 2];
	for(Uint16 x = 0; x < m_size.x + 2; x++)
	{
		m_voxelData[x] = new Uint16*[m_size.y + 2];
		m_faceData[x] = new Sint8*[m_size.y + 2];
		for(Uint16 y = 0; y < m_size.y + 2; y++)
		{
			m_voxelData[x][y] = new Uint16[m_size.z + 2];
			m_faceData[x][y] = new Sint8[m_size.z + 2];
			for(Uint16 z = 0; z < m_size.z + 2; z++)
			{
				m_voxelData[x][y][z] = noVoxel;
				m_faceData[x][y][z] = FACE_ALL;
			}
		}
	}

	for(Uint16 x = 0; x < m_size.x; x++)
		for(Uint16 y = 0; y < m_size.y; y++)
			for(Uint16 z = 0; z < m_size.z; z++)
				setVoxel({x, y, z}, m.getVoxel({x, y, z}));

	m_mesh = new VoxelMesh();
}

void VoxelMatrix::setSize(Vector3<Sint32> p_size)
{
	p_size = Vector3<Sint32>(max(p_size.x, 1), max(p_size.y, 1), max(p_size.z, 1));
	Vector3<Sint32> _size = Vector3<Sint32>(min(p_size.x, m_size.x), min(p_size.y, m_size.y), min(p_size.z, m_size.z));

	Voxel*** _voxelData = new Voxel**[_size.x];
	for(Uint16 x = 0; x < _size.x; x++)
	{
		_voxelData[x] = new Voxel*[_size.y];
		for(Uint16 y = 0; y < _size.y; y++)
		{
			_voxelData[x][y] = new Voxel[_size.z];
			for(Uint16 z = 0; z < _size.z; z++)
			{
				_voxelData[x][y][z] = getVoxel({x, y, z});
			}
		}
	}

	for(Uint16 x = 0; x < m_size.x + 2; x++)
	{
		for(Uint16 y = 0; y < m_size.y + 2; y++)
		{
			delete[] m_voxelData[x][y];
			delete[] m_faceData[x][y];
		}
		delete[] m_voxelData[x];
		delete[] m_faceData[x];
	}
	delete[] m_voxelData;
	delete[] m_faceData;

	m_size = p_size;

	Uint16 noVoxel = MVoxel::getInstance().getUnitID(Voxel(0, MColor::getInstance().getUnitID(Color())));

	m_voxelData = new Uint16**[p_size.x + 2];
	m_faceData = new Sint8**[p_size.x + 2];
	for(Uint16 x = 0; x < p_size.x + 2; x++)
	{
		m_voxelData[x] = new Uint16*[p_size.y + 2];
		m_faceData[x] = new Sint8*[p_size.y + 2];
		for(Uint16 y = 0; y < p_size.y + 2; y++)
		{
			m_voxelData[x][y] = new Uint16[p_size.z + 2];
			m_faceData[x][y] = new Sint8[p_size.z + 2];
			for(Uint16 z = 0; z < p_size.z + 2; z++)
			{
				m_voxelData[x][y][z] = noVoxel;
				m_faceData[x][y][z] = FACE_ALL;
			}
		}
	}

	for(Uint16 x = 0; x < p_size.x + 2; x++)
		for(Uint16 y = 0; y < p_size.y + 2; y++)
			for(Uint16 z = 0; z < p_size.z + 2; z++)
				if(x != 0 && x <= _size.x && y != 0 && y <= _size.y && z != 0 && z <= _size.z)
					setVoxel({x - 1, y - 1, z - 1}, _voxelData[x - 1][y - 1][z - 1]);

}
void VoxelMatrix::setPosition(Vector3<GLfloat> p_pos)
{
	m_pos = p_pos;
	m_pos = (m_pos * 2).round() / 2;
}
void VoxelMatrix::addPosition(Vector3<GLfloat> p_pos)
{
	m_pos = m_pos + p_pos;
	m_pos = (m_pos * 2).round() / 2;
}

bool VoxelMatrix::setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel)
{
	if(p_pos.x < 0 || p_pos.y < 0 || p_pos.z < 0 || p_pos.x >= m_size.x || p_pos.y >= m_size.y || p_pos.z >= m_size.z) return false;
	Vector3<Sint32> _pos = p_pos + 1;
	if(m_voxelData[_pos.x][_pos.y][_pos.z] == MVoxel::getInstance().getUnitID(p_voxel)) return false;
	if(p_voxel.interactionType != MVoxel::getInstance().getUnit(m_voxelData[_pos.x][_pos.y][_pos.z]).interactionType)
	{
		// Set face data of surrounding voxels
		if(p_pos.x < m_size.x)
		{
			if(p_voxel.interactionType != 0 && (m_faceData[_pos.x + 1][_pos.y][_pos.z] & FACE_NORTH))
				m_faceData[_pos.x + 1][_pos.y][_pos.z] -= FACE_NORTH;
			else if(p_voxel.interactionType == 0 && !(m_faceData[_pos.x + 1][_pos.y][_pos.z] & FACE_NORTH))
				m_faceData[_pos.x + 1][_pos.y][_pos.z] += FACE_NORTH;
		}

		if(p_pos.x >= 0)
		{
			if(p_voxel.interactionType != 0 && (m_faceData[_pos.x - 1][_pos.y][_pos.z] & FACE_SOUTH))
				m_faceData[_pos.x - 1][_pos.y][_pos.z] -= FACE_SOUTH;
			else if(p_voxel.interactionType == 0 && !(m_faceData[_pos.x - 1][_pos.y][_pos.z] & FACE_SOUTH))
				m_faceData[_pos.x - 1][_pos.y][_pos.z] += FACE_SOUTH;
		}

		if(p_pos.z < m_size.z)
		{
			if(p_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y][_pos.z + 1] & FACE_WEST))
				m_faceData[_pos.x][_pos.y][_pos.z + 1] -= FACE_WEST;
			else if(p_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y][_pos.z + 1] & FACE_WEST))
				m_faceData[_pos.x][_pos.y][_pos.z + 1] += FACE_WEST;
		}

		if(p_pos.z >= 0)
		{
			if(p_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y][_pos.z - 1] & FACE_EAST))
				m_faceData[_pos.x][_pos.y][_pos.z - 1] -= FACE_EAST;
			else if(p_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y][_pos.z - 1] & FACE_EAST))
				m_faceData[_pos.x][_pos.y][_pos.z - 1] += FACE_EAST;
		}

		if(p_pos.y < m_size.y)
		{
			if(p_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y + 1][_pos.z] & FACE_BOTTOM))
				m_faceData[_pos.x][_pos.y + 1][_pos.z] -= FACE_BOTTOM;
			else if(p_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y + 1][_pos.z] & FACE_BOTTOM))
				m_faceData[_pos.x][_pos.y + 1][_pos.z] += FACE_BOTTOM;
		}

		if(p_pos.y >= 0)
		{
			if(p_voxel.interactionType != 0 && (m_faceData[_pos.x][_pos.y - 1][_pos.z] & FACE_TOP))
				m_faceData[_pos.x][_pos.y - 1][_pos.z] -= FACE_TOP;
			else if(p_voxel.interactionType == 0 && !(m_faceData[_pos.x][_pos.y - 1][_pos.z] & FACE_TOP))
				m_faceData[_pos.x][_pos.y - 1][_pos.z] += FACE_TOP;
		}
	}
	m_voxelData[_pos.x][_pos.y][_pos.z] = MVoxel::getInstance().getUnitID(p_voxel);
	m_needsRasterize = true;
	return true;
}
Voxel VoxelMatrix::getVoxel(Vector3<Sint32> p_pos)
{
	p_pos = p_pos + 1;
	return MVoxel::getInstance().getUnit(m_voxelData[p_pos.x][p_pos.y][p_pos.z]);
}
Uint16 VoxelMatrix::getVoxelId(Vector3<Sint32> p_pos)
{
	p_pos = p_pos + 1;
	return m_voxelData[p_pos.x][p_pos.y][p_pos.z];
}
void VoxelMatrix::shiftVoxels(Vector3<Sint32> d)
{
	Voxel*** _voxelData = new Voxel**[m_size.x];
	for(Sint32 x = 0; x < m_size.x; x++)
	{
		_voxelData[x] = new Voxel*[m_size.y];
		for(Sint32 y = 0; y < m_size.y; y++)
		{
			_voxelData[x][y] = new Voxel[m_size.z];
			for(Sint32 z = 0; z < m_size.z; z++)
			{
				_voxelData[x][y][z] = getVoxel({x, y, z});
			}
		}
	}

	Vector3<Sint32> _offset;
	for(Sint32 x = 0; x < m_size.x; x++)
		for(Sint32 y = 0; y < m_size.y; y++)
			for(Sint32 z = 0; z < m_size.z; z++)
			{
				_offset = Vector3<Sint32>(fmod(x + d.x, m_size.x), fmod(y + d.y, m_size.y), fmod(z + d.z, m_size.z));
				if(_offset.x < 0) _offset.x += m_size.x;
				if(_offset.y < 0) _offset.y += m_size.y;
				if(_offset.z < 0) _offset.z += m_size.z;
				setVoxel(_offset, _voxelData[x][y][z]);
			}


}

void VoxelMatrix::update()
{
	
}
void VoxelMatrix::render()
{
	if(m_needsRasterize) rasterize();
	glPushMatrix();
	{
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		m_mesh->renderMesh();
	}
	glPopMatrix();
}

void VoxelMatrix::rasterize()
{
	m_mesh->createMesh(m_voxelData, m_faceData, m_size);
	m_needsRasterize = false;
}
